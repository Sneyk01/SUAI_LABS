#include "lib.h"

int main() {
    // std::cout << "Hello, World!" << std::endl;
    // printf("AC/DC\n");
    int size_ar = 9;
    BitArray a(size_ar);

    for (int i = 0; i < size_ar; i++)
        printf("%d", a.getOne(i));
    printf("\n");

    a.setOne(1, 2);
    a.setOne(100, 5);
    a.setOne(-100, 7);
    a.setOne(0, 8);

    for (int i = 0; i < size_ar; i++)
        printf("%d", a.getOne(i));
    printf("\n");

    a.setOne(0, 2);

    a.printAll();

    return 0;
}
