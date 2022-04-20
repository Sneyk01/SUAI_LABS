#include "lib.h"

int main() {
    int size_ar = 9;

    BitArray a(size_ar);
    a.printAll();

    a.setOne(1, 2);
    a.setOne(100, 5);
    a.setOne(0, 8);
    a.printAll();

    a.setOne(0, 2);
    a.printAll();


    a.setAll(1);
    a.printAll();

    a.addNew(1);
    a.addNew(0);
    a.printAll();

    a.setAll(0);
    a.printAll();

    a.delOne();
    a.setAll(1);
    a.printAll();

    a.delOne();
    a.printAll();

    return 0;
}
