
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HEADERSIZE   54 
#define PALLETSIZE 1024 
#define MAXWIDTH   2000 
#define MAXHEIGHT  2000 


typedef struct {        
  unsigned char b;
  unsigned char g;
  unsigned char r;
} color;

typedef struct {
  long     height;
  long     width;
  color    data[MAXHEIGHT][MAXWIDTH];
} img;


extern void ReadBmp(char *filename, img *imgp);
extern void WriteBmp(char *filename, img *tp);
extern void PrintBmpInfo(char *filename);
extern void HMirror(img *tp, img *sp);
extern void VMirror(img *tp, img *sp);
extern void Rotate90(int a, img *tp, img *sp);
extern void Mosaic(int a, img *tp, img *sp);
extern void Gray(img *tp, img *sp);
extern void Diminish(img *tp, img *sp, unsigned char x);
extern void Shrink(int a, img *tp, img *sp);
extern void Expand(int a, img *tp, img *sp);
extern void WriteHex(char *filename, img *tp);
