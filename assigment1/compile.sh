gcc -std=gnu99 -c osdev.c -o osdev.o -fno-stack-protector
gcc -std=gnu99 -c output.c -o output.o -fno-stack-protector
gcc -std=gnu99 -c thread.c -o thread.o -fno-stack-protector
gcc -std=gnu99 -c scheduler.c -o scheduler.o -fno-stack-protector
as --32 memos-2.s -o memos-2.o
as --32 switch_thread.s -o switch_thread.o
ld -T memos-2.ld switch_thread.o memos-2.o osdev.o output.o thread.o scheduler.o -o memos-2
qemu-system-i386 -kernel memos-2
