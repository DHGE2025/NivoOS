CC = gcc
CFLAGS = -m32 -std=c11 -ffreestanding -fno-pie -fno-stack-protector -Wall -Wextra -Werror -O2
.PHONY: all test run clean
all: build/nivo.iso
build:
	mkdir -p build
build/boot.o: src/boot.S | build
	$(CC) -m32 -c $< -o $@
build/kernel.o: src/kernel.c src/desktop.h | build
	$(CC) $(CFLAGS) -c $< -o $@
build/desktop.o: src/desktop.c src/desktop.h | build
	$(CC) $(CFLAGS) -c $< -o $@
build/kernel.elf: build/boot.o build/kernel.o build/desktop.o src/linker.ld
	ld -m elf_i386 -T src/linker.ld -o $@ build/boot.o build/kernel.o build/desktop.o
	grub-file --is-x86-multiboot $@
build/nivo.iso: build/kernel.elf
	mkdir -p build/iso/boot/grub
	cp $< build/iso/boot/kernel.elf
	printf 'set timeout=0\nset default=0\nmenuentry "Nivo OS" {\n multiboot /boot/kernel.elf\n boot\n}\n' > build/iso/boot/grub/grub.cfg
	grub-mkrescue -o $@ build/iso
build/desktop_test: tests/desktop_test.c src/desktop.c src/desktop.h | build
	$(CC) -std=c11 -Wall -Wextra -Werror -Isrc tests/desktop_test.c src/desktop.c -o $@
test: all build/desktop_test
	./build/desktop_test
	python3 -m unittest discover -s tests -p 'test_*.py'
	python3 scripts/run.py
run: all
	python3 scripts/run.py
clean:
	rm -rf build
