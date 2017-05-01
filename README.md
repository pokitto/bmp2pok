# bmp2pok
BMP to Pokitto graphics converter
Copyright 2017 Pokitto Oy Finland
(see LICENSE)

This program converts an 8-bit BMP file (256 indexed colors) to a Pokitto-compatible .C file

Program will warn about using too many colors in the source image (>16 in 4 bit mode and >4 colors in 2-bit mode)

USAGE

bmp2pok.exe: usage:
        bmp2pok.exe infile -2/-4 
where
        infile is an 8bpp Microsoft(tm) BMP file
        -2 will generate 2-bit colors
        -4 will generate 4-bit colors
        
OUTPUT

.C file with palette in 565 (5 bits Red, 6 bits Green, 5 bits Blue) format and the bitmap as bytes that each 
contain either 2 pixels (4 bit mode) or 4 pixels (2 bit mode)

WARNING

Program may contain bugs still, use at your own risk & please fix if found

= Pokitto =
Jonne Valola
