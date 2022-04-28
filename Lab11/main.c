#include "lib.h"


int main() {
    char *str1;
    char *str2;

    printf("Enter the main string:");
    while ((str1 = get_str()) == -1) {
        printf("Enter the main string:");
    }
    printf("Enter an array of symbols:");
    while ((str2 = get_str()) == -1) {
        printf("Enter an array of symbols:");
    }

    //printf("%p\n", &(str1[0]));
    printf("%d\n", strcspn_my(str1, str2));
    printf("%d", strcspn(str1, str2));
    return 0;
}
