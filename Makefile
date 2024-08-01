# Nuke built-in rules and variables.
override MAKEFLAGS += -rR

# This is the name that our final kernel executable will have.
# Change as needed.
override KERNEL := bados

# Convenience macro to reliably declare user overridable variables.
define DEFAULT_VAR =
	ifeq ($(origin $1),default)
		override $(1) := $(2)
	endif
	ifeq ($(origin $1),undefined)
		override $(1) := $(2)
	endif
endef

# It is suggested to use a custom built cross toolchain to build a kernel.
# We are using the standard "cc" here, it may work by using
# the host system's toolchain, but this is not guaranteed.
override DEFAULT_KCC := clang++
$(eval $(call DEFAULT_VAR,KCC,$(DEFAULT_KCC)))

# Same thing for "ld" (the linker).
override DEFAULT_KLD := ld.lld
$(eval $(call DEFAULT_VAR,KLD,$(DEFAULT_KLD)))

# User controllable C flags.
override DEFAULT_KCFLAGS := -g  -pipe
$(eval $(call DEFAULT_VAR,KCFLAGS,$(DEFAULT_KCFLAGS)))

# User controllable C preprocessor flags. We set none by default.
override DEFAULT_KCPPFLAGS :=
$(eval $(call DEFAULT_VAR,KCPPFLAGS,$(DEFAULT_KCPPFLAGS)))

# User controllable nasm flags.
override DEFAULT_KNASMFLAGS := -F dwarf -g
$(eval $(call DEFAULT_VAR,KNASMFLAGS,$(DEFAULT_KNASMFLAGS)))

# User controllable linker flags. We set none by default.
override DEFAULT_KLDFLAGS :=
$(eval $(call DEFAULT_VAR,KLDFLAGS,$(DEFAULT_KLDFLAGS)))

# Internal C flags that should not be changed by the user.
override KCFLAGS += \
	-g \
	-Wall \
	-Wextra \
	-std=gnu11 \
	-ffreestanding \
	-fno-stack-protector \
	-fno-stack-check \
	-fno-lto \
	-fPIE \
	-m64 \
	-march=x86-64 \
	-mno-80387 \
	-mno-mmx \
	-mno-sse \
	-mno-sse2 \
	-mno-red-zone \
	-fPIC \
	-O0

# Internal C preprocessor flags that should not be changed by the user.
override KCPPFLAGS := \
	-Ikernel \
	-I \
	$(KCPPFLAGS) \
	-MMD \
	-MP

override KCXXFLAGS += \
	-g \
	-Wall \
	-Wextra \
	-std=gnu++20 \
	-ffreestanding \
	-fno-stack-protector \
	-fno-stack-check \
	-fno-lto \
	-fPIE \
	-m64 \
	-march=x86-64 \
	-mno-80387 \
	-mno-mmx \
	-mno-sse \
	-mno-sse2 \
	-mno-red-zone \
	-Ikernel/include \
	-fPIC \
	-I. \
	-fno-rtti \
	-fno-exceptions \
	-O0

# Internal linker flags that should not be changed by the user.
override KLDFLAGS += \
	-m elf_x86_64 \
	-nostdlib \
	-z text \
	-z max-page-size=0x1000 \
	-T bootloader/limine/linker.ld

# Internal nasm flags that should not be changed by the user.
override KNASMFLAGS += \
	-g \
	-O0 \
	-Wall \
	-f elf64 

# Use "find" to glob all *.c, *.S, and *.asm files in the tree and obtain the
# object and header dependency file names.
override CFILES := $(shell cd kernel && find -L * -type f -name '*.c')
override CXXFILES := $(shell cd kernel && find -L * -type f -name '*.cpp')
override ASFILES := $(shell cd kernel && find -L * -type f -name '*.S')

override NASMFILES := $(shell cd kernel/ASM/non_abi && find -L * -type f -name '*.asm')
override NASM_OBJS := $(addprefix obj/ASM/non_abi/, $(NASMFILES:.asm=.asm.o))

override OBJ := $(addprefix obj/,$(CFILES:.c=.c.o) $(ASFILES:.S=.S.o) $(CXXFILES:.cpp=.cpp.o))
override HEADER_DEPS := $(addprefix obj/,$(CFILES:.c=.c.d) $(ASFILES:.S=.S.d) $(CXXFILES:.cpp=.cpp.d))


CRTI_FILE := $(addprefix kernel/ASM/abi/global_constructors/, $(shell cd kernel/ASM/abi/global_constructors && find -L * -type f -name crti.asm))
CRTN_FILE := $(addprefix kernel/ASM/abi/global_constructors/, $(shell cd kernel/ASM/abi/global_constructors && find -L * -type f -name crtn.asm))

CRTI_OBJ =  $(addprefix obj/, $(CRTI_FILE:.asm=.asm.o))
CRTN_OBJ =  $(addprefix obj/, $(CRTN_FILE:.asm=.asm.o))

OBJECTS = $(CRTI_OBJ) $(NASM_OBJS) $(OBJ) $(CRTN_OBJ)
#$(info $(NASMFILES))
#$(error $(NASM_OBJS))

# Default target.
.PHONY: all
all: bin/$(KERNEL)

# Link rules for the final kernel executable.
# The magic printf/dd command is used to force the final ELF file type to ET_DYN.
# GNU binutils, for silly reasons, forces the ELF type to ET_EXEC even for
# relocatable PIEs, if the base load address is non-0.
# See https://sourceware.org/bugzilla/show_bug.cgi?id=31795 for more information.
bin/$(KERNEL): bootloader/limine/linker.ld $(OBJECTS)
	mkdir -p "$$(dirname $@)"
	$(KLD) $(OBJECTS) $(KLDFLAGS) -o $@
#printf '\003' | dd of=$@ bs=1 count=1 seek=16 conv=notrunc 2>/dev/null
#$(error $(NASM_OBJS))
# Include header dependencies.
-include $(HEADER_DEPS)

# Compilation rules for *.c files.
obj/%.cpp.o: kernel/%.cpp
	mkdir -p "$$(dirname $@)"
	$(KCC) $(KCXXFLAGS) $(KCPPFLAGS) -c $< -o $@

obj/%.c.o: kernel/%.c
	mkdir -p "$$(dirname $@)"
	$(KCC) $(KCFLAGS) $(KCPPFLAGS) -c $< -o $@

# Compilation rules for *.S files.
obj/%.S.o: kernel/%.S
	mkdir -p "$$(dirname $@)"
	$(KCC) $(KCFLAGS) $(KCPPFLAGS) -c $< -o $@

# Compilation rules for *.asm (nasm) files.
obj/ASM/non_abi/%.asm.o: kernel/ASM/non_abi/%.asm
	mkdir -p "$$(dirname $@)"
	nasm $(KNASMFLAGS) $< -o $@

obj/kernel/ASM/abi/global_constructors/crti.asm.o: kernel/ASM/abi/global_constructors/crti.asm
	mkdir -p "$$(dirname $@)"
	nasm $(KNASMFLAGS) $< -o $@

obj/kernel/ASM/abi/global_constructors/crtn.asm.o: kernel/ASM/abi/global_constructors/crtn.asm
	mkdir -p "$$(dirname $@)"
	nasm $(KNASMFLAGS) $< -o $@

# Remove object files and the final executable.
.PHONY: clean
clean:
	rm -rf bin obj