#include  "bmp.h"

extern void Gray(img *tp, img *sp){
    unsigned char r;
    unsigned char g;
    unsigned char b;
    unsigned char ave;
    memcpy(sp, tp, sizeof(img));
    printf("%02x\n", (tp->data[200][300]).r );
    for (size_t i = 0; i <= tp->height; i++) {
        for (size_t j = 0; j <= tp->width; j++) {
            r = tp->data[i][j].r;
            g = tp->data[i][j].g;
            b = tp->data[i][j].b;
            ave = (r+g+b)/3;
            // printf("%02x  %02x  %02x : %02x\n",r,g,b,ave );
            sp->data[i][j].r = ave;
            sp->data[i][j].g = ave;
            sp->data[i][j].b = ave;
            r = sp->data[i][j].r;
            g = sp->data[i][j].g;
            b = sp->data[i][j].b;
            ave = (r+g+b)/3;
            printf("[%d][%d]%02x  %02x  %02x : %02x\n",i,j,r,g,b,ave );
        }
    }
}
extern void VMirror(img *tp, img *sp){
    memcpy(sp, tp, sizeof(img));
    for (size_t i = 0; i <= tp->height; i++) {
        for (size_t j = 0; j <= tp->width; j++) {
            sp->data[i][tp->width-j].r = tp->data[i][j].r;
            sp->data[i][tp->width-j].g = tp->data[i][j].g;
            sp->data[i][tp->width-j].b = tp->data[i][j].b;
        }
    }
}

extern void HMirror(img *tp, img *sp){
    memcpy(sp, tp, sizeof(img));
    for (size_t i = 0; i <= tp->height; i++) {
        for (size_t j = 0; j <= tp->width; j++) {
            sp->data[tp->height-i][j].r = tp->data[i][j].r;
            sp->data[tp->height-i][j].g = tp->data[i][j].g;
            sp->data[tp->height-i][j].b = tp->data[i][j].b;
        }
    }
}
extern void Rotate90(int a, img *tp, img *sp){
    int tmp = 0;
    memcpy(sp, tp, sizeof(img));
    for (size_t i = 0; i <= tp->height; i+=a) {
        for (size_t j = 0; j <= tp->width; j+=a) {
            sp->data[i][j].r = tp->data[(tp->width-1)-i][j].r;
            sp->data[i][j].g = tp->data[(tp->width-1)-i][j].g;
            sp->data[i][j].b = tp->data[(tp->width-1)-i][j].b;
        }
    }
    sp->width = tp->height;
    sp->height = tp->width;

}

extern void Mosaic(int a, img *tp, img *sp){
    int r,g,b;
    memcpy(sp, tp, sizeof(img));
    for (size_t i = 0; i <= tp->height; i+=a) {
        for (size_t j = 0; j <= tp->width; j+=a) {
            r = 0;
            g = 0;
            b = 0;
            for (size_t x = 0; x < a; x++) {
                for (size_t y = 0; y < a; y++) {
                    r += tp->data[i+x][j+y].r;
                    g += tp->data[i+x][j+y].g;
                    b += tp->data[i+x][j+y].b;
                }
            }
            r /= (a*a);
            g /= (a*a);
            b /= (a*a);
            for (size_t x = 0; x < a; x++) {
                for (size_t y = 0; y < a; y++) {
                    sp->data[i+x][j+y].r = r;
                    sp->data[i+x][j+y].g = g;
                    sp->data[i+x][j+y].b = b;
                    printf("[%d][%d]\n",x+i,y+j );
                }
            }
        }
    }
}
