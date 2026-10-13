#include "desktop.h"
static void outb(unsigned short port, unsigned char value)
{
    __asm__ volatile ("outb %0, %1" : : "a"(value), "Nd"(port));
}
static unsigned char inb(unsigned short port)
{
    unsigned char value;
    __asm__ volatile ("inb %1, %0" : "=a"(value) : "Nd"(port));
    return value;
}
static void serial(const char *text)
{
    while (*text) {
        while (!(inb(0x3fd) & 0x20)) {}
        outb(0x3f8, *text++);
    }
}
void kernel_main(void)
{
    outb(0x3f9, 0);
    outb(0x3fb, 0x80);
    outb(0x3f8, 3);
    outb(0x3f9, 0);
    outb(0x3fb, 3);
    outb(0x3fa, 0xc7);
    outb(0x3fc, 0x0b);
    desktop_render((unsigned short *)0xb8000);
    serial("Nivo OS: boot OK\nDesktop: Willkommen | Finder | Terminal | Info\n");
    /* shortcut: QEMU smoke boot exits; add an event loop when input is implemented. */
    outb(0xf4, 0x10);
}
