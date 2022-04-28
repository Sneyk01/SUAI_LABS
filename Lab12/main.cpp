#include "lib.h"

int main() {

    BitArray a(9);
    a.printAll();

    a.addNew(1);
    a.printAll();

    a.setAll(0);
    a.printAll();

    a.delOne();
    a.printAll();

    return 0;
}
