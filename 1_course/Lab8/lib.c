//
// Created by prgle on 15.02.2022.
//


#include "lib.h"


int* input() {
    int degree = -1;
    printf("Enter polynomial degree:\n");
    while (scanf("%d", &degree) != 1 || degree < 0) {
        printf("Input error! Enter polynomial degree:\n");
        while (getchar() != '\n') {}
    }

    int* polynomial = (int*) malloc(((degree + 2) * sizeof (int)));

    polynomial[0] = degree;
    for (int i = 1; i <= degree + 1; i++)   {
        printf("Enter %d-th coef:\n", i - 1);
        while (scanf("%d", &polynomial[i]) != 1)    {
            printf("Input error! Enter %d-th coef:\n", i - 1);
            while (getchar() != '\n') {}
        }
    }
    return polynomial;
}


void output(int* data) {
    for (int c = 1; c <= (data[0] + 1); c++) {
        if ((c - 1) == 0) printf("%d", data[c]);                // x^0
        else if ((c - 1) == 1) printf("%d*x", data[c]);         // x^1
        else printf("%d*x^%d", data[c], c - 1);

        if (c <= data[0]) printf(" + ");
        else printf("\n");
    }
}

void deg(int* i, int degr)    {
    for (int d = 0; d < degr; d++) {
        for (int c = 2; c <= (i[0] + 1); c++) {
            i[c - 1] = i[c] * (c - 1);
        }
        i[i[0] + 1] = 0;
        i[0] -= 1;
    }
}


int get_degree(){
    int degree;
    while (scanf("%d", &degree) != 1 || degree < 1) {
        printf("Input error! Enter degree:\n");
        while (getchar() != '\n') {}
    }
    return degree;
}


FILE* open_file(char *path) {
    FILE* src;
    src = fopen(path, "rt");

    if (src == NULL) {
        printf("File open error!\n");
        return -1;
    }

    return src;
}


int* input_file(FILE* src) {
    char chr;
    int* data;
    int size = 0, flag = 0;

    while ((chr = getc(src)) != '\n') {
        if (feof(src) == 1)
            return -1;
        //printf("\n__%d__\n", chr);
        if (chr > 47 && chr < 58)
            size = size * 10 + (chr - 48);
        else {
            printf("Data error!\n");
            return -1;
        }
    }

    printf("Size: %d\n", size);
    data = (int*) malloc( (size + 2) * sizeof(int));
    data[0] = size;

    for (int i = 1; i <= (size + 1); i++) {
        data[i] = get_num(src, &flag);
        if (flag == 1)
            return -1;
    }

    return data;
}


int get_num(FILE* src, int* flag) {
    char chr;
    int num = 0, first_symbol = 1, sign = 1;

    chr = getc(src);
    //printf("%d %c\n", chr, chr);

    while ((chr != '\n') && (chr != ' ') && (chr != '\0')) {
        if (feof(src) == 1)
            break;

        if (first_symbol == 1 && chr == '-') {
            first_symbol = 0;
            sign = -1;
        }
        else if (chr < 48 || chr > 57) {
            printf("Data error!");
            *flag = 1;
            return -1;
        }

        first_symbol == 0;
        if (chr > 47 && chr < 58)
            num = num * 10 + (chr - 48);

        chr = getc(src);
    }

    num *= sign;

    return num;
}


void output_file(FILE* src ,int* data) {
    for (int c = 1; c <= (data[0] + 1); c++) {
        if ((c - 1) == 0) fprintf(src,"%d", data[c]);                // x^0
        else if ((c - 1) == 1) fprintf(src,"%d*x", data[c]);         // x^1
        else fprintf(src,"%d*x^%d", data[c], c - 1);

        if (c <= data[0]) fprintf(src," + ");
        else fprintf(src,"\n");
    }
}
