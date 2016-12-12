
#define _CRT_SECURE_NO_WARNINGS

#include "bmp.h"

unsigned char  Bmp_headbuf[HEADERSIZE];/* ヘッダを格納するための変数          */
unsigned char  Bmp_Pallet[PALLETSIZE]; /* カラーパレットを格納                */

char           Bmp_type[2];            /* ファイルタイプ "BM"                 */
unsigned int  Bmp_size;               /* bmpファイルのサイズ (バイト)        */
unsigned int   Bmp_info_header_size;   /* 情報ヘッダのサイズ = 40             */
unsigned int   Bmp_header_size;        /* ヘッダサイズ = 54                   */
int           Bmp_height;             /* 高さ (ピクセル)                     */
int           Bmp_width;              /* 幅   (ピクセル)                     */
unsigned short Bmp_planes;             /* プレーン数 常に 1                   */
unsigned short Bmp_color;              /* 色 (ビット)     24                  */
int           Bmp_comp;               /* 圧縮方法         0                  */
int           Bmp_image_size;         /* 画像部分のファイルサイズ (バイト)   */
int           Bmp_xppm;               /* 水平解像度 (ppm)                    */
int           Bmp_yppm;               /* 垂直解像度 (ppm)                    */

void ReadBmp(char *filename, img *imgp) {
  int i,j;
  int Real_width;
  unsigned char *Bmp_Data;

  FILE *Bmp_Fp=fopen(filename,"rb");
  if(Bmp_Fp==NULL){
    printf("Error: file %s couldn¥'t open for read!.¥n",filename);
    exit(1);
  }

  fread(Bmp_headbuf,sizeof(unsigned char),HEADERSIZE,Bmp_Fp);
  memcpy(&Bmp_type,Bmp_headbuf,sizeof(Bmp_type));
  if (strncmp(Bmp_type,"BM",2)!=0) {
    printf("Error: %s is not a bmp file.¥n",filename);
    exit(1);
  }
  memcpy(&imgp->width, Bmp_headbuf+18,sizeof(Bmp_width));
  memcpy(&imgp->height,Bmp_headbuf+22,sizeof(Bmp_height));
  memcpy(&Bmp_color,Bmp_headbuf+28,sizeof(Bmp_color));
  if (Bmp_color!=24) {
    printf("Error: Bmp_color = %d is not implemented in this program.¥n",Bmp_color);
    exit(1);
  }
  if (imgp->width > MAXWIDTH) {
    printf("Error: Bmp_width = %d > %d = MAXWIDTH!¥n",Bmp_width,MAXWIDTH);
    exit(1);
  }
  if (imgp->height > MAXHEIGHT) {
    printf("Error: Bmp_height = %d > %d = MAXHEIGHT!¥n",Bmp_height,MAXHEIGHT);
    exit(1);
  }


  Real_width = imgp->width*3 + imgp->width%4;

  if((Bmp_Data = (unsigned char *)calloc(Real_width,sizeof(unsigned char)))==NULL) {
    printf("Error: Memory allocation failed for Bmp_Data!¥n");
    exit(1);
  }
  for(i=0;i<imgp->height;i++) {
    fread(Bmp_Data,1,Real_width,Bmp_Fp);
    for (j=0;j<imgp->width;j++) {
      imgp->data[imgp->height-i-1][j].b = Bmp_Data[j*3];
      imgp->data[imgp->height-i-1][j].g = Bmp_Data[j*3+1];
      imgp->data[imgp->height-i-1][j].r = Bmp_Data[j*3+2];
    }
  }
  free(Bmp_Data);
  // File Close
  fclose(Bmp_Fp);
}



void WriteBmp(char *filename, img *tp) {
  int i,j;
  int Real_width;
  unsigned char *Bmp_Data;

  FILE *Out_Fp = fopen(filename,"wb");
  if(Out_Fp==NULL){
    printf("Error: file %s couldn¥'t open for write!¥n",filename);
    exit(1);
  }

  Real_width = tp->width*3 + tp->width%4;

  if((Bmp_Data = (unsigned char *)calloc(Real_width,sizeof(unsigned char)))==NULL) {
   printf("Error: Memory allocation failed for Bmp_Data!¥n");
   exit(1);
 }

  Bmp_color=24;
  Bmp_header_size=HEADERSIZE;
  Bmp_info_header_size=40;
  Bmp_planes=1;

  Bmp_xppm=Bmp_yppm=0;
  Bmp_image_size = tp->height*Real_width;
  Bmp_size       = Bmp_image_size + HEADERSIZE;
  Bmp_headbuf[0]='B'; Bmp_headbuf[1]='M';
  memcpy(Bmp_headbuf+2,&Bmp_size,sizeof(Bmp_size));
  Bmp_headbuf[6]=Bmp_headbuf[7]=Bmp_headbuf[8]=Bmp_headbuf[9]=0;
  memcpy(Bmp_headbuf+10,&Bmp_header_size,sizeof(Bmp_header_size));
  Bmp_headbuf[11]=Bmp_headbuf[12]=Bmp_headbuf[13]=0;
  memcpy(Bmp_headbuf+14,&Bmp_info_header_size,sizeof(Bmp_info_header_size));
  Bmp_headbuf[15]=Bmp_headbuf[16]=Bmp_headbuf[17]=0;
  memcpy(Bmp_headbuf+18,&tp->width,sizeof(Bmp_width));
  memcpy(Bmp_headbuf+22,&tp->height,sizeof(Bmp_height));
  memcpy(Bmp_headbuf+26,&Bmp_planes,sizeof(Bmp_planes));
  memcpy(Bmp_headbuf+28,&Bmp_color,sizeof(Bmp_color));
  memcpy(Bmp_headbuf+34,&Bmp_image_size,sizeof(Bmp_image_size));
  memcpy(Bmp_headbuf+38,&Bmp_xppm,sizeof(Bmp_xppm));
  memcpy(Bmp_headbuf+42,&Bmp_yppm,sizeof(Bmp_yppm));
  Bmp_headbuf[46]=Bmp_headbuf[47]=Bmp_headbuf[48]=Bmp_headbuf[49]=0;
  Bmp_headbuf[50]=Bmp_headbuf[51]=Bmp_headbuf[52]=Bmp_headbuf[53]=0;

  fwrite(Bmp_headbuf,sizeof(unsigned char),HEADERSIZE,Out_Fp);

  for (i=0;i<tp->height;i++) {
    for (j=0;j<tp->width;j++) {
      Bmp_Data[j*3]   = tp->data[tp->height-i-1][j].b;
      Bmp_Data[j*3+1] = tp->data[tp->height-i-1][j].g;
      Bmp_Data[j*3+2] = tp->data[tp->height-i-1][j].r;
    }
    for (j=tp->width*3;j<Real_width;j++) {
      Bmp_Data[j]=0;
    }
    fwrite(Bmp_Data,sizeof(unsigned char),Real_width,Out_Fp);
  }
  // 動的確保した配列領域の解放
  free(Bmp_Data);
  // File Close
  fclose(Out_Fp);
}


void WriteHex(char *filename, img *tp) {
  int i,j,k=0;
  int Real_width;
  int zeros=0;

  FILE *Out_Fp = fopen(filename,"wt");
  if(Out_Fp==NULL){
    printf("Error: file %s couldn¥'t open for write!¥n",filename);
    exit(1);
  }

  Real_width = tp->width*3 + tp->width%4;

  fprintf(Out_Fp,"const  uint8_t  BMP_%s[] = {¥n",filename);

  for(i=0; i<tp->height; i++) {                             // tp->height = Page数
     fprintf(Out_Fp,"¥t");
     for(j=0; j<tp->width; j++) {
        if (j*3 <= Real_width){
           fprintf(Out_Fp,"0x%02x",tp->data[tp->height-i-1][j].b);
           fprintf(Out_Fp,"%02x",  tp->data[tp->height-i-1][j].g);
           fprintf(Out_Fp,"%02x",  tp->data[tp->height-i-1][j].r);
        }else{
           zeros= Real_width-j*3;
           for (k=0;k<zeros;k++){
           fprintf(Out_Fp,"0x%02x",0x00);
           }
        }
        if(i<tp->height-1 || j<tp->width-1) { fprintf(Out_Fp,",");
        }else                               { fprintf(Out_Fp," ");
        }
        if(j<tp->width-1 && j%16==15) { fprintf(Out_Fp,"¥n¥t");}
        if(j==tp->width-1)            { fprintf(Out_Fp," // 行%d¥n¥n",i);}
     }
  }
  fprintf(Out_Fp,"};¥n");

  fclose(Out_Fp);
}
