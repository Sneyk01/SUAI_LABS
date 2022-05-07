//
// Created by prgle on 03.05.2022.
//

#ifndef LAB13_LIB_H
#define LAB13_LIB_H

#include <iostream>
#include <string>

class String {
private:
    char* data;
    size_t len;
public:
    String();
    String(String& a);
    String(int a);
    String(char a);
    String(float a);
    String(double a);
    String(bool a);
    String(const char* a);

    void set(char* src);
    char* get();
    String operator+(const String& src);
    void operator+=(const String& src);
    String& operator=(const String& src);


    friend bool operator==(const String& a, const String& b);
    friend bool operator!=(const String& a, const String& b);
    friend bool operator>(const String& a, const String& b);
    friend bool operator<(const String& a, const String& b);
    friend bool operator>=(const String& a, const String& b);
    friend bool operator<=(const String& a, const String& b);

    friend std::ostream& operator<< (std::ostream &out, const String &src);
    friend std::istream& operator>> (std::istream &in, String &src);

    ~String();
};

#endif //LAB13_LIB_H
