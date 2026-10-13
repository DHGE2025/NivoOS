#include "desktop.h"
static void label(unsigned short *cells, int x, int y, const char *text, unsigned char color)
{
    while (*text && x < WIDTH) cells[y * WIDTH + x++] = ((unsigned short)color << 8) | (unsigned char)*text++;
}
void desktop_render(unsigned short *cells)
{
    for (int y = 0; y < HEIGHT; y++)
        for (int x = 0; x < WIDTH; x++)
            cells[y * WIDTH + x] = ((y == 0 || y == 23 ? 0x70 : 0x1f) << 8) | ' ';
    label(cells, 2, 0, "Nivo OS     Desktop", 0x70);
    for (int y = 6; y < 18; y++)
        for (int x = 14; x < 66; x++) cells[y * WIDTH + x] = 0x7020;
    label(cells, 16, 7, "o o o                 Willkommen", 0x70);
    label(cells, 19, 11, "Nivo OS", 0x70);
    label(cells, 19, 13, "Ein ruhiger Ort fuer neue Ideen.", 0x70);
    label(cells, 19, 15, "Erster bootfaehiger Prototyp", 0x70);
    label(cells, 24, 23, "[ Finder ]  [ Terminal ]  [ Info ]", 0x70);
}
