#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "helpers.h"

#define _MAX_DRIVE	3
#define _MAX_DIR	256
#define _MAX_FNAME	256
#define _MAX_EXT	256

#include <ctype.h>

char* _strupr( char* s )
  {
  char* p = s;
  while (*p = toupper( *p )) p++;
  return s;
  }

typedef struct tagRGBQUAD {
  uint8_t rgbBlue;
  uint8_t rgbGreen;
  uint8_t rgbRed;
  uint8_t rgbReserved;
} RGBQUAD;

typedef struct tagBITMAPFILEHEADER {
  int16_t  bfType;
  int32_t  bfSize;
  int16_t  bfReserved1;
  int16_t  bfReserved2;
  int32_t  bfOffBits;
} __attribute__((packed)) BITMAPFILEHEADER, *PBITMAPFILEHEADER;

typedef struct tagBITMAPINFOHEADER {
  int32_t biSize;
  int32_t  biWidth;
  int32_t  biHeight;
  int16_t  biPlanes;
  int16_t  biBitCount;
  int32_t biCompression;
  int32_t biSizeImage;
  int32_t biXPelsPerMeter;
  int32_t  biYPelsPerMeter;
  int32_t biClrUsed;
  int32_t biClrImportant;
} __attribute__((packed)) BITMAPINFOHEADER, *PBITMAPINFOHEADER;

typedef struct tagBITMAPINFO {
  BITMAPINFOHEADER bmiHeader;
  RGBQUAD          bmiColors[1];
} __attribute__((packed)) BITMAPINFO, *PBITMAPINFO;

void _splitpath (
   const char *path,  // Path Input
   char *drive,       // Drive     : Output
   char *dir,         // Directory : Output
   char *fname,       // Filename  : Output
   char *ext          // Extension : Output
);

/* implementation of the _splitpath runtime library function with ANSI character strings */
 void _splitpath(const char* path, char* drv, char* dir, char* name, char* ext)
 {
     const char* end; /* end of processed string */
     const char* p;   /* search pointer */
     const char* s;   /* copy pointer */

     /* extract drive name */
     if (path[0] && path[1]==':') {
         if (drv) {
             *drv++ = *path++;
             *drv++ = *path++;
             *drv = '\0';
         }
     } else if (drv)
        *drv = '\0';

     /* search for end of string or stream separator */
     for(end=path; *end && *end!=':'; )
         end++;

     /* search for begin of file extension */
     for(p=end; p>path && *--p!='\\' && *p!='/'; )
         if (*p == '.') {
             end = p;
             break;
         }

     if (ext)
         for(s=end; (*ext=*s++); )
             ext++;

    /* search for end of directory name */
     for(p=end; p>path; )
         if (*--p=='\\' || *p=='/') {
            p++;
            break;
        }

     if (name) {
         for(s=p; s<end; )
             *name++ = *s++;

         *name = '\0';
     }

     if (dir) {
         for(s=path; s<p; )
             *dir++ = *s++;

         *dir = '\0';
     }
 }


RGBQUAD myColors[257];


#include "common.cpp" //common code for windows & linux versions
