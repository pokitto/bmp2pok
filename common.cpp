#define NOT_DEBUG 1 //true = command line arguments are active

int main(int argc, char * argv[])
{
    BITMAPFILEHEADER bf;
    BITMAPINFO bmi;
    RGBQUAD myColors[256]; // needed because size of bmi.bmiColors is defined as 1 in wingdi.h !!!

    FILE *infile, *outfile;
    uint32_t bytes_read = 0, bmpsize, fillindex, nextlinei, linei, i, offset;

    int use2=0, use4=0, use8=0, palout=0, padbytes=0;

    char drive[_MAX_DRIVE];
    char dir[_MAX_DIR];
    char file[_MAX_FNAME];
    char justfile[_MAX_FNAME];
    char ufile[_MAX_FNAME];
    char ext[_MAX_EXT];
    char of_name[_MAX_FNAME+_MAX_EXT];
    unsigned char *databuffer;
    unsigned char *rowbuffer; unsigned char *rowbuffer2;
    uint16_t rowbufindex=0, currentrowbuf=1;
    char *commentbuffer; char* commentbuffer2;
    bool rowflipping=false; //needed for 4-bit files from GIMP

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
            //printf("strlen file: %d " ,strlen(file));
            memset((void*)justfile,0,_MAX_FNAME);
            memcpy((void*)justfile,(void*)file,strlen(file)-4);
            strcat(justfile,"\0");
            //printf("justfile: %s ",justfile);
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

    /** numcol is the number of colors for output */
    unsigned int numcol;
    unsigned char pixperbyte;

    if (use8) { numcol=256;pixperbyte=1;}
    else if (use4) { numcol=16;pixperbyte=2;}
    else if (use2) { numcol=4;pixperbyte=4;}

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



  uint16_t test = sizeof(bmi.bmiHeader);
  if (fread(&bmi,test,1,infile) == 1)
    {
	if (bf.bfType != 0x4D42) {
        printf("Bitmap file has an unrecognized format (4D42 id missing from beginning).\n");
        printf("BMP2POK accepts .BMP files that have an indexed (4-bit or 8-bit) color palette.\n");
		fclose(infile);
		exit(-1);
	}
    if (bmi.bmiHeader.biBitCount != 8 && bmi.bmiHeader.biBitCount != 4 && bmi.bmiHeader.biBitCount != 1)
	{
		printf("Only 8bpp, 4bpp & 1bpp BMP files are supported\n");
		fclose(infile);

		exit(-1);
	}
        int c = bmi.bmiHeader.biClrUsed;
        if (c==0) c = 1 << bmi.bmiHeader.biBitCount; // from MS BMP specs. 0 means 2^n colors
        bmi.bmiHeader.biClrUsed = c;
        printf("Number of colours used: %d\n", c);
        //fread(&bmi.bmiColors[0],c*4,1,infile);
        /* seek to the beginning of the color table - because of gimp */
        fseek(infile, bf.bfOffBits-c*4, SEEK_SET); //gfx data star minus color table
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


	/* Allocate buffer storage */
	bmpsize = bmi.bmiHeader.biWidth * bmi.bmiHeader.biHeight*bmi.bmiHeader.biBitCount/8;
	if (bmi.bmiHeader.biWidth%4) {
            padbytes = bmi.bmiHeader.biWidth%4;
            printf("Width is not divisible by 4\n");
            printf("Ignoring %d padding bytes at each line\n", padbytes);
	}

	databuffer = (unsigned char *) malloc(bmpsize);
    rowbuffer = (unsigned char *) malloc(bmi.bmiHeader.biWidth/pixperbyte);
    rowbuffer2 = (unsigned char *) malloc(bmi.bmiHeader.biWidth/pixperbyte);
    commentbuffer = (char *) malloc(bmi.bmiHeader.biWidth+16);
    commentbuffer2 = (char *) malloc(bmi.bmiHeader.biWidth+16);

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
		unsigned char rgb;

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

  uint16_t row=0;

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
            /** OUTPUT as 4-BIT **/
            if (bmi.bmiHeader.biBitCount == 8) {
                /** 8-bit source image (photoshop) **/
                if (bitcounter) {
                    fprintf (outfile, "%d", (unsigned char)(prevvalue[0]<<4 | databuffer[offset]));
                    fillindex++;
                } else {
                    prevvalue[0] = databuffer[offset];
                }
                bitcounter = !bitcounter;
            } else if (bmi.bmiHeader.biBitCount == 4){
                /** 4-bit (probably GIMP) **/
                // you need to flip the rows arounf because in a 4-bit image pixels are packed in heiight direction also
                if (row&0x1) fprintf (outfile, "%d", (unsigned char)databuffer[offset+(bmi.bmiHeader.biWidth+padbytes)/2]);
                else fprintf (outfile, "%d", (unsigned char)databuffer[offset-(bmi.bmiHeader.biWidth+padbytes)/2]);
                fillindex++;
            } else if (bmi.bmiHeader.biBitCount == 1){
                /** 1-bit source image, 8 pixels per byte are written as 4 bytes with 2 pixels per byte **/
                fprintf (outfile, "%d,", (((databuffer[offset]>>7)&0x1)<<4) | ((databuffer[offset]>>6)&0x1)) ; //source bits 7-8 to 2 bytes
                fprintf (outfile, "%d,", (((databuffer[offset]>>5)&0x1)<<4) | ((databuffer[offset]>>4)&0x1)) ; //source bits 5-6 to 2 bytes
                fprintf (outfile, "%d,", (((databuffer[offset]>>3)&0x1)<<4) | ((databuffer[offset]>>2)&0x1)) ; //source bits 5-6 to 2 bytes
                fprintf (outfile, "%d,", (((databuffer[offset]>>1)&0x1)<<4) | ((databuffer[offset]>>0)&0x1)) ; //source bits 5-6 to 2 bytes
                fillindex++;
            }
        } else if (use2) {
            unsigned char outputbyte;
            if (bmi.bmiHeader.biBitCount == 8) {
            /** 8-bit source **/
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
            } else if (bmi.bmiHeader.biBitCount == 4) {
            rowflipping=true;
            /** 4-bit source **/
            switch(bitcounter) {
            case 0:
                prevvalue[0] = databuffer[offset]&0x0F; // first pixel is first byte lower nibble
                linei++; i--;// dont jump to next byte yet
                bitcounter +=2;
                break;
            case 2:
                prevvalue[1] = databuffer[offset]>>4; // 2nd pixel is first byte higher nibble
                bitcounter +=2;
                break;
            case 4:
                prevvalue[2] = databuffer[offset]&0x0F; // third pixel is second byte lower nibble
                linei++; i--;// dont jump to next byte yet
                bitcounter +=2;
                break;
            default:
                //outputbyte |= databuffer[offset]>>4;

                /*outputbyte = ((uint8_t)prevvalue[0] << 6); //pixel 0 is highest half nibble
                outputbyte |= ((uint8_t)prevvalue[1] << 4); //pixel 1
                outputbyte |= ((uint8_t)prevvalue[2] << 2); //pixel 2
                outputbyte |= databuffer[offset]>>4; // 4th pixel is second byte higher nibble*/

                prevvalue[3] = databuffer[offset]>>4;

                outputbyte = ((uint8_t)prevvalue[1] << 6); //pixel 0 is highest half nibble
                outputbyte |= ((uint8_t)prevvalue[0] << 4); //pixel 1
                outputbyte |= ((uint8_t)prevvalue[3] << 2); //pixel 2
                outputbyte |= ((uint8_t)prevvalue[2] << 0); // 4th pixel is second byte higher nibble*/
                //if (row&3>2) outputbyte=0;
                //fprintf (outfile, "%d", outputbyte);

                if (currentrowbuf==1) rowbuffer[rowbufindex++]=outputbyte;
                else rowbuffer2[rowbufindex++]=outputbyte;
                fillindex ++;
                bitcounter = 0;
            }
            }

        }
        if (temp!=fillindex) {
            /** A new entry was written to file **/
            if (fillindex == bmi.bmiHeader.biWidth/pixperbyte) //line change
            {
                if (rowflipping) {
                    /** flip rows**/
                    /** this is where row flipping happens **/
                    /** it was needed to change order of rows in a 4-bit source from GIMP */
                    if (currentrowbuf==2) {
                        /** output row 2 **/
                        for (int z=0;z<fillindex;z++) {
                                fprintf (outfile, "0x");
                                if (rowbuffer2[z]<0x10) fprintf (outfile, "0");
                                fprintf (outfile, "%X,",rowbuffer2[z]);
                        }
                        fprintf (outfile, "\n");
                        /** output row 1 **/
                        for (int z=0;z<fillindex;z++) {
                                fprintf (outfile, "0x");
                                if (rowbuffer[z]<0x10) fprintf (outfile, "0");
                                fprintf (outfile, "%X,",rowbuffer[z]);
                        }
                        fprintf (outfile, "\n");
                        currentrowbuf=1;
                    } else {
                        currentrowbuf=002;
                    }
                    rowbufindex=0;
                    fillindex = 0;
                    row++;
                } else {
                    /** no row flipping **/
                    fprintf (outfile, ",\n");
                    fillindex = 0;
                    row++;
                }
            }
            else {
                if (rowflipping==false) fprintf (outfile, ","); // add comma after entry
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

    fprintf (outfile, "};");
	free(databuffer);
	fclose(outfile);

    return 0;
}
