#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bmplib.h"

/*
 * This method enlarges a 24-bit, uncompressed .bmp file that has been
 * read in using readFile(), by doubling the number of rows and
 * columns. Also the image will convert to gray scale if requested.
 *
 * original - an array containing the original PIXELs, 3 bytes per each
 * rows     - the original number of rows
 * cols     - the original number of columns
 * bw       - convert to gray scale if not zero
 *
 * new      - the new array containing the PIXELs, allocated within
 * newrows  - the new number of rows (twice as many)
 * newcols  - the new number of columns (twice as many)
 */
int process(PIXEL* original, int rows, int cols, int bw,
	    PIXEL** new, int* newrows, int* newcols)
{
  /* THIS IS THE METHOD THAT YOU SHOULD WRITE */

    int row, col;
    if ((rows <= 0) || (cols <= 0)) return -1;

    *newrows = rows * 2;
    *newcols = cols * 2;
    
    *new = (PIXEL*)malloc((*newrows) * (*newcols) * sizeof(PIXEL));

    for (row = 0; row < rows; row++) {
        for (col = 0; col < cols; col++) {
            PIXEL* o = original + row * cols + col;

            if (bw)
                o->r = o->g = o->b = 0.2126 * o->r + 0.7152 * o->g + 0.0722 * o->b;
            
            for (int i = 0; i < 2; i++)
                for (int j = 0; j < 2; j++) {
                    PIXEL* n = (*new) + 2 * (row * (*newcols) + col) + (i * (*newcols) + j);
                    *n = *o;
                }
        }

    }

  return 0;
}

/*
 * This method horizontally flips a 24-bit, uncompressed bmp file
 * that has been read in using readFile(). 
 * 
 * THIS IS PROVIDED TO YOU AS AN EXAMPLE FOR YOU TO UNDERSTAND HOW IT
 * WORKS
 *
 * original - an array containing the original PIXELs, 3 bytes per each
 * rows     - the number of rows
 * cols     - the number of columns
 *
 * new      - the new array containing the PIXELs, allocated within
 */
int flip (PIXEL *original, int rows, int cols, PIXEL **new) 
{
  int row, col;

  if ((rows <= 0) || (cols <= 0)) return -1;

  *new = (PIXEL*)malloc(rows*cols*sizeof(PIXEL));

  for (row=0; row < rows; row++)
    for (col=0; col < cols; col++) {
      PIXEL* o = original + row*cols + col;
      PIXEL* n = (*new) + row*cols + (cols-1-col);
      *n = *o;
    }

  return 0;
}

void main(int argc, char* argv[])
{
  int rows, cols, newrows, newcols;
  PIXEL *pix = NULL;
  PIXEL* npix = NULL;

  if (argc < 3) {
      fprintf(stderr, "Too few arguments\n");
  } else if (argc > 4) {
      fprintf(stderr, "Too many arguments\n");
  } else if (argc == 3) {
      int r = readFile(argv[1], &rows, &cols, &pix);
      if (r == -1) return;
      process(pix, rows, cols, 0, &npix, &newrows, &newcols);
      writeFile(argv[2], newrows, newcols, npix);
  } else if (argc == 4) {
      if (strcmp(argv[1], "-b") == 0) {
          int r = readFile(argv[2], &rows, &cols, &pix);
          if (r == -1) return;
          process(pix, rows, cols, 1, &npix, &newrows, &newcols);
          writeFile(argv[3], newrows, newcols, npix);
      } else {
          fprintf(stderr, "Incorrect arguments");
      }
  }
   

  if(pix != NULL) free(pix);
  if(npix != NULL) free(npix);


}
