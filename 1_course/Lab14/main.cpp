// Реализовать do_func в классе Farm и с его помощью вывести всех животных и их количество


#include "classes.h"


int main() {

    Goose* g = new Goose("Ivan", 2, "pink", "white", "white");
    Penguin* p = new Penguin("Kavalski", 3, "white");
    Ostrich* o = new Ostrich("Ilya", 10, "pink", "white");
    Ostrich* o2 = new Ostrich("Ilya2", 8, "pink", "white");


    Farm f2;

    f2.add_new_animal(g);
    f2.add_new_animal(p);
    f2.add_new_animal(o);
    f2.add_new_animal(o2);

    f2.do_func(my_print_animal);

    std::cout << "\n" << f2.do_func(print_animals_count);


    Goose goo1("Ivan", 2, "pink", "white", "white");
    Goose goo2;
    goo2 = goo1;

    return 0;
}
