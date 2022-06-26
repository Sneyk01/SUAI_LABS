//
// Created by prgle on 26.06.2022.
//

#ifndef LAB15_BMP_READ_H
#define LAB15_BMP_READ_H


#include <iostream>
#include <cstdio>
#include <cstdlib>


typedef struct {
    uint16_t bfType;
    uint32_t bfSize;
    uint16_t bfReserved1;
    uint16_t bfReserved2;
    uint32_t bfOffBits;
} BITMAPFILEHEADER;


typedef struct {
    uint32_t biSize;
    int32_t biWidth;
    int32_t biHeight; // < 0 = error
    uint16_t biPlanes;
    uint16_t biBitCount;
    uint32_t biComression;
    uint32_t biSizeImage;
    uint32_t biXPelsPerMeter;
    uint32_t biYPelsPerMeter;
    uint32_t biClrUsed;
    uint32_t biClrImportant;
} BITMAPINFOHEADER;


void read_file_header(BITMAPFILEHEADER& head, FILE* image);
void read_info_header(BITMAPINFOHEADER& head, FILE* image);
unsigned char*** read_pixels(BITMAPFILEHEADER& f_head, BITMAPINFOHEADER& i_head, FILE* image);

void write_file_header(BITMAPFILEHEADER& head, FILE* image);
void write_info_header(BITMAPINFOHEADER& head, FILE* image);
void write_pixels(unsigned char*** pixels, BITMAPINFOHEADER& head, FILE* image);


#endif //LAB15_BMP_READ_H
