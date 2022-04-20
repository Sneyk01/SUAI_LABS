#include "lib.h"

int main() {
    int size_ar = 9;

    BitArray a(9);
    a.enter_bit();
    a.printAll();

    a.addNew(1);
    a.printAll();

    a.setAll(0);
    a.printAll();

    a.delOne();
    a.printAll();



    return 0;
}
