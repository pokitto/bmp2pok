

/*
 * BMP image as 4bpp (16 color index) data
 */

#include <stdint.h>

const uint16_t ball_pal[] = {
4195,16678,12717,19017,33382,13092,53801,29580,23545,54245,33972,27973,54611,28185,57003,57210
};

const uint8_t ball[] = {
12,12,
0x66,0x66,0xFF,0xFF,0x66,0x66,
0x66,0x66,0x66,0x66,0x66,0x66,
0x66,0x66,0x00,0x06,0x66,0x66,
0x66,0x60,0x02,0x22,0x66,0x66,
0x66,0x00,0x28,0x88,0x36,0x66,
0x66,0x02,0x88,0xAA,0x83,0x66,
0x66,0x02,0x8A,0xDD,0x83,0x66,
0x66,0x62,0x8A,0xDF,0x83,0x66,
0x66,0x66,0x38,0x88,0x36,0x66,
0x66,0x66,0x63,0x33,0x66,0x66,
0x66,0x66,0x66,0x66,0x66,0x66,
0x66,0x66,0x66,0x66,0x66,0x66,
};