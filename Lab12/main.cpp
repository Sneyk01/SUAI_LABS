#include "lib.h"

int main() {

    BitArray a(9568);
    a.printAll();

    printf("\nRevers output:");
    a.printAllRevers();
    printf("\n");

    a.addNew(1);
    a.printAll();

    a.setAll(0);
    a.printAll();

    a.delOne();
    a.printAll();

    return 0;
}
