//
// Created by prgle on 03.05.2022.
//

#include "lib.h"


String::String() {
    this->data = nullptr;
    this->len = 0;
}


String::String(int a) {
    if (a == 0) {
        this->data = nullptr;
        this->len = 0;
    }

    char* new_string;
    int temp = a, len_s = 0, degree = 1;

    while (temp > 0) {
        temp /= 10;
        len_s++;
    }

    new_string = new char[len_s + 1];
    for (int i = 1; i < len_s; i++) {
        degree *= 10;
    }

    temp = a;
    for (int i = 0; i < len_s; i++) {
        new_string[i] = (temp / degree) + '0';
        temp -= (temp / degree) * degree;
        degree /= 10;
    }
    new_string[len_s] = '\0';
    this->data = new_string;
    this->len = len_s + 1;
}


String::String(bool a) {
    this->data = nullptr;
    this->len = 0;

    if (a == 0)
        this->set("False");
    else
        this->set("True");
}


String::String(const char* a) {
    //std::cout<<"char*\n";
    this->data = nullptr;
    this->len = 0;

    int len_str = 0;
    while (a[len_str] != '\n' && a[len_str] != '\0')
        len_str++;

    //std::cout << len_str;
    char* new_data = new char[len_str + 1];

    for (int i = 0; i < len_str; i++)
        new_data[i] = a[i];

    new_data[len_str] = '\0';
    this->data = new_data;
    this->len = len_str + 1;
}


String::String(char a) {
    this->data = new char[2];
    this->data[0] = a;
    this->data[1] = '\0';
    this->len = 2;
}


String::String(float a) {
    this->data = nullptr;
    this->len = 0;

    float b = a - (int)a;
    int c = 0;

    while (b != 0) {
        //std::cout << b << '\n';
        a *= 10;
        b = a - (int)a;
        c++;
    }

    String new_str((int)a);
    //std::cout<<c << " " << a << "\n";
    *this = new_str;
    char *str = this->get();
    char *new_s = new char[this->len + 1];
    int i2 = 0;
    for (int i = 0; i < this->len; i++) {
        if (this->len - 1 - c == i)
            new_s[i] = ',';
        else
            new_s[i] = str[i2++];
    }
    new_s[this->len] = '\0';
    delete str;

    delete[] this->data;
    this->data = new_s;
    this->len++;

}


String::String(double a) {
    this->data = nullptr;
    this->len = 0;

    double b = a - (int)a;
    int c = 0;
    int temp = a;

    while (b > 0.000001 && b < 1) {
        //std::cout << b << '\n';
        a *= 10;
        b = a - (long long int)a;
        if ( b > 1) {
            a /= 10;
            break;
        }
        c++;
        if (c > 8) {
            a /= 10;
            c--;
            break;
        }

    }

    String new_str(temp);
    //std::cout<<c << " " << (long long int)a << "\n";
    *this = new_str;
    char *str = this->get();
    char *new_s = new char[this->len + c + 1];
    //std::cout<<this->len + c + 1 << " " << (long long int)a << "\n";
    int i2 = 0;
    for (int i = 0; i < this->len - 1; i++)                     //*****.0
        new_s[i2++] = str[i];

    new_s[i2++] = ',';
    b = a - temp * pow(10, c);
    //std::cout<<(int)b << "\n";


    double temp2 = floor(b);                                           // PREPARATION
    int len_s = 0, degree = 1;

    while (temp2 >= 1) {
        temp2 /= 10;
        len_s++;
    }

    for (int i = 1; i < len_s; i++) {
        degree *= 10;
    }
    temp2 = floor(b);

    for (int i = this->len + 1; i < this->len + c + 1; i++) {   //0.*******
        new_s[i2++] = floor(temp2 / degree) + '0';
        temp2 -= floor(temp2 / degree) * degree;
        degree /= 10;
    }

    new_s[this->len + c] = '\0';

    delete[] str;
    delete[] this->data;
    this->data = new_s;
    this->len += (c + 1);

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


bool operator<(const String& a, const String& b) {
    if (b.len == 0 || a.len == 0) {
        printf("The string is empty!\n");
        return false;
    }

   char* symb1 = a.data;
   char* symb2 = b.data;

   while ((*symb1 != 0) && (*symb1 == *symb2)) {
       symb1++;
       symb2++;
   }

   if ((*symb1 - *symb2) < 0)
       return true;

   return false;
}


bool operator>(const String& a, const String& b) {
    if (b.len == 0 || a.len == 0) {
        printf("The string is empty!\n");
        return false;
    }

    return b<a;
}


bool operator==(const String& a, const String& b) {
    if (b.len == 0 || a.len == 0) {
        printf("The string is empty!\n");
        return false;
    }

    char* symb1 = a.data;
    char* symb2 = b.data;

    while ((*symb1 != 0) && (*symb1 == *symb2)) {
        symb1++;
        symb2++;
    }

    if ((*symb1 - *symb2) == 0)
        return true;

    return false;
}


bool operator!=(const String& a, const String& b) {
    if (b.len == 0 || a.len == 0) {
        printf("The string is empty!\n");
        return false;
    }

    return !(a == b);
}


bool operator<=(const String& a, const String& b) {
    if (b.len == 0 || a.len == 0) {
        printf("The string is empty!\n");
        return false;
    }

    return !(a > b);
}


bool operator>=(const String& a, const String& b){
    if (b.len == 0 || a.len == 0) {
        printf("The string is empty!\n");
        return false;
    }

    return !(a < b);
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
