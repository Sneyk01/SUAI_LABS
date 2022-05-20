#include "classes.h"


int main() {
    std::cout << "Hello, World!" << std::endl;

    Goose g("Ivan", 2, "pink", "white", "white");
    Penguin p("Kavalski", 3, "white");
    Ostrich o("Ilya", 10, "pink", "white");

    Farm f1;
    Farm f2(10);

    f1.add_new_animal(&g);
    f1.add_new_animal(&p);
    f1.add_new_animal(&o);
    f1.add_new_animal(&o);
    f1.show_all_animals();

    f1.delete_animal();
    f1.delete_animal();
    f1.delete_animal();
    f1.delete_animal();
    f1.paint_all_animals();
    f1.show_all_animals();

    std::cout << "\n";
    f2.add_new_animal(&g);
    f2.add_new_animal(&p);
    f2.add_new_animal(&o);
    f2.show_all_animals();

    return 0;
}
