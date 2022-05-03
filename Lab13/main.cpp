#include "lib.h"


int main() {
    //std::cout << "Hello, World!" << std::endl;
    String a;
    a.set("Hello world");
    printf("%s\n", a.get());

    String b;
    b.set(" I am super code!");
    printf("%s\n", b.get());

    String c;
    c = a + b;
    b += a;
    printf("%s | ", a.get());
    printf("%s\n", b.get());
    printf("%d\n", a <= b);

    b = a;
    printf("%d\n", b == a);

    return 0;
}
