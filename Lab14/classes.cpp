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


char* enter_color() {
    std::cout << "Enter color:";

    char* new_data = nullptr;
    char* temp = nullptr;
    char new_symb;
    int len = 1;

    //std::cin >> new_symb;
    while ((new_symb = std::cin.get()) != '\n') {
        len++;
        temp = new char[len];
        temp[len - 2] = new_symb;
        temp[len - 1] = 0;

        if (new_data != nullptr)
            for (int i = 0; i < len - 2; i++)
                temp[i] = new_data[i];

        delete[] new_data;
        new_data = temp;
        //printf("(%s) \n", new_data);
    }
    return new_data;
}


//_______ Animal _______


int Animal::last_num = 0;


Animal::Animal() {
    this->name = nullptr;

    this->num = 0;
    this->old = 0;
}


Animal::Animal(const Animal &src) {
    this->num = src.num;
    this->old = src.old;

    this->name = str_copy(src.name);
}


Animal::Animal(char *animal_name, unsigned int animal_old) {
    this->num = Animal::last_num + 1;
    Animal::last_num++;

    this->name = str_copy(animal_name);
    this->old = animal_old;
}


void Animal::print_animal() {
    std::cout << "Number: " << this->num << ", nickname: " << this->name << ", old: " << this->old << "\n";
}


Animal::~Animal() {
    delete[] name;
}


/*
Animal& Animal::operator=(const Animal &src) {
    if (&src  == this)
        return *this;

    delete[] this->name;

    this->name = str_copy(src.name);

    this->old = src.old;
    this->num = src.num;

    return *this;
}
*/


//_______ GOOSE _______


Goose::Goose() : Animal() {
    this->legs_color = nullptr;
    this->wings_color = nullptr;
    this->body_color = nullptr;
}


Goose::Goose(char* goose_name, unsigned int goose_old,
             char* goose_legs_color, char* goose_wings_color, char* goose_body_color) : Animal(goose_name, goose_old) {

    this->legs_color = str_copy(goose_legs_color);
    this->wings_color = str_copy(goose_wings_color);
    this->body_color = str_copy(goose_body_color);
}


Goose::Goose(const Goose &src) : Animal(src) {
    this->legs_color = str_copy(src.legs_color);
    this->wings_color = str_copy(src.wings_color);
    this->body_color = str_copy(src.body_color);
}


Goose::~Goose() {
    //delete[] name;

    delete[] this->legs_color;
    delete[] this->wings_color;
    delete[] this->body_color;
}


void Goose::paint() {
    delete[] this->legs_color;
    delete[] this->wings_color;
    delete[] this->body_color;

    char* color = enter_color();
    this->legs_color = str_copy(color);
    delete color;
    color = enter_color();
    this->wings_color = str_copy(color);
    delete color;
    color = enter_color();
    this->body_color = str_copy(color);
    delete color;
}


Goose& Goose::operator=(const Goose& src) {     //Как тут вызвать наследование?
    if (&src == this)                           //Нужен ли return если есть в базовом классе?
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


void Goose::print_animal(){
    std::cout << "Number: " << this->num << ", nickname: " << this->name << ", old: " << this->old;
    std::cout << ", legs color: " << this->legs_color << ", wings color: " << this->wings_color <<
                                    ", body color: " << this->body_color << "\n";
}


//_______ PENGUIN _______


Penguin::Penguin() {
    this->body_color = nullptr;
}


Penguin::Penguin(char *penguin_name, unsigned int penguin_old, char *penguin_body_color) : Animal(penguin_name, penguin_old) {
    this->body_color = str_copy(penguin_body_color);
}


Penguin::Penguin(const Penguin& src) : Animal(src) {
    this->body_color = str_copy(src.body_color);
}


void Penguin::paint() {
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


void Penguin::print_animal(){
    std::cout << "Number: " << this->num << ", nickname: " << this->name << ", old: " << this->old;
    std::cout << ", body color: " << this->body_color << "\n";
}


Penguin::~Penguin() {
    delete[] name;
    delete[] this->body_color;
}


//_______ OSTRICH _______


Ostrich::Ostrich() {
    this->legs_color = nullptr;
    this->wings_color = nullptr;
}


Ostrich::Ostrich(char *ostrich_name, unsigned int ostrich_old, char *ostrich_legs_color, char *ostrich_wings_color) :
                                                                                    Animal(ostrich_name, ostrich_old) {
    this->legs_color = str_copy(ostrich_legs_color);
    this->wings_color = str_copy(ostrich_wings_color);
}


Ostrich::Ostrich(const Ostrich& src) : Animal(src) {
    this->legs_color = str_copy(src.legs_color);
    this->wings_color = str_copy(src.wings_color);
}


void Ostrich::paint() {
    delete[] this->legs_color;
    this->legs_color = str_copy(this->wings_color);
}


Ostrich& Ostrich::operator=(const Ostrich &src) {
    if (&src == this)
        return *this;

    delete[] this->name;
    delete[] this->legs_color;
    delete[] this->wings_color;

    this->num = src.num;
    this->old = src.old;

    this->name = str_copy(src.name);
    this->legs_color = str_copy(src.legs_color);
    this->wings_color = str_copy(src.wings_color);

    return *this;
}


void Ostrich::print_animal(){
    std::cout << "Number: " << this->num << ", nickname: " << this->name << ", old: " << this->old;
    std::cout << ", legs color: " << this->legs_color << ", wings color: " << this->wings_color << "\n";
}


Ostrich::~Ostrich() {
    //delete[] name;
    delete[] this->legs_color;
    delete[] this->wings_color;
}


//_______ FARM _______
Farm::Farm() {
    this->Animals = nullptr;
    this->free_ind = 0;
    this->size = 0;
}


Farm::Farm(size_t size) {
    this->Animals = new Animal* [size];
    this->size = size;
    this->free_ind = 0;
}


void Farm::add_new_animal(Animal* a) {
    if (this->free_ind < this->size)
        this->Animals[this->free_ind++] = a;

    else {
        if (this->size == 0)
            this->size = 1;

        Animal** new_data = new Animal *[this->size * 2]; // What is it? (Animal**)

        for (int i = 0; i < this->free_ind; i++)    // if Animals is empty (free_ind)
            new_data[i] = this->Animals[i];

        delete this->Animals;                       // I special delete []

        this->Animals = new_data;
        this->size = this->size * 2;

        this->Animals[this->free_ind++] = a;
    }
}


void Farm::show_all_animals() {
    for (int i = 0; i < free_ind; i++)
        this->Animals[i]->print_animal();
}


void Farm::paint_all_animals() {
    for (int i = 0; i < free_ind; i++)
        this->Animals[i]->paint();
}


void Farm::delete_animal() {
    if (this->free_ind == 0)
        return;
    //this->Animals[this->free_ind - 1] = nullptr; // a[1] = o & a[2] = o -> error, класс удалит сам себя в конце?
    //std::cout<<"\n\n";
    //this->Animals[this->free_ind-1]->print_animal();
    delete this->Animals[this->free_ind-1];
    this->free_ind--;
}


Farm::~Farm() {
    for (int i = 0; i < free_ind; i++)
        delete Animals[i];             // Зачем в примере for с delete, если для всех классов будут свои диструкторы далее
    delete[] Animals;
}

