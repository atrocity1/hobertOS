all:
	nasm -f elf32 boot/boot.asm -o boot/boot.o
	gcc -m32 -ffreestanding -c kernel_c/kernel.c -o kernel_c/kernel.o -std=gnu99 -O2 -Wall -Wextra
	g++ -m32 -ffreestanding -fno-exceptions -fno-rtti -c cpp/snake.cpp -o cpp/snake.o
	ld -m elf_i386 -T linker.ld -o kernel.bin boot/boot.o kernel_c/kernel.o cpp/snake.o
	qemu-system-i386 -kernel kernel.bin

kernel_c/kernel.o: kernel_c/kernel.c
	gcc -m32 -ffreestanding -c kernel_c/kernel.c -o kernel_c/kernel.o

cpp/snake.o: cpp/snake.cpp
	g++ -m32 -ffreestanding -fno-exceptions -fno-rtti -c cpp/snake.cpp -o cpp/snake.o

kernel.bin: kernel_c/kernel.o cpp/snake.o boot/boot.o
	ld -m elf_i386 -T linker.ld boot/boot.o kernel_c/kernel.o cpp/snake.o -o kernel.bin