//
// Created by prgle on 03.05.2022.
//

#ifndef LAB13_LIB_H
#define LAB13_LIB_H

#include <iostream>

class String {
private:
    char *data;
    size_t len;
public:
    String();
    void set(char* src);
    char* get();
    String operator+(const String& data);
    void operator+=(const String& data);
    void operator=(const String& data);
    bool operator==(const String& data);
    bool operator!=(const String& data);
    bool operator>(const String& data);
    bool operator<(const String& data);
    bool operator>=(const String& data);
    bool operator<=(const String& data);
    ~String();
};

#endif //LAB13_LIB_H
