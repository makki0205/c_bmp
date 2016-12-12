

#include  "bmp.h"

int main(int argc, char** argv) {
  img *tmp1;
  img *tmp2;

  char in_filename[70]  ="example.bmp" ;
  char out_filename[70] ="output.bmp" ;
  char hex_filename[70] ="hex.h" ;

  tmp1=(img *)malloc(sizeof(img));
  tmp2=(img *)malloc(sizeof(img));

 ReadBmp(in_filename,tmp1);
 // ReadBmp(in_filename,tmp2);
 // Gray(tmp1, tmp2);
 // VMirror(tmp1,tmp2);
 // HMirror(tmp1,tmp2);
 // Mosaic(5,tmp1,tmp2);
 printf("init");
 Rotate90(0,tmp1,tmp2);
 WriteBmp(out_filename,tmp2);
 }
