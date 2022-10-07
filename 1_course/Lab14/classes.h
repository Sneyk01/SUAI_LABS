//
// Created by prgle on 20.05.2022.
//

#ifndef LAB14_CLASSES_H
#define LAB14_CLASSES_H


#include <iostream>


char* str_copy (const char* src);
char* enter_color();


class Animal {
protected:
    int num;
    static int last_num;
    char* name;
    unsigned int old;
public:
    Animal();
    Animal(const Animal& src);
    Animal(char* animal_name, unsigned int animal_old);
    virtual ~Animal();
    virtual Animal& operator=(const Animal& src);
    virtual void print_animal();            // А можно ли вызвать часть от сюда и часть из потомка?
    virtual void paint() {}
};


class Goose: public Animal{
protected:
    char* legs_color;
    char* wings_color;
    char* body_color;
public:
    Goose();
    Goose (const Goose& a);
    Goose (char* goose_name, unsigned int goose_old,
           char* goose_legs_color, char* goose_wings_color, char* goose_body_color);

    virtual void paint();
    Goose& operator=(const Goose& src);
    virtual void print_animal();
    virtual ~Goose();
};


class Penguin: public Animal{
private:
    char* body_color;
public:
    Penguin();
    Penguin(const Penguin& src);
    Penguin(char* penguin_name, unsigned int penguin_old, char* penguin_body_color);
    virtual void paint();
    Penguin& operator=(const Penguin& src);
    virtual void print_animal();
    virtual ~Penguin();
};


class Ostrich: public Animal{
private:
    char* legs_color;
    char* wings_color;
public:
    Ostrich();
    Ostrich(const Ostrich& src);
    Ostrich(char* ostrich_name, unsigned int ostrich_old, char* ostrich_legs_color, char* ostrich_wings_color);
    virtual void paint();
    Ostrich& operator=(const Ostrich& src);
    virtual void print_animal();
    virtual ~Ostrich();
};


class Farm {
protected:
    Animal** Animals;
    size_t free_ind;
    size_t size;
public:
    Farm();
    Farm(size_t size);
    void add_new_animal(Animal* a);
    void delete_animal();
    void show_all_animals();
    void paint_all_animals();
    int do_func(int (*func)(Animal* src));      // Возвращает последнее возвращенное функцией значение
    ~Farm();
};


int my_print_animal(Animal* src);
int print_animals_count(Animal* src);

#endif //LAB14_CLASSES_H
