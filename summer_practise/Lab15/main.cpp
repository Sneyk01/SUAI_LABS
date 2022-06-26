#include "BMP_read.h"


int main() {
    int flag = 0;

    BITMAPFILEHEADER f_head;
    BITMAPINFOHEADER i_head;

    FILE* image = fopen("D:\\Project\\C\\summer_practise\\Lab15\\test.bmp", "rb");

    read_file_header(f_head, image);
    read_info_header(i_head, image);

    unsigned char*** pixels = read_pixels(f_head, i_head, image);

    FILE* new_image = fopen("D:\\Project\\C\\summer_practise\\Lab15\\new_test.bmp", "wb");

    BITMAPFILEHEADER new_f_head = f_head;
    BITMAPINFOHEADER new_i_head = i_head;

    new_i_head.biWidth = i_head.biWidth / 2;
    new_i_head.biHeight = i_head.biHeight / 2;
    new_i_head.biSizeImage = abs(new_i_head.biWidth * new_i_head.biHeight * 3);

    new_f_head.bfSize = f_head.bfOffBits + new_i_head.biSizeImage;

    unsigned int orientation = 0;
    if (new_i_head.biHeight > 0)
        orientation = abs(new_i_head.biHeight) + (abs(i_head.biHeight) % 2); // if new Height !/ by 2

    unsigned char*** new_pixels = new unsigned char** [abs(new_i_head.biHeight)];
    for (int h = 0; h < abs(new_i_head.biHeight); h++) {
        new_pixels[h] = new unsigned char *[new_i_head.biWidth];
        //std::cout <<orientation + h << '\n';
        for (int w = 0; w < new_i_head.biWidth; w++) {
            new_pixels[h][w] = new unsigned char[3];
            for(int i = 0; i < 3; i++)
                new_pixels[h][w][i] = pixels[orientation + h][w][i];
        }
    }

    write_file_header(new_f_head, new_image);
    write_info_header(new_i_head, new_image);
    write_pixels(new_pixels, new_i_head, new_image);

    //std::cout << new_i_head.biWidth;


    delete[] pixels;
    delete[] new_pixels;

    fclose(image);
    fclose(new_image);

    return 0;
}
