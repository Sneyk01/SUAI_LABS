//
// Created by prgle on 04.04.2022.
//

#include "lib.h"


BitArray::BitArray(int size) {
    int size_ar = 0;
    if (size > 0 && size < 33) {
        size_ar = size / 8;
        if (size % 8 != 0)
            size_ar++;

        //printf("Array size - %d\n", size_ar);
        data = new char [size_ar];
        size_bit = size;

        for (int i = 0; i < size_ar; i++)
            data[i] = 0;

    }

    else {
        printf("Value is out of size off limits\n");
        *data = NULL;
        size_bit = 0;
    }

    // printf("_%lu\n\n", data[0]);
}


BitArray::~BitArray() {
    delete[] data;
}


void BitArray::setOne(int value, int num) {
    if (num > -1 && num < this->size_bit) {
        if (value < 0) {
            printf("Value error!\n");
            return;
        }

        unsigned char mask = 1 << num;
        // printf("(mask - %d)\n", mask);

        int num_ar = num / 8;

        // printf("(res - %lu)\n", this->data[num_ar]);

        if (value > 0)
            this->data[num_ar] = this->data[num_ar] | mask;

        else
            if (this->getOne(num) == 1)
                this->data[num_ar] -= mask;

        // printf("(res - %lu)\n", this->data[num_ar]);
    }

    else
        printf("Unacceptable number!\n");
}


int BitArray::getOne(int num) {
    if (num > -1 && num < this->size_bit) {
        int num_ar = num / 8;
        unsigned char mask = 1 << num;
        unsigned char res = this->data[num_ar] & mask;
        if (res > 0) return 1;
        else return 0;
    }

    printf("Unacceptable number!\n");
    return -1;
}