#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "windows.h"
#include "helpers.h"

#define NOT_DEBUG 1 //true = command line arguments are active

int main(int argc, char * argv[])
{
    BITMAPFILEHEADER bf;
    BITMAPINFO bmi;
    RGBQUAD myColors[256]; // needed because size of bmi.bmiColors is defined as 1 in wingdi.h !!!

    FILE *infile, *outfile;
    DWORD bytes_read = 0, bmpsize, fillindex, nextlinei, linei, i, offset;

    int use2=0, use4=0, use8=0, palout=0, padbytes=0;

    char drive[_MAX_DRIVE];
    char dir[_MAX_DIR];
    char file[_MAX_FNAME];
    char justfile[_MAX_FNAME];
	char ufile[_MAX_FNAME];
    char ext[_MAX_EXT];
    char of_name[_MAX_FNAME+_MAX_EXT];
    unsigned char *databuffer;


	printf("Pokitto BMP to Pokitto bitmap conversion utility\n");

    if (((argc < 3) || (argc > 4)) && NOT_DEBUG)

    {
        print_usage(argv[0]);
        exit(-1);
    }

    if ((strcmp(argv[2], "-2") == 0) && NOT_DEBUG)
    {
        use2 = 1;
    }
    else if ((strcmp(argv[2], "-4") == 0) && NOT_DEBUG)
    {
        use4 = 1;
    }
    else if ((strcmp(argv[2], "-8")) == 0 && NOT_DEBUG)
    {
        use8 = 1;
    }
    else if (NOT_DEBUG)
    {
        print_usage(argv[0]);
        exit(-1);
    }

    if ((argc == 4) && NOT_DEBUG)
    {
        if (strcmp(argv[3], "-p") == 0)
			palout = 1;
		else
		{
			print_usage(argv[0]);
			exit(-1);
        }
    }

    if (NOT_DEBUG) {
    /* split the string to separate elementss */
        _splitpath(argv[1], drive, dir, file, ext);

        strcpy(ufile,file);
        _strupr(ufile);

        strcpy(file,argv[1]);
        printf("file: %s ",file);
        if (strlen(ext)==0) {
            strcpy(justfile,argv[1]); // save a copy of bare filename
        } else {
            printf("strlen file: %d " ,strlen(file));
            memset((void*)justfile,0,_MAX_FNAME);
            memcpy((void*)justfile,(void*)file,strlen(file)-4);
            strcat(justfile,"\0");
            printf("justfile: %s ",justfile);
        }

        if (strlen(ext) == 0)
        {
            strcat(file,".bmp");
        }
    }
    else
    {
        strcpy(file,"test4col.bmp");
        strcpy(justfile, "test4col");
        palout = 1;
        use2 = 1;
        use4 = 0;
        use8 = 0;
    }

    infile = fopen(file, "rb");
    if (!infile)
    {
		printf("Error opening input file %s\n", file);
		exit(-1);
	}

	if (fread(&bf,sizeof(bf),1,infile) == 1)
    {
        bytes_read += sizeof(bf);
    }
	else
	{
		printf("Error reading BMP header\n");
		fclose(infile);
		exit(-1);
	}

    if (fread(&bmi,sizeof(bmi.bmiHeader),1,infile) == 1)
    {
        int c = bmi.bmiHeader.biClrUsed;
        if (c==0) c=256; // from MS BMP specs. 0 means 2^n colors
        bmi.bmiHeader.biClrUsed = c;
        printf("Number of colours used: %d\n", c);
        //fread(&bmi.bmiColors[0],c*4,1,infile);
        fread(&myColors[0],c*4,1,infile);
        bytes_read += sizeof(bmi.bmiHeader)+c*4;
        for (unsigned int j=0; j<bmi.bmiHeader.biClrUsed; j++) {
            printf("Colour: %d",j);
            if (j<10) printf(" ");
            /*R*/
            c=myColors[j].rgbRed;
            printf(" r:%d",c);
            if (c<10) printf("  ");
            else if (c<100) printf(" ");
            printf(" ");
            /*G*/
            c=myColors[j].rgbGreen;
            printf("g:%d",c);
            if (c<10) printf("  ");
            else if (c<100) printf(" ");
            printf(" ");
            /*B*/
            c=myColors[j].rgbBlue;
            printf("b:%d",c);
            if (c<10) printf("  ");
            else if (c<100) printf(" ");
            printf("\n");
        }
    }
	else
	{
		printf("Error reading BMP info\n");
		fclose(infile);
		exit(-1);
	}



	if (bmi.bmiHeader.biBitCount != 8)
	{
		printf("Only 8bpp BMP files are supported\n");
		fclose(infile);
		exit(-1);
	}

	/* Allocate buffer storage */
	bmpsize = bmi.bmiHeader.biWidth * bmi.bmiHeader.biHeight;
	if (bmi.bmiHeader.biWidth%4) {
            padbytes = bmi.bmiHeader.biWidth%4;
            printf("Width is not divisible by 4\n");
            printf("Ignoring %d padding bytes at each line\n", padbytes);
	}

	databuffer = (unsigned char *) malloc(bmpsize);
	if (databuffer == NULL)
	{
		printf("Error allocating temporary data buffer, is image too big?\n");
		fclose(infile);
		exit(-1);
	}

    /* seek to the beginning of the data */
	fseek(infile, bf.bfOffBits, SEEK_SET);

	/* Read data into array */
	int padcounter = bmi.bmiHeader.biWidth+padbytes;
	fillindex = bmpsize - 1;
	i = 0;
	while (i < bmpsize)
    {
		BYTE rgb;

		if (fread(&rgb, sizeof(rgb), 1, infile) != 1)
		{
			printf("error reading BMP data\n");
 		    fclose(infile);
			free(databuffer);
	        exit(-1);
   	    }
		/* Store in color array for the correct type. BMPs are
		   stored in reverse, so save the data backwards */
        if (padbytes) {
            /* there are padding bytes */
            if (padcounter>padbytes) {
                /*not in padding section yet, so store */
                databuffer[fillindex]=rgb;
                fillindex--;
                i++;
            }
            padcounter--;
            if (padcounter==0) padcounter = bmi.bmiHeader.biWidth + padbytes; // reset padvounter at each line
        } else {
            /* no need to worry about padding */
            databuffer[fillindex]=rgb;
            fillindex--;
            i++;
        }

	}

	fclose(infile);

	//if (use555)
	sprintf(of_name,justfile);
	strcat(of_name,".c");

	printf("Outputting c file: %s\n", of_name);
    outfile = fopen(of_name,"w");

	if (outfile == NULL)
	{
		printf("error opening out file %s\n", of_name);
		free(databuffer);
	    exit(-1);
	}

	    if (use8) fprintf (outfile,
			"\n\n/*\n * BMP image as 8bpp (up to 256 color index) data\n");
        else if (use4) fprintf (outfile,
			"\n\n/*\n * BMP image as 4bpp (16 color index) data\n");
        else if (use2) fprintf (outfile,
			"\n\n/*\n * BMP image as 2bpp (4 color) data\n");
		//if (swaprgb)
		//	fprintf (outfile, " * Red and green data swapped\n");
	    fprintf (outfile, " */\n\n");
	    fprintf(outfile,"#include <stdint.h>\n\n");

        /* Palette data */
        fprintf(outfile,"const uint16_t ");
        fprintf(outfile,justfile);
        fprintf(outfile,"_pal[] = {\n");
        unsigned int numcol;
        if (use8) { numcol=256;}
        else if (use4) { numcol=16;}
        else if (use2) { numcol=4;}
        if (bmi.bmiHeader.biClrUsed>numcol) {
                printf("WARNING! \n");
                printf("Your image has %d different colors.\n",(int)bmi.bmiHeader.biClrUsed);
                if (use4) printf("But 4bpp mode only allows 16 different colors in the palette.\n");
                else if (use2) printf("But 2bpp mode only allows 4 different colors in the palette.\n");
                printf("The program will automatically IGNORE any colors used above this limit.\n");
        }
        if (numcol>bmi.bmiHeader.biClrUsed) numcol = bmi.bmiHeader.biClrUsed;
        for (unsigned int c=0;c<numcol;c++) {
            unsigned int r,g,b,o;
            r = myColors[c].rgbRed >> 3; // 5 bits
            g = myColors[c].rgbGreen >> 2; // 6 bits
            b = myColors[c].rgbBlue >> 3; // 5 bits
            o = (r<<11)|(g<<5)|b;
            fprintf(outfile,"%d",o);
            if(c<numcol-1) fprintf(outfile,",");
            else fprintf(outfile,"\n");
        }
        fprintf(outfile,"};\n\n");
		/* Image data */
        fprintf(outfile, "const uint8_t ");
        fprintf(outfile,justfile);
        fprintf(outfile,"[] = {\n%d,%d,\n",(int)bmi.bmiHeader.biWidth,(int)bmi.bmiHeader.biHeight);

	fillindex = 0;
	i = 0;
	linei = bmi.bmiHeader.biWidth - 1;
	nextlinei = 0;
	int entrywidth = 0;
	if (use8) entrywidth = 3;
	else entrywidth = 2;
	int bitcounter=0; // needed for packing bits
	int prevvalue[8]; // needed for packing bits

	while (i < bmpsize)
	{
		offset = nextlinei + linei;

		/** OUTPUT DATA tO FILE **/

        unsigned int temp=fillindex;
        if (use8) {
            if (databuffer[offset]<10) fprintf (outfile, "0%d", (unsigned char)databuffer[offset]);
            else fprintf (outfile, "%d", databuffer[offset]);
            fillindex++;
        } else if (use4) {
            if (bitcounter) {
                    fprintf (outfile, "%d", (unsigned char)(prevvalue[0]<<4 | databuffer[offset]));
                    fillindex++;
            } else {
                    prevvalue[0] = databuffer[offset];
            }
            bitcounter = !bitcounter;
        } else if (use2) {
            unsigned char outputbyte;
            switch(bitcounter) {
            case 0:
                prevvalue[0] = databuffer[offset];
                bitcounter +=2;
                break;
            case 2:
                prevvalue[1] = databuffer[offset];
                bitcounter +=2;
                break;
            case 4:
                prevvalue[2] = databuffer[offset];
                bitcounter +=2;
                break;
            default:
                outputbyte = (prevvalue[0] << 6); //pixel 0 is highest half nibble..
                outputbyte |= (prevvalue[1] << 4); //pixel 1
                outputbyte |= (prevvalue[2] << 2); //pixel 2
                outputbyte |= databuffer[offset]; //pixel 3
                fprintf (outfile, "%d", outputbyte);
                fillindex ++;
                bitcounter = 0;
            }

        }
        if (temp!=fillindex) {
            /** A new entry was written to file **/
            if (fillindex == bmi.bmiHeader.biWidth) //line change
            {
                fprintf (outfile, ",\n");
                fillindex = 0;
            }
            else {
                fprintf (outfile, ","); // add comma after entry
            }
        }
		i++;

		if (linei == 0)
		{
			linei = bmi.bmiHeader.biWidth;
			nextlinei += bmi.bmiHeader.biWidth;
		}
		linei--;
	}

    fprintf (outfile, "\n};");
	free(databuffer);
	fclose(outfile);

    return 0;
}
