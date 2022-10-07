#include "lib.h"

int main() {

    BitArray a(395);
    printf("Your array:");
    a.printAll();

    printf("\nRevers output:");
    a.printAllRevers();
    printf("\n");

    printf("Add new bit (1):");
    a.addNew(1);
    a.printAll();

    printf("Set all bit (0):");
    a.setAll(0);
    a.printAll();

    printf("Delete last bit:");
    a.delOne();
    a.printAll();

    return 0;
}
