//
// Created by prgle on 20.05.2022.
//

#ifndef LAB14_CLASSES_H
#define LAB14_CLASSES_H


#include <iostream>


char* str_copy (const char* src);

/*class Farm {
private:
public:
    void add_new_animal();
    void delete_animal();
    void show_all_animals();
    void paint_all_animals(char* color);
};
*/


class Goose {
private:
    int num;
    static int last_num;
    char* name;
    unsigned int old;
    char* legs_color;
    char* wings_color;
    char* body_color;
public:
    Goose ();
    Goose (const Goose& a);
    Goose (char* goose_name, unsigned int goose_old, char* goose_legs_color, char* goose_wings_color, char* goose_body_color);
    void paint(char* new_legs_color, char* new_wings_color, char* new_body_color);
    Goose& operator=(const Goose& src);
    ~Goose();
};


class Penguin{
private:
    int num;
    static int last_num;
    char* name;
    unsigned int old;
    char* body_color;
public:
    Penguin();
    Penguin(const Penguin& src);
    Penguin(char* penguin_name, unsigned int penguin_old, char* penguin_body_color);
    void paint_black();
    Penguin& operator=(const Penguin& src);
    ~Penguin();
};


#endif //LAB14_CLASSES_H
