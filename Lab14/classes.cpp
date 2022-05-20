//
// Created by prgle on 20.05.2022.
//

#include "classes.h"


char* str_copy (const char* src) {
    if (src == nullptr)
        return nullptr;

    int len = 0;
    while (src[len] != 0 && src[len] != '\n')
        len++;

    char* new_data = new char[len + 1];

    for (int i = 0; i <= len; i++)
        new_data[i] = src[i];

    return new_data;
}

//_______ GOOSE _______


int Goose::last_num = 0;


Goose::Goose() {
    this->num = 0;
    //Goose::last_num++;
    this->name = nullptr;
    this->legs_color = nullptr;
    this->wings_color = nullptr;
    this->body_color = nullptr;

    this->old = 0;
}


Goose::Goose(char* goose_name, unsigned int goose_old, char* goose_legs_color, char* goose_wings_color, char* goose_body_color) {
    this->num = Goose::last_num + 1;
    Goose::last_num++;

    this->name = str_copy(goose_name);
    this->legs_color = str_copy(goose_legs_color);
    this->wings_color = str_copy(goose_wings_color);
    this->body_color = str_copy(goose_body_color);

    this->old = goose_old;
}


Goose::Goose(const Goose &a) {
    this->num = a.num;
    this->old = a.old;

    this->name = str_copy(a.name);
    this->legs_color = str_copy(a.legs_color);
    this->wings_color = str_copy(a.wings_color);
    this->body_color = str_copy(a.body_color);
}


Goose::~Goose() {
    delete[] this->name;
    delete[] this->legs_color;
    delete[] this->wings_color;
    delete[] this->body_color;
}


void Goose::paint(char *new_legs_color, char *new_wings_color, char *new_body_color) {
    delete[] this->legs_color;
    delete[] this->wings_color;
    delete[] this->body_color;

    this->legs_color = str_copy(new_legs_color);
    this->wings_color = str_copy(new_wings_color);
    this->body_color = str_copy(new_body_color);
}


Goose& Goose::operator=(const Goose& src) {
    if (&src == this)
        return *this;

    this->num = src.num;
    this->old = src.old;

    delete[] this->name;
    delete[] this->legs_color;
    delete[] this->wings_color;
    delete[] this->body_color;

    this->name = str_copy(src.name);
    this->legs_color = str_copy(src.legs_color);
    this->wings_color = str_copy(src.wings_color);
    this->body_color = str_copy(src.body_color);

    return *this;
}


//_______ PENGUIN _______


int Penguin::last_num = 0;


Penguin::Penguin() {
    this->num = 0;

    this->name = nullptr;
    this->body_color = nullptr;

    this->old = 0;
}


Penguin::Penguin(char *penguin_name, unsigned int penguin_old, char *penguin_body_color) {
    this->num = Penguin::last_num + 1;
    Penguin::last_num++;

    this->old = penguin_old;

    this->name = str_copy(penguin_name);
    this->body_color = str_copy(penguin_body_color);
}


Penguin::Penguin(const Penguin& src) {
    this->num = src.num;
    this->old = src.old;

    this->name = str_copy(src.name);
    this->body_color = str_copy(src.body_color);
}


void Penguin::paint_black() {
    delete[] this->body_color;
    this->body_color = str_copy("black");
}


Penguin& Penguin::operator=(const Penguin& src) {
    if (&src == this)
        return *this;

    delete[] this->name;
    delete[] this->body_color;

    this->num = src.num;
    this->old = src.old;
    this->name = str_copy(src.name);
    this->body_color = str_copy(src.body_color);

    return *this;
}


Penguin::~Penguin() {
    delete[] this->name;
    delete[] this->body_color;
}