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
            fseek(image, i_head.biWidth % 4, SEEK_CUR); //skip 0

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
            fwrite(buf, 1, head.biWidth % 4, image);    // adding 0 if it needs
    }
}


void BMP::load(char *path) {
    FILE* image = fopen(path, "rb");

    if (image == nullptr) {
        std::cout << "Source not found!";
        exit(-1);
    }

    read_file_header(this->f_head, image);
    read_info_header(this->i_head, image);
    this->pixels = read_pixels(this->f_head, this->i_head, image);

    fclose(image);
}


void BMP::save_quarter(char *path) {
    FILE* new_image = fopen(path, "wb");

    if (new_image == nullptr) {
        std::cout << "Destination path error!";
        exit(-1);
    }

    BITMAPFILEHEADER new_f_head = this->f_head;
    BITMAPINFOHEADER new_i_head = this->i_head;

    new_i_head.biWidth = this->i_head.biWidth / 2;
    new_i_head.biHeight = this->i_head.biHeight / 2;
    new_i_head.biSizeImage = abs(new_i_head.biWidth * new_i_head.biHeight * 3);

    new_f_head.bfSize = this->f_head.bfOffBits + new_i_head.biSizeImage;

    unsigned int orientation = 0;
    if (new_i_head.biHeight > 0)
        orientation = abs(new_i_head.biHeight) + (abs(this->i_head.biHeight) % 2); // if new Height !/ by 2

    unsigned char*** new_pixels = new unsigned char** [abs(new_i_head.biHeight)];
    for (int h = 0; h < abs(new_i_head.biHeight); h++) {
        new_pixels[h] = new unsigned char* [new_i_head.biWidth];

        for (int w = 0; w < new_i_head.biWidth; w++) {
            new_pixels[h][w] = new unsigned char[3];
            for(int i = 0; i < 3; i++)
                new_pixels[h][w][i] = this->pixels[orientation + h][w][i];
        }
    }

    write_file_header(new_f_head, new_image);
    write_info_header(new_i_head, new_image);
    write_pixels(new_pixels, new_i_head, new_image);

    delete[] new_pixels;

    fclose(new_image);
}


BMP::~BMP() {
    delete[] pixels;
}


BMP::BMP() {
    pixels = nullptr;
}
