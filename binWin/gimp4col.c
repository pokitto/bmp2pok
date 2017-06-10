

/*
 * BMP image as 2bpp (4 color) data
 */

#include <stdint.h>

const uint16_t gimp4col_pal[] = {
0,63519,2047,65535
};

const uint8_t gimp4col[] = {
40,40,
0x33,0x33,0xCC,0xCC,0xC0,0x09,0x99,0x94,0x84,0x84,
0xCC,0xCC,0xCC,0xCC,0xC0,0x06,0x66,0x64,0x84,0x84,
0x33,0x33,0xCC,0xCC,0xC0,0x09,0x99,0x94,0x84,0x84,
0xCC,0xCC,0xCC,0xCC,0xC0,0x06,0x66,0x64,0x84,0x84,
0x33,0x33,0xCC,0xCC,0xC0,0x09,0x99,0x94,0x84,0x84,
0xCC,0xCC,0xCC,0xCC,0xC0,0x06,0x66,0x64,0x84,0x84,
0x33,0x33,0xCC,0xCC,0xC0,0x09,0x99,0x94,0x84,0x84,
0xCC,0xCC,0xCC,0xCC,0xC0,0x06,0x66,0x64,0x84,0x84,
0x00,0x00,0xFF,0xFF,0xC0,0x00,0x00,0x05,0x55,0x54,
0xFF,0xFF,0xFF,0xF0,0xC0,0x0A,0xAA,0xA5,0x55,0x04,
0x00,0x00,0xFF,0xC3,0xC0,0x00,0x00,0x05,0x54,0x14,
0xFF,0xFF,0xFF,0x0F,0xC0,0x05,0x55,0x55,0x50,0x54,
0x00,0x00,0xFC,0x3F,0xC0,0x00,0x00,0x05,0x41,0x54,
0xFF,0xFF,0xF0,0xFF,0xC0,0x0A,0xAA,0xA5,0x05,0x54,
0x00,0x00,0xC3,0xFF,0xC0,0x00,0x00,0x04,0x15,0x54,
0xFF,0xFF,0xFF,0xFF,0xC0,0x05,0x55,0x55,0x55,0x54,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xC0,0xC0,0xC0,0xC0,0xFC,0xC0,0x0C,0x0C,0x03,0x03,
0xF3,0xC3,0xCF,0xF3,0xFC,0xCC,0xCC,0xCC,0xFF,0x0F,
0xF3,0xCF,0xF0,0xF3,0xFC,0xCC,0xCC,0x0C,0xC3,0x3F,
0xF3,0xC0,0xC0,0xF3,0xFC,0xCF,0xCC,0xCC,0x03,0x03,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0x66,0x66,0x84,0x84,0x80,0x03,0x33,0x3C,0xCC,0xCC,
0x99,0x99,0x84,0x84,0x80,0x0C,0xCC,0xCC,0xCC,0xCC,
0x66,0x66,0x84,0x84,0x80,0x03,0x33,0x3C,0xCC,0xCC,
0x99,0x99,0x84,0x84,0x80,0x0C,0xCC,0xCC,0xCC,0xCC,
0x66,0x66,0x84,0x84,0x80,0x03,0x33,0x3C,0xCC,0xCC,
0x99,0x99,0x84,0x84,0x80,0x0C,0xCC,0xCC,0xCC,0xCC,
0x66,0x66,0x84,0x84,0x80,0x03,0x33,0x3C,0xCC,0xCC,
0x99,0x99,0x84,0x84,0x80,0x0C,0xCC,0xCC,0xCC,0xCC,
0x00,0x00,0xAA,0xAA,0x80,0x00,0x00,0x0F,0xFF,0xFC,
0x55,0x55,0xAA,0xA5,0x80,0x0F,0xFF,0xFF,0xFF,0x0C,
0x00,0x00,0xAA,0x96,0x80,0x00,0x00,0x0F,0xFC,0x3C,
0xAA,0xAA,0xAA,0x5A,0x80,0x0F,0xFF,0xFF,0xF0,0xFC,
0x00,0x00,0xA9,0x6A,0x80,0x00,0x00,0x0F,0xC3,0xFC,
0x55,0x55,0xA5,0xAA,0x80,0x0F,0xFF,0xFF,0x0F,0xFC,
0x00,0x00,0x96,0xAA,0x80,0x00,0x00,0x0C,0x3F,0xFC,
0xAA,0xAA,0xAA,0xAA,0x80,0x0F,0xFF,0xFF,0xFF,0xFC,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
};