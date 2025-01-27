mkdir -p ./build

nasm -f bin TermOS.asm -o TermOS

gcc -c main.c -o kernel
objcopy -O binary kernel kernel.bin

cat TermOS kernel.bin > OS.bin
rm kernel.bin
mv OS.bin ./build
mv kernel ./build
touch ./build/run.sh
echo "qemu-system-x86_64 -hda OS.bin" > ./build/run.sh
sudo chmod +x ./build/run.sh
