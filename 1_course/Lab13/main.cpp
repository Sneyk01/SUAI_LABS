#include "lib.h"


int main() {
    int num = 543;
    String a(num);

    a += ' ';
    a += (bool)0;
    a += 3116.1414;
    a += 5;
    a += "ABFD";

    std::cout << a;

    /*
    String b;
    b.set(" Hello world!");

    printf("%s\n", b.get());
    a = b;

    std::cout << a;

    //printf("\n| %d |\n", a == b);
    */
    /*
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
    */
    return 0;
}
