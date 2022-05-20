#include "classes.h"


int main() {
    std::cout << "Hello, World!" << std::endl;

    Goose g("Ivan", 2, "pink", "white", "white");
    g.paint("orange", "orange", "orange");
    Penguin p("Kavalski", 3, "white");
    Penguin p2;
    p2 = p;
    return 0;
}
