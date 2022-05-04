//
// Created by prgle on 03.05.2022.
//

#include "lib.h"


String::String() {
    this->data = nullptr;
    this->len = 0;
}


String::String(String &a) {
    this->len = a.len;
    this->data = new char[this->len];
    for(size_t i = 0; i < this->len; i++)
        this->data[i] = a.data[i];
}


void String::set(char* src) {
    if (src == nullptr || *src == 0) {
        this->data = nullptr;
        this->len = 0;
        return;
    }

    int i = 0, len_str = 0;
    while (src[i] != '\n' && src[i] != '\0')
        i++;

    len_str = i;
    char* data_str = new char[len_str + 1];
    i = 0;

    while (src[i] != '\0') {
        data_str[i] = src[i];
        i++;
    }

    data_str[i] = 0;

    delete[] this->data;
    this->data = data_str;
    this->len = len_str + 1;        // len + [0]
}


char* String::get() {
    char* new_data = new char[this->len];
    for(int i = 0; i < this->len; i++)
        new_data[i] = this->data[i];

    return new_data;
}


String String::operator+(const String &src) {
    size_t new_len = 0;
    new_len = this->len + src.len - 1; // [0][0] - [0]

    char* new_data = new char[new_len];

    int i;
    for (i = 0; i < (this->len - 1); i++)
        new_data[i] = this->data[i];

    for (int c = 0; c < src.len; c++)
        new_data[i++] = src.data[c];

    //printf("%s", new_data);

    String new_string;
    //new_string.set(new_data);
    new_string.data = new_data;
    new_string.len = new_len;

    //printf("%s", new_string.data);
    //printf("%d %d", new_string.len, new_len);

    return new_string;
}


void String::operator+=(const String &src) {
    *this = *this + src;
}


String& String::operator=(const String &src) {
    if (&src == this)
        return *this;

    this->set(src.data);
    return *this;
}


bool String::operator<(const String &src) const {
    if (src.len == 0 || this->len == 0) {
        printf("The string is empty!\n");
        return false;
    }

   char* symb1 = this->data;
   char* symb2 = src.data;

   while ((*symb1 != 0) && (*symb1 == *symb2)) {
       symb1++;
       symb2++;
   }

   if ((*symb1 - *symb2) < 0)
       return true;

   return false;
}


bool String::operator>(const String &src) const {
    if (src.len == 0 || this->len == 0) {
        printf("The string is empty!\n");
        return false;
    }

    return src<*this;
}


bool String::operator==(const String &src) const {
    if (src.len == 0 || this->len == 0) {
        printf("The string is empty!\n");
        return false;
    }

    char* symb1 = this->data;
    char* symb2 = src.data;

    while ((*symb1 != 0) && (*symb1 == *symb2)) {
        symb1++;
        symb2++;
    }

    if ((*symb1 - *symb2) == 0)
        return true;

    return false;
}

bool String::operator!=(const String &src) const {
    if (src.len == 0 || this->len == 0) {
        printf("The string is empty!\n");
        return false;
    }

    return !(*this == src);
}


bool String::operator<=(const String &src) const {
    if (src.len == 0 || this->len == 0) {
        printf("The string is empty!\n");
        return false;
    }

    return !(*this > src);
}


bool String::operator>=(const String &src) const {
    if (src.len == 0 || this->len == 0) {
        printf("The string is empty!\n");
        return false;
    }

    return !(*this < src);
}


String::~String() {
    delete[] this->data;
}


std::ostream& operator<< (std::ostream &out,const String &src) {
    if (src.data == nullptr || *src.data == 0) {
        out << "The string is empty!\n";
        return out;
    }

    out << "___\nString: " << src.data << "\nlen: " << src.len << "\n___\n";
    return out;
}


std::istream& operator>> (std::istream &in, String &src) {
    char* new_data = nullptr;
    char* temp = nullptr;
    char new_symb;
    int len = 1;

    while ((new_symb = in.get()) != '\n') {
        len++;
        temp = new char[len];
        temp[len - 2] = new_symb;
        temp[len - 1] = 0;

        if (new_data != nullptr)
            for (int i = 0; i < len - 2; i++)
                temp[i] = new_data[i];

        delete[] new_data;
        new_data = temp;
    }


    //printf("|%s|\n", new_data);
    src.set(new_data);
    delete(new_data);

    return in;
}
