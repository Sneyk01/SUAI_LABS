//
// Created by prgle on 26.06.2022.
//

#include "BMP_read.h"


void read_file_header(BITMAPFILEHEADER& head, FILE* image) {
    fread(&head.bfType, 2, 1, image);
    fread(&head.bfSize, 4, 1, image);
    fread(&head.bfReserved1, 2, 1, image);
    fread(&head.bfReserved2, 2, 1, image);
    fread(&head.bfOffBits, 4, 1, image);
    //printf("%c%c\n", head.bfType, head.bfType >> 8);
}


void read_info_header(BITMAPINFOHEADER& head, FILE* image) {
    fread(&head.biSize, 4, 1, image);
    fread(&head.biWidth, 4, 1, image);
    fread(&head.biHeight, 4, 1, image);
    fread(&head.biPlanes, 2, 1, image);
    fread(&head.biBitCount, 2, 1, image);
    fread(&head.biComression, 4, 1, image);
    fread(&head.biSizeImage, 4, 1, image);
    fread(&head.biXPelsPerMeter, 4, 1, image);
    fread(&head.biYPelsPerMeter, 4, 1, image);
    fread(&head.biClrUsed, 4, 1, image);
    fread(&head.biClrImportant, 4, 1, image);
    //printf("%d\n", head.biHeight);
}


unsigned char*** read_pixels(BITMAPFILEHEADER& f_head, BITMAPINFOHEADER& i_head, FILE* image) {
    unsigned char*** pixels = new unsigned char**[abs(i_head.biHeight)];

    for (int h = 0; h < abs(i_head.biHeight); h++) {
        pixels[h] = new unsigned char*[i_head.biWidth];

        for (int w = 0; w < i_head.biWidth; w++) {
            pixels[h][w] = new unsigned char[3];

            if (fread(pixels[h][w], 1, 3, image) != 3) {
                std::cout << "Error! \n";
                return nullptr;
            }
        }

        if (i_head.biWidth % 4 != 0)
            fseek(image, i_head.biWidth % 4, SEEK_CUR);

    }
    return pixels;
}


void write_file_header(BITMAPFILEHEADER& head, FILE* image) {
    fwrite(&head.bfType, 2, 1, image);
    fwrite(&head.bfSize, 4, 1, image);
    fwrite(&head.bfReserved1, 2, 1, image);
    fwrite(&head.bfReserved2, 2, 1, image);
    fwrite(&head.bfOffBits, 4, 1, image);
}


void write_info_header(BITMAPINFOHEADER& head, FILE* image) {
    fwrite(&head.biSize, 4, 1, image);
    fwrite(&head.biWidth, 4, 1, image);
    fwrite(&head.biHeight, 4, 1, image);
    fwrite(&head.biPlanes, 2, 1, image);
    fwrite(&head.biBitCount, 2, 1, image);
    fwrite(&head.biComression, 4, 1, image);
    fwrite(&head.biSizeImage, 4, 1, image);
    fwrite(&head.biXPelsPerMeter, 4, 1, image);
    fwrite(&head.biYPelsPerMeter, 4, 1, image);
    fwrite(&head.biClrUsed, 4, 1, image);
    fwrite(&head.biClrImportant, 4, 1, image);
}


void write_pixels(unsigned char*** pixels, BITMAPINFOHEADER& head, FILE* image) {
    char buf[3] = {0};
    for(int h = 0; h < abs(head.biHeight); h++) {
        for (int w = 0; w < head.biWidth; w++)
            fwrite(pixels[h][w], 1, 3, image);

        if (head.biWidth % 4 != 0)
            fwrite(buf, 1, head.biWidth % 4, image);
    }
}
