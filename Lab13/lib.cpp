//
// Created by prgle on 03.05.2022.
//

#include "lib.h"


String::String() {
    this->data = nullptr;
    this->len = 0;
}


void String::set(char* src) {
    int i = 0, len_str = 0;
    while (src[i] != '\n' && src[i] != '\0') {
        i++;
        len_str++;
    }

    char* data_str = new char[len_str + 1];
    i = 0;
    while (src[i] != '\n' && src[i] != '\0') {
        data_str[i] = src[i];
        i++;
    }
    data_str[i] = 0;

    delete this->data;
    this->data = data_str;
    this->len = len_str + 1;        // len + [0]
}


char* String::get() {
    char* new_data = new char[this->len];
    for(int i = 0; i < this->len; i++)
        new_data[i] = this->data[i];

    return new_data;
}


String::~String() {
    delete[] data;
}
