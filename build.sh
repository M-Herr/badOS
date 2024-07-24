(cd src/bootloader; nasm -o boot boot.asm)
boot_result=$?

(cd src/kernel; make)
make_result=$?

echo Make Result: $make_result

if [ "$boot_result" = "0" ] && [ "$make_result" = "0" ]

then
    cp src/bootloader/boot ./os.img
    cat src/kernel/badOS >> os.img
    fsize=$(wc -c < os.img)
    sectors=$(($fsize/512))

    echo "Build finished successfully"
    echo "ALERT: Adjust boot sector to load $sectors sectors"
else
    result=`expr $boot_result + $make_result`
    echo "Build failed with error code $result. See output for more info."
fi