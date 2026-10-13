#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "desktop.h"
static void expect_text(unsigned short *cells, int x, int y, const char *text)
{
    for (size_t i = 0; i < strlen(text); i++) assert((cells[y * WIDTH + x + i] & 0xff) == (unsigned char)text[i]);
}
int main(void)
{
    unsigned short guarded[WIDTH * HEIGHT + 2];
    for (int i = 0; i < WIDTH * HEIGHT + 2; i++) guarded[i] = 0xdead;
    desktop_render(guarded + 1);
    assert(guarded[0] == 0xdead && guarded[WIDTH * HEIGHT + 1] == 0xdead);
    expect_text(guarded + 1, 2, 0, "Nivo OS");
    expect_text(guarded + 1, 19, 13, "Ein ruhiger Ort fuer neue Ideen.");
    expect_text(guarded + 1, 24, 23, "[ Finder ]  [ Terminal ]  [ Info ]");
    assert(guarded[WIDTH * HEIGHT] == 0x1f20);
    for (int i = 1; i <= WIDTH * HEIGHT; i++) assert(guarded[i] != 0xdead);
    puts("Desktop tests passed (content, boundaries, complete initialization)");
}
