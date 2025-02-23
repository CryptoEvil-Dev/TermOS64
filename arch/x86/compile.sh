mkdir -p build
cd boot
nasm -f bin Haron.asm -o bootloader.bin
mv ./bootloader.bin ./../build
cd ..
cd kernel
gcc kernel.c ./include/impl/disk.c -o kernel.bin -m32 -nostdlib -ffreestanding 
mv ./kernel.bin ./../build
cd ../build
cat bootloader.bin kernel.bin > os.bin