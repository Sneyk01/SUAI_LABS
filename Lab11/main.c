#include "lib.h"


int main() {
    char *str1;
    char *str2;

    printf("Enter main string:");
    while ((str1 = get_str()) == -1) {
        printf("Enter main string:");
    }
    printf("Enter array symbols:");
    while ((str2 = get_str()) == -1) {
        printf("Enter array symbols:");
    }

    printf("%p\n", strpbrk_my(str1, str2));
    printf("%p", strpbrk(str1, str2));
    return 0;
}
