#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "windows.h"
#include "helpers.h"


void add_underscores(char *name)
{
    while(*name)
    {
        if(isspace((int)*name))
            *name = '_';
        name++;
    }
}

void print_usage(char *filename)
{
    printf("%s: usage:\n\t%s infile -2/-4 [-p]\n"
                   "where\n\tinfile is an 8bpp Microsoft(tm) BMP file\n"
                   "\t-2 will generate 2-bit colors\n"
                   "\t-4 will generate 4-bit colors\n"
                   "\t-p will include palette in output\n"
                   ,
            filename, filename);
}
