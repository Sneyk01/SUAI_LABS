#include "lib.h"


int main() {
    //std::cout << "Hello, World!" << std::endl;
    String a;
    a.set("Hello world");
    printf("%s", a.get());
    return 0;
}
