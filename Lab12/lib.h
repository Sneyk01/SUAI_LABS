//
// Created by prgle on 04.04.2022.
//

#ifndef LAB12_LIB_H
#define LAB12_LIB_H

#include <iostream>

class BitArray {
private:
    char *data;
    size_t size_bit;
public:
    BitArray (int size);
    void setOne (int value, int num);
    void setAll (int value);
    int getOne (int num);
    void printAll();
    void addNew (int value);
    void delOne();
    char* get();
    void set(char* new_data, size_t bit_count);
    void enter_bit();
    ~BitArray();

};

#endif //LAB12_LIB_H
