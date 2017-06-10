

/*
 * BMP image as 4bpp (16 color index) data
 */

#include <stdint.h>

const uint16_t gimp16col_pal[] = {
0,63519,64768,2016,2047,65440,65535
};

const uint8_t gimp16col[] = {
40,40,
6,6,6,6,96,96,96,96,96,0,0,65,65,65,65,16,64,16,64,16,
96,96,96,96,96,96,96,96,96,0,0,20,20,20,20,16,64,16,64,16,
6,6,6,6,96,96,96,96,96,0,0,65,65,65,65,16,64,16,64,16,
96,96,96,96,96,96,96,96,96,0,0,20,20,20,20,16,64,16,64,16,
6,6,6,6,96,96,96,96,96,0,0,65,65,65,65,16,64,16,64,16,
96,96,96,96,96,96,96,96,96,0,0,20,20,20,20,16,64,16,64,16,
6,6,6,6,96,96,96,96,96,0,0,65,65,65,65,16,64,16,64,16,
96,96,96,96,96,96,96,96,96,0,0,20,20,20,20,16,64,16,64,16,
0,0,0,0,102,102,102,102,96,0,0,0,0,0,0,17,17,17,17,16,
102,102,102,102,102,102,102,0,96,0,0,68,68,68,68,17,17,17,0,16,
0,0,0,0,102,102,96,6,96,0,0,0,0,0,0,17,17,16,1,16,
102,102,102,102,102,102,0,102,96,0,0,17,17,17,17,17,17,0,17,16,
0,0,0,0,102,96,6,102,96,0,0,0,0,0,0,17,16,1,17,16,
102,102,102,102,102,0,102,102,96,0,0,68,68,68,68,17,0,17,17,16,
0,0,0,0,96,6,102,102,96,0,0,0,0,0,0,16,1,17,17,16,
102,102,102,102,102,102,102,102,96,0,0,17,17,17,17,17,17,17,17,16,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
85,85,85,85,85,85,85,85,85,85,85,85,85,85,85,85,85,85,85,85,
80,0,80,0,80,0,80,0,85,80,80,0,0,80,0,80,0,5,0,5,
85,5,80,5,80,85,85,5,85,80,80,80,80,80,80,80,85,85,0,85,
85,5,80,85,85,0,85,5,85,80,80,80,80,80,0,80,80,5,5,85,
85,5,80,0,80,0,85,5,85,80,80,85,80,80,80,80,0,5,0,5,
85,85,85,85,85,85,85,85,85,85,85,85,85,85,85,85,85,85,85,85,
20,20,20,20,64,16,64,16,64,0,0,50,50,50,50,32,48,32,48,32,
65,65,65,65,64,16,64,16,64,0,0,35,35,35,35,32,48,32,48,32,
20,20,20,20,64,16,64,16,64,0,0,50,50,50,50,32,48,32,48,32,
65,65,65,65,64,16,64,16,64,0,0,35,35,35,35,32,48,32,48,32,
20,20,20,20,64,16,64,16,64,0,0,50,50,50,50,32,48,32,48,32,
65,65,65,65,64,16,64,16,64,0,0,35,35,35,35,32,48,32,48,32,
20,20,20,20,64,16,64,16,64,0,0,50,50,50,50,32,48,32,48,32,
65,65,65,65,64,16,64,16,64,0,0,35,35,35,35,32,48,32,48,32,
0,0,0,0,68,68,68,68,64,0,0,0,0,0,0,34,34,34,34,32,
17,17,17,17,68,68,68,17,64,0,0,51,51,51,51,34,34,34,51,32,
0,0,0,0,68,68,65,20,64,0,0,0,0,0,0,34,34,35,50,32,
68,68,68,68,68,68,17,68,64,0,0,34,34,34,34,34,34,51,34,32,
0,0,0,0,68,65,20,68,64,0,0,0,0,0,0,34,35,50,34,32,
17,17,17,17,68,17,68,68,64,0,0,51,51,51,51,34,51,34,34,32,
0,0,0,0,65,20,68,68,64,0,0,0,0,0,0,35,50,34,34,32,
68,68,68,68,68,68,68,68,64,0,0,34,34,34,34,34,34,34,34,32,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,

};