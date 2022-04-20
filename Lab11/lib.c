#include "lib.h"


char* get_str() {
    char chr;
    char *str1 = 0;
    int len = 0;

    while ((chr = getchar()) != '\n') {
        str1 = (char* ) realloc(str1, len + sizeof(char) + sizeof(char)*2);
        str1[len++] = chr;
    }
    if (len == 0)
        return -1;
    str1[len++] = '\n';
    str1[len] = 0;
    return str1;
}


size_t strcspn_my (const char * str1, const char * str2) {
    int i = 0, i2 = 0, count = 0;
    char cur_char = 0;

    while(str1[i] != 0 && str1[i] != '\n') {
        cur_char = str1[i++];
        i2 = 0;

        while(str2[i2] != 0 && str2[i2] != '\n') {
            if (cur_char == str2[i2++])
                return count;
        }

        count++;
    }

    return count;
}


char* strpbrk_my (const char *str1, const char *str2) {
    int i = 0, i2 = 0, count = 0;
    char cur_char = 0;

    while(str1[i] != 0 && str1[i] != '\n') {
        cur_char = str1[i++];
        i2 = 0;

        while(str2[i2] != 0 && str2[i2] != '\n') {
            if (cur_char == str2[i2++])
                return (str1 + count);
        }

        count++;
    }

    return (str1 + count);
}