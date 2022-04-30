//
// Created by prgle on 04.04.2022.
//

#include "lib.h"

BitArray::BitArray() {
    this->data = nullptr;
    this->size_bit = 0;
}


BitArray::BitArray(unsigned int value) {
    int deg = 0, size_ar = 0;
    unsigned int temp = value;

    while (temp > 0) {                          // bit count
        temp /= 2;
        deg++;
    }

    if (deg == 0)
        deg++;

    size_ar = deg / 8;                          // char count
    if (deg % 8 != 0)
        size_ar++;

    this->data = new char [size_ar];
    this->size_bit = deg;

    for (int i = 0; i < size_ar; i++)
        this->data[i] = 0;

    unsigned int mask, bit_value;

    for (int i = 0; i < deg; i++) {
        mask = 1 << i;
        bit_value = value & mask;
        if (bit_value > 0) bit_value = 1;

        this->setOne(bit_value, i);
    }
}

/* BitArray::BitArray(int size) {
    int size_ar = 0;
    if (size > 0 && size < 33) {
        size_ar = size / 8;
        if (size % 8 != 0)
            size_ar++;

        //printf("Array size - %d\n", size_ar);
        this->data = new char [size_ar];
        this->size_bit = size;

        for (int i = 0; i < size_ar; i++)
            this->data[i] = 0;

    }

    else {
        printf("Value is out of size off limits\n");
        this->data = nullptr;
        this->size_bit = 0;
    }

    // printf("_%lu\n\n", data[0]);
} */


BitArray::~BitArray() {
    delete[] data;
}


void BitArray::setOne(int value, int num) {
    if (this->data == nullptr) {
        printf("Data error!\n");
        return;
    }

    if (num > -1 && num < this->size_bit) {
        if (value < 0) {
            printf("Value error!\n");
            return;
        }

        unsigned char mask = 1 << (num % 8);
        //printf("(mask - %d)\n", mask);

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
    if (this->data == nullptr) {
        printf("Data error!\n");
        return -1;
    }

    if (num > -1 && num < this->size_bit) {
        int num_ar = num / 8;
        unsigned char mask = 1 << (num % 8);
        unsigned char res = this->data[num_ar] & mask;
        if (res > 0) return 1;
        else return 0;
    }

    printf("Unacceptable number!\n");
    return -1;
}


void BitArray::printAll() {
    if (this->data == nullptr) {
        printf("Data error!\n");
        return;
    }

    for (int i = 0; i < this->size_bit; i++)
        printf("%d", this->getOne(i));
    printf("\n");
}


void BitArray::setAll(int value) {
    //printf("%d\n", this->size_bit);
    if (this->data == nullptr) {
        printf("Data error!\n");
        return;
    }

    if (value < 0) {
        printf("Value error!\n");
        return;
    }

    for (int i = 0; i < this->size_bit; i++)
        setOne(value, i);
}


void BitArray::addNew(int value) {
    if (this->size_bit > 31) {
        printf("Data error!\n");
        return;
    }

    if (this->data == nullptr) {
    char* new_data = new char[1];
    new_data[0] = 0;
    this->data = new_data;
    this->size_bit = 1;
    this->setOne(value, 0);
    return;
    }

    if (this->size_bit % 8 == 0) {                          //NEED NEW BYTE
        size_t new_size_ar = (this->size_bit / 8) + 1;      // 16 bit -> 17 bit => 2 byte -> 3 byte
        char* data_copy = new char [new_size_ar];           //                    [0,1]     [0,1,2]
        for (int i = 0; i < (new_size_ar - 1); i++)
            data_copy[i] = this->data[i];

        data_copy[new_size_ar - 1] = 0;                     //CLEAR NEW BYTE
        delete[] this->data;
        this->data = data_copy;
    }

    this->size_bit++;
    this->setOne(value, this->size_bit - 1);
}


void BitArray::delOne() {
    if (this->size_bit < 1 || this->data == nullptr) {
        printf("Data error!\n");
        return;
    }

    if (this->size_bit % 8 == 1) {                          //NEED DEL BYTE
        size_t new_size_ar = this->size_bit / 8;            // 17 bit -> 16 bit => 3 byte -> 2 byte
                                                            //                     [0,1,2]  [0,1]
        if (new_size_ar == 0) {
            this->data = nullptr;
            this->size_bit = 0;
            return;
        }

        char* data_copy = new char [new_size_ar];
        for (int i = 0; i < new_size_ar; i++)
            data_copy[i] = this->data[i];

        delete[] this->data;
        this->data = data_copy;
    }

    this->size_bit--;
}


char* BitArray::get() {
    size_t size_ar = this->size_bit / 8;
    if (this->size_bit % 8 != 0)
        size_ar++;

    char* new_arr = new char[size_ar];
    for (int i = 0; i < size_ar; i++)
        new_arr[i] = this->data[i];

    return new_arr;
}


void BitArray::set(char* new_data, size_t bit_count) {
    size_t size_ar = bit_count / 8;
    if (bit_count % 8 != 0)
        size_ar++;

    char* new_data_copy = new char[size_ar];
    for (int i = 0; i < size_ar; i++)
        new_data_copy[i] = new_data[i];

    delete[] this->data;
    this->data = new_data_copy;
    this->size_bit = bit_count;
}


void BitArray::enter_bit() {
    int count = 0;
    printf("Enter bit count:\n");
    while (scanf("%d", &count) != 1) {
        while (getchar() != '\n') {}
        printf("Enter bit count:\n");
    }

    if (count < 1 || count > 32) {
        printf("Data error!\n");
        return;
    }
    // printf("(%d)\n", count);
    //BitArray new_array(count);
    this->size_bit = count;
    size_t size_ar = count / 8;
    if (count % 8 != 0)
        size_ar++;
    char* new_array = new char[size_ar];
    delete[] this->data;
    this->data = new_array;
    // new_array.printAll();
    int el = 0;

    for (int i = 0; i < count; i++) {
        printf("Enter element %d:", i);
        while (scanf("%d", &el) != 1) {
            while (getchar() != '\n') {}
            printf("Enter element %d:\n", i);
        }
        this->setOne(el, i);

        // new_array.printAll();
        // printf("%d %d\n", el, i);
    }
    //this->printAll();
    //new_array.printAll();
    //delete[] this->data;
    //this->set(new_array.data, count);
}


void BitArray::printAllRevers() {
    if (this->data == nullptr) {
        printf("Data error!\n");
        return;
    }

    for (int i = size_bit - 1; i > -1; i--)
        printf("%d", this->getOne(i));
    printf("\n");
}