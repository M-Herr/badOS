# Nuke built-in rules and variables.
override MAKEFLAGS += -rR

override KERNEL := badOS

CC = clang
NC = nasm
LD = ld.lld

CFLAGS += \
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
	-mno-red-zone

CPPFLAGS += \
	-g \
	-trigraphs \
	-fno-builtin \
	-O2 \
	-Iinclude \
	-c \
	-ffreestanding \
	-target x86_64-none-elf \
	-std=gnu++20

LDFLAGS += \
	-Ttext 0x8200 \
	-nostdlib

LDFLAGS_BIN = ${LDFLAGS} --oformat binary

ASMFLAGS += \
	-Wall \
	-f elf64

BUILD_DIR = build/x86_64

all: $(KERNEL) $(KERNEL).elf

CPP_SOURCE := $(shell find . -name '*.cpp')
$(info $(CPP_SOURCE))
CPP_OBJECTS := $(patsubst %.cpp, $(BUILD_DIR)/%.o, $(CPP_SOURCE))

ASM_SOURCE := $(shell find entry -name '*.asm')
ASM_OBJECTS := $(patsubst entry/%.asm, $(BUILD_DIR)/entry/%.o, $(ASM_SOURCE))

CRTI_OBJ = crti.o
CRTN_OBJ = crtn.o

ALL_OBJECTS = $(CRTI_OBJ) $(ASM_OBJECTS) $(CPP_OBJECTS)  $(CRTN_OBJ)

$(KERNEL): $(ALL_OBJECTS)
	$(LD) -o $@ $(LDFLAGS_BIN) $^

$(KERNEL).elf: $(ALL_OBJECTS)
	$(LD) -o $@ $(LDFLAGS) $^

$(CRTI_OBJ): global_constructors/crti.asm
	mkdir -p $(dir $@)
	$(NC) $(ASMFLAGS) $< -o $@

$(CRTN_OBJ): global_constructors/crtn.asm
	mkdir -p $(dir $@)
	$(NC) $(ASMFLAGS) $< -o $@

$(BUILD_DIR)/entry/%.o: entry/%.asm
	mkdir -p $(dir $@)
	$(NC) $(ASMFLAGS) $< -o $@

$(BUILD_DIR)/%.o: %.cpp
	mkdir -p $(dir $@)
	$(CC) $(CPPFLAGS) $< -o $@

clean:
	rm -f $(KERNEL) $(KERNEL).elf $(BUILD_DIR)/**/*.o

.PHONY: all clean
