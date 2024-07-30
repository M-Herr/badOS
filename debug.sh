
if test -f image.iso; then
    qemu-system-x86_64 -cdrom image.iso -s -S &
    gdb -ex "target remote localhost:1234" -ex "symbol-file bin/bados"
else
    sh build.sh

    qemu-system-x86_64 -cdrom image.iso -s -S &
    gdb -ex "target remote localhost:1234" -ex "symbol-file bin/bados"
fi


