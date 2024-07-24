
if test -f os.img; then
    qemu-system-x86_64 -drive file=os.img,format=raw -s -S &
    gdb -ex "target remote localhost:1234" -ex "symbol-file src/kernel/badOS.elf"
else
    sh build.sh

    qemu-system-x86_64 -drive file=os.img,format=raw -s -S &
    gdb -ex "target remote localhost:1234" -ex "symbol-file src/kernel/badOS.elf"
fi

