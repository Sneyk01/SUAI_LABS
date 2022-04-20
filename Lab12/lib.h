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
    int getOne (int num);
    ~BitArray();

};

#endif //LAB12_LIB_H
