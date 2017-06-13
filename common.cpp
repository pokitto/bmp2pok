#define NOT_DEBUG 1 //true = command line arguments are active

int main(int argc, char * argv[])
{
    BITMAPFILEHEADER bf;
    BITMAPINFO bmi;
    RGBQUAD myColors[256]; // needed because size of bmi.bmiColors is defined as 1 in wingdi.h !!!

    FILE *infile, *outfile;
    uint32_t bytes_read = 0, bmpsize, parsedsize=0, fillindex, nextlinei, linei, i, offset;

    int use1=0, use2=0, use4=0, use8=0, palout=0, padbytes=0;

    char drive[_MAX_DRIVE];
    char dir[_MAX_DIR];
    char file[_MAX_FNAME];
    char justfile[_MAX_FNAME];
    char ufile[_MAX_FNAME];
    char ext[_MAX_EXT];
    char of_name[_MAX_FNAME+_MAX_EXT];
    unsigned char *databuffer;
    unsigned char *parsedbuffer;
    unsigned char *rowbuffer;

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
    else if ((strcmp(argv[2], "-1")) == 0 && NOT_DEBUG)
    {
        use1 = 1;
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
        printf("File name: %s \n",file);
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
    else if (use1) { numcol=1;pixperbyte=8;}

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
        printf("BMP2POK accepts .BMP files that have an indexed (1,-bit, 4-bit or 8-bit) color palette.\n");
		fclose(infile);
		exit(-1);
	}

	if (bmi.bmiHeader.biWidth%32 && bmi.bmiHeader.biBitCount == 1) {
            printf("ERROR!\nPadding of 1-bit (monochrome) images is not yet supported\n");
            printf("1-bit images need to have width that is divisible by 32!\n");
            printf("Adjust size of source image.\n", padbytes);
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
        printf("Bits per pixel: %d\n", bmi.bmiHeader.biBitCount);
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


	/** ALLOCATE buffer storage **/
	bmpsize = bmi.bmiHeader.biWidth * bmi.bmiHeader.biHeight*bmi.bmiHeader.biBitCount/8;
	parsedsize = bmi.bmiHeader.biWidth * bmi.bmiHeader.biHeight;
	if (bmi.bmiHeader.biWidth%4) {
            padbytes = bmi.bmiHeader.biWidth%4;
            printf("Width is not divisible by 4\n");
            printf("Ignoring %d padding bytes at each line\n", padbytes);
	}

	databuffer = (unsigned char *) malloc(bmpsize);
	parsedbuffer = (unsigned char *) malloc (parsedsize);
    rowbuffer = (unsigned char*) malloc (bmi.bmiHeader.biWidth);

	if (databuffer == NULL)
	{
		printf("Error allocating temporary data buffer, is image too big?\n");
		fclose(infile);
		exit(-1);
	}

  /** SEEK to the beginning of the data **/
	fseek(infile, bf.bfOffBits, SEEK_SET);

	/** READ DATA into array, IGNORE BMP PADDING **/
	int padcounter = bmi.bmiHeader.biWidth+padbytes;
	fillindex = bmpsize - 1;
	i = 0;
	while (i < bmpsize)
    {
		unsigned char rgb;

		if (fread(&rgb, sizeof(rgb), 1, infile) != 1)
		{
			printf("Error reading BMP data\n");
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

  /** PARSING DATABUFFER to PURE BYTES (1-,4- bit sources to 8-bit) **/
  uint16_t tempcol;
  bool truncated_warning = false;

  for (uint16_t k=0, l=0; k < bmpsize; k++, l++) {
    switch (bmi.bmiHeader.biBitCount) {
    case 8:
        tempcol = databuffer[k];
        if (!use8 && tempcol > 0x0F) truncated_warning = true;
        parsedbuffer[l] = databuffer[k];break;
    case 4:
        parsedbuffer[l+1] = databuffer[k]>>4;
        tempcol = databuffer[k]>>4;
        if (!use8 && !use4 && tempcol > 0x03) truncated_warning = true;
        parsedbuffer[l] = databuffer[k]&0x0F;
        tempcol = databuffer[k];
        if (!use8 && !use4 && tempcol > 0x03) truncated_warning = true;
        l++; break;
    case 1:
        parsedbuffer[l] =   (databuffer[k]>>7)&0x01;
        parsedbuffer[l+1] = (databuffer[k]>>6)&0x01;
        parsedbuffer[l+2] = (databuffer[k]>>5)&0x01;
        parsedbuffer[l+3] = (databuffer[k]>>4)&0x01;
        parsedbuffer[l+4] = (databuffer[k]>>3)&0x01;
        parsedbuffer[l+5] = (databuffer[k]>>2)&0x01;
        parsedbuffer[l+6] = (databuffer[k]>>1)&0x01;
        parsedbuffer[l+7] = (databuffer[k]>>0)&0x01;
        l += 7; break;
    }
  }


  /** MIRROR ROWS HORIZONTALLY **/

  for (uint16_t l=0; l < bmi.bmiHeader.biHeight; l++) {
        for (uint16_t m=0; m < bmi.bmiHeader.biWidth; m++) rowbuffer[m] = parsedbuffer[m+l*bmi.bmiHeader.biWidth];
        for (uint16_t m=0; m < bmi.bmiHeader.biWidth; m++) parsedbuffer[m+l*bmi.bmiHeader.biWidth] = rowbuffer[bmi.bmiHeader.biWidth -1 - m];
    }


  /** FLIP ROWS for 4-BIT IMAGE SOURCES **/
  /*uint16_t ind=0;
  if (bmi.bmiHeader.biBitCount == 4) {
    for (uint16_t l=0; l < bmi.bmiHeader.biHeight; l+=2) {
        for (uint16_t m=0; m < bmi.bmiHeader.biWidth; m++,ind++) {
        uint8_t temp = parsedbuffer[ind];
        parsedbuffer[ind]=parsedbuffer[ind+bmi.bmiHeader.biWidth];
        parsedbuffer[ind+bmi.bmiHeader.biWidth]=temp;
    }
    ind += bmi.bmiHeader.biWidth; //jump 1 row to next pair
  }
  }*/

  /** PREPARE OUTPUT FILE **/
	//if (use555)
	sprintf(of_name,justfile);
	strcat(of_name,".c");

	printf("Outputting c file: %s\n", of_name);
    outfile = fopen(of_name,"w");

	if (outfile == NULL)
	{
		printf("Error opening out file %s\n", of_name);
		free(databuffer);
	    exit(-1);
	}

  if (use8) fprintf (outfile,
	"\n\n/*\n * BMP image as 8bpp (up to 256 color index) data\n");
  else if (use4) fprintf (outfile,
  "\n\n/*\n * BMP image as 4bpp (16 color index) data\n");
  else if (use2) fprintf (outfile,
	"\n\n/*\n * BMP image as 2bpp (4 color) data\n");
	else if (use1) fprintf (outfile,
	"\n\n/*\n * BMP image as 1bpp (2 color) data\n");

	fprintf (outfile, " */\n\n");
	fprintf(outfile,"#include <stdint.h>\n\n");

  /** SHOW PARSED DATA **/
  #ifdef SHOW_PARSED
  for (uint32_t j=0, l=0; j<bmi.bmiHeader.biHeight; j++) {
    fprintf (outfile, "// ");
    for (uint16_t k=0; k<bmi.bmiHeader.biWidth; k++, l++) {
    unsigned char temp = parsedbuffer[l];
    if (temp<0x10) fprintf (outfile, "%X",temp);
    else fprintf (outfile, "%X",temp);
    }
    fprintf (outfile, "\n");
  }
  #endif

  /** OUTPUT Palette data **/
  fprintf(outfile,"const uint16_t ");
  fprintf(outfile,justfile);
  fprintf(outfile,"_pal[] = {\n");

  if (bmi.bmiHeader.biClrUsed>numcol) {
    printf("WARNING! \n");
    printf("Your image has %d different colors.\n",(int)bmi.bmiHeader.biClrUsed);
    if (use4) printf("But 4bpp mode only allows 16 different colors in the palette.\n");
    else if (use2) printf("But 2bpp mode only allows 4 different colors in the palette.\n");
    else if (use1) printf("But 1bpp mode only allows 2 different colors in the palette.\n");
    printf("The program will automatically IGNORE any colors used above this limit.\n");
  }

  if (truncated_warning) {
        printf("WARNING! \nYou have pixels in your image that use colors that are not in the output palette.\n");
        printf("The image may not look right. Reduce number of image colors in the drawing program before converting.\n");
  }
  /** OUTPUT Palette **/
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

	/** PREPARE Image data **/
  fprintf(outfile, "const uint8_t ");
  fprintf(outfile,justfile);
  fprintf(outfile,"[] = {\n%d,%d,\n",(int)bmi.bmiHeader.biWidth,(int)bmi.bmiHeader.biHeight);

    i = 0;

  /** OUTPUT Image data **/
	while (i < parsedsize)
	{
	for (uint16_t b=0; b < bmi.bmiHeader.biWidth; b++, i++) {
    if (use8) {
      /** 256 Color output **/
      if (parsedbuffer[i]<0x10) fprintf (outfile, "0x0%X,", (unsigned char)parsedbuffer[i]);
      else fprintf (outfile, "0x%X,", parsedbuffer[i]);
    } else if (use4) {
      /** 16 Color output **/
      unsigned char combined = (parsedbuffer[i] << 4) | (parsedbuffer[i+1] & 0x0F);
      if (combined<0x10) fprintf (outfile, "0x0%X,", combined);
      else fprintf (outfile, "0x%X,", combined);
      b++; i++; // jump over next byte
    } else if (use2) {
      /** 4 Color output **/
      unsigned char combined = (parsedbuffer[i] << 6) | (parsedbuffer[i+1] << 4) | (parsedbuffer[i+2] << 2) | (parsedbuffer[i+3]);
      if (combined<0x10) fprintf (outfile, "0x0%X,", combined);
      else fprintf (outfile, "0x%X,", combined);
      b+=3; i+=3; // jump over next 3 bytes
    } else if (use1) {
      /** 2 Color output - horizontal input bits are packed vertically !**/
      unsigned char combined = (parsedbuffer[i] << 7) | \
                               (parsedbuffer[i+1 * bmi.bmiHeader.biWidth] << 6) | \
                               (parsedbuffer[i+2 * bmi.bmiHeader.biWidth] << 5) | \
                               (parsedbuffer[i+3 * bmi.bmiHeader.biWidth] << 4) | \
                               (parsedbuffer[i+4 * bmi.bmiHeader.biWidth] << 3) | \
                               (parsedbuffer[i+5 * bmi.bmiHeader.biWidth] << 2) | \
                               (parsedbuffer[i+6 * bmi.bmiHeader.biWidth] << 1) | \
                               (parsedbuffer[i+7 * bmi.bmiHeader.biWidth]);
      if (combined<0x10) fprintf (outfile, "0x0%X,", combined);
      else fprintf (outfile, "0x%X,", combined);
      b+=7; // add 1+7 bytes processed to counter
    }
	}
	fprintf (outfile, "\n");
	if (use1) i += bmi.bmiHeader.biWidth;
    }

/** FINALIZE **/
fprintf (outfile, "};");
free(databuffer);
free(parsedbuffer);
free(rowbuffer);
fclose(outfile);

return 0;
}
