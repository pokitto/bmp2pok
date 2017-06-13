

/*
 * BMP image as 4bpp (16 color index) data
 */

#include <stdint.h>

const uint16_t gimp2col_pal[] = {
65535,0
};

const uint8_t gimp2col[] = {
64,40,
0x11,0x11,0x11,0x11,0x11,0x11,0x10,0x10,0x10,0x10,0x01,0x01,0x01,0x01,0x01,0x11,0x11,0x10,0x10,0x10,0x10,0x01,0x01,0x01,0x01,0x01,0x11,0x11,0x11,0x11,0x11,0x11,
0x11,0x11,0x11,0x11,0x11,0x11,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x11,0x11,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x11,0x11,0x11,0x11,0x11,0x11,
0x11,0x11,0x11,0x11,0x11,0x11,0x10,0x10,0x10,0x10,0x01,0x01,0x01,0x01,0x01,0x11,0x11,0x10,0x10,0x10,0x10,0x01,0x01,0x01,0x01,0x01,0x11,0x11,0x11,0x11,0x11,0x11,
0x11,0x11,0x11,0x11,0x11,0x11,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x11,0x11,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x11,0x11,0x11,0x11,0x11,0x11,
0x11,0x11,0x11,0x11,0x11,0x11,0x10,0x10,0x10,0x10,0x01,0x01,0x01,0x01,0x01,0x11,0x11,0x10,0x10,0x10,0x10,0x01,0x01,0x01,0x01,0x01,0x11,0x11,0x11,0x11,0x11,0x11,
0x11,0x11,0x11,0x11,0x11,0x11,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x11,0x11,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x11,0x11,0x11,0x11,0x11,0x11,
0x11,0x11,0x11,0x11,0x11,0x11,0x10,0x10,0x10,0x10,0x01,0x01,0x01,0x01,0x01,0x11,0x11,0x10,0x10,0x10,0x10,0x01,0x01,0x01,0x01,0x01,0x11,0x11,0x11,0x11,0x11,0x11,
0x11,0x11,0x11,0x11,0x11,0x11,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x11,0x11,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x11,0x11,0x11,0x11,0x11,0x11,
0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x00,0x00,0x00,0x00,0x01,0x11,0x11,0x11,0x11,0x11,0x11,0x00,0x00,0x00,0x00,0x01,0x11,0x11,0x11,0x11,0x11,0x11,
0x11,0x11,0x11,0x11,0x11,0x11,0x00,0x00,0x00,0x00,0x00,0x01,0x11,0x00,0x01,0x11,0x11,0x00,0x00,0x00,0x00,0x00,0x01,0x11,0x00,0x01,0x11,0x11,0x11,0x11,0x11,0x11,
0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x01,0x01,0x01,0x01,0x01,0x11,0x11,0x11,0x11,0x11,0x11,0x01,0x01,0x01,0x01,0x01,0x11,0x11,0x11,0x11,0x11,0x11,
0x11,0x11,0x11,0x11,0x11,0x11,0x00,0x00,0x00,0x00,0x00,0x11,0x11,0x10,0x01,0x11,0x11,0x00,0x00,0x00,0x00,0x00,0x11,0x11,0x10,0x01,0x11,0x11,0x11,0x11,0x11,0x11,
0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x00,0x01,0x11,0x00,0x01,0x11,0x11,0x11,0x11,0x11,0x11,0x00,0x01,0x11,0x00,0x01,0x11,0x11,0x11,0x11,0x11,0x11,
0x11,0x11,0x11,0x11,0x11,0x11,0x00,0x00,0x00,0x00,0x00,0x11,0x11,0x10,0x01,0x11,0x11,0x00,0x00,0x00,0x00,0x00,0x11,0x11,0x10,0x01,0x11,0x11,0x11,0x11,0x11,0x11,
0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x01,0x10,0x00,0x11,0x01,0x11,0x11,0x11,0x11,0x11,0x11,0x01,0x10,0x00,0x11,0x01,0x11,0x11,0x11,0x11,0x11,0x11,
0x11,0x11,0x11,0x11,0x11,0x11,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x11,0x11,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x11,0x11,0x11,0x11,0x11,0x11,
0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x11,
0x11,0x11,0x11,0x11,0x11,0x11,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x11,0x11,0x11,0x11,0x11,0x11,
0x11,0x11,0x11,0x11,0x11,0x11,0x01,0x11,0x01,0x11,0x01,0x11,0x01,0x11,0x00,0x01,0x01,0x11,0x11,0x01,0x11,0x01,0x11,0x10,0x11,0x10,0x11,0x11,0x11,0x11,0x11,0x11,
0x11,0x11,0x11,0x11,0x11,0x11,0x00,0x10,0x01,0x10,0x01,0x00,0x00,0x10,0x00,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x00,0x00,0x11,0x00,0x11,0x11,0x11,0x11,0x11,0x11,
0x11,0x11,0x11,0x11,0x11,0x11,0x00,0x10,0x01,0x00,0x00,0x11,0x00,0x10,0x00,0x01,0x01,0x01,0x01,0x01,0x11,0x01,0x01,0x10,0x10,0x00,0x11,0x11,0x11,0x11,0x11,0x11,
0x11,0x11,0x11,0x11,0x11,0x11,0x00,0x10,0x01,0x11,0x01,0x11,0x00,0x10,0x00,0x01,0x01,0x00,0x01,0x01,0x01,0x01,0x11,0x10,0x11,0x10,0x11,0x11,0x11,0x11,0x11,0x11,
0x11,0x11,0x11,0x11,0x11,0x11,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x11,0x11,0x11,0x11,0x11,0x11,
0x11,0x11,0x11,0x11,0x11,0x11,0x10,0x10,0x10,0x10,0x01,0x01,0x01,0x01,0x01,0x11,0x11,0x10,0x10,0x10,0x10,0x01,0x01,0x01,0x01,0x01,0x11,0x11,0x11,0x11,0x11,0x11,
0x11,0x11,0x11,0x11,0x11,0x11,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x11,0x11,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x11,0x11,0x11,0x11,0x11,0x11,
0x11,0x11,0x11,0x11,0x11,0x11,0x10,0x10,0x10,0x10,0x01,0x01,0x01,0x01,0x01,0x11,0x11,0x10,0x10,0x10,0x10,0x01,0x01,0x01,0x01,0x01,0x11,0x11,0x11,0x11,0x11,0x11,
0x11,0x11,0x11,0x11,0x11,0x11,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x11,0x11,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x11,0x11,0x11,0x11,0x11,0x11,
0x11,0x11,0x11,0x11,0x11,0x11,0x10,0x10,0x10,0x10,0x01,0x01,0x01,0x01,0x01,0x11,0x11,0x10,0x10,0x10,0x10,0x01,0x01,0x01,0x01,0x01,0x11,0x11,0x11,0x11,0x11,0x11,
0x11,0x11,0x11,0x11,0x11,0x11,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x11,0x11,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x11,0x11,0x11,0x11,0x11,0x11,
0x11,0x11,0x11,0x11,0x11,0x11,0x10,0x10,0x10,0x10,0x01,0x01,0x01,0x01,0x01,0x11,0x11,0x10,0x10,0x10,0x10,0x01,0x01,0x01,0x01,0x01,0x11,0x11,0x11,0x11,0x11,0x11,
0x11,0x11,0x11,0x11,0x11,0x11,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x11,0x11,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x11,0x11,0x11,0x11,0x11,0x11,
0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x00,0x00,0x00,0x00,0x01,0x11,0x11,0x11,0x11,0x11,0x11,0x00,0x00,0x00,0x00,0x01,0x11,0x11,0x11,0x11,0x11,0x11,
0x11,0x11,0x11,0x11,0x11,0x11,0x00,0x00,0x00,0x00,0x00,0x01,0x11,0x00,0x01,0x11,0x11,0x00,0x00,0x00,0x00,0x00,0x01,0x11,0x00,0x01,0x11,0x11,0x11,0x11,0x11,0x11,
0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x01,0x01,0x01,0x01,0x01,0x11,0x11,0x11,0x11,0x11,0x11,0x01,0x01,0x01,0x01,0x01,0x11,0x11,0x11,0x11,0x11,0x11,
0x11,0x11,0x11,0x11,0x11,0x11,0x00,0x00,0x00,0x00,0x00,0x11,0x11,0x10,0x01,0x11,0x11,0x00,0x00,0x00,0x00,0x00,0x11,0x11,0x10,0x01,0x11,0x11,0x11,0x11,0x11,0x11,
0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x00,0x01,0x11,0x00,0x01,0x11,0x11,0x11,0x11,0x11,0x11,0x00,0x01,0x11,0x00,0x01,0x11,0x11,0x11,0x11,0x11,0x11,
0x11,0x11,0x11,0x11,0x11,0x11,0x00,0x00,0x00,0x00,0x00,0x11,0x11,0x10,0x01,0x11,0x11,0x00,0x00,0x00,0x00,0x00,0x11,0x11,0x10,0x01,0x11,0x11,0x11,0x11,0x11,0x11,
0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x01,0x10,0x00,0x11,0x01,0x11,0x11,0x11,0x11,0x11,0x11,0x01,0x10,0x00,0x11,0x01,0x11,0x11,0x11,0x11,0x11,0x11,
0x11,0x11,0x11,0x11,0x11,0x11,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x11,0x11,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x11,0x11,0x11,0x11,0x11,0x11,
0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x11,
};