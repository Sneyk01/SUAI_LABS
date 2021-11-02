#include <stdio.h>

int checkS(char symb) {
    if (symb > 47 && symb < 58) return 1;
    return 0;
}

double getNum(int bf, int minusMem, double degree, double* numb, char* str, int dotMem) {
    for (bf; bf > minusMem; bf--) {
        if (bf != dotMem) {
            *numb += (str[bf] - 48) * degree;
            degree *= 10;
        }
    }
    return *numb * (-1);
}

void checkWord(char *a,int *word, int *iA, double *numb ) {
    int i = *iA;
    if (a[i] == 'o' && a[i + 1] == 'n' && a[i + 2] == 'e') {
        *word = 1;
        *numb = -1;
        *iA += 2;
    }
    if (a[i] == 't' && a[i + 1] == 'w' && a[i + 2] == 'o' && *word == 0) {
        *word = 1;
        *numb = -2;
        *iA += 2;
    }
    if (a[i] == 't' && a[i + 1] == 'h' && a[i + 2] == 'r' && a[i + 3] == 'e' && a[i + 4] == 'e' && *word == 0) {
        *word = 1;
        *numb = -3;
        *iA += 3;
    }
    if (a[i] == 'f' && a[i + 1] == 'o' && a[i + 2] == 'u' && a[i + 3] == 'r' && *word == 0) {
        *word = 1;
        *numb = -4;
        *iA += 3;
    }
    if (a[i] == 'f' && a[i + 1] == 'i' && a[i + 2] == 'v' && a[i + 3] == 'e' && *word == 0) {
        *word = 1;
        *numb = -5;
        *iA += 3;
    }
    if (a[i] == 's' && a[i + 1] == 'i' && a[i + 2] == 'x' && *word == 0) {
        *word = 1;
        *numb = -6;
        *iA += 2;
    }
    if (a[i] == 's' && a[i + 1] == 'e' && a[i + 2] == 'v' && a[i + 3] == 'e' && a[i + 4] == 'n' && *word == 0) {
        *word = 1;
        *numb = -7;
        *iA += 4;
    }
    if (a[i] == 'e' && a[i + 1] == 'i' && a[i + 2] == 'g' && a[i + 3] == 'h' && a[i + 4] == 't' && *word == 0) {
        *word = 1;
        *numb = -8;
        *iA += 4;
    }
    if (a[i] == 'n' && a[i + 1] == 'i' && a[i + 2] == 'n' && a[i + 3] == 'e' && *word == 0) {
        *word = 1;
        *numb = -9;
        *iA += 3;
    }
    if (a[i] == 't' && a[i + 1] == 'e' && a[i + 2] == 'n' && *word == 0) {
        *word = 1;
        *numb = -10;
        *iA += 2;
    }
}

int main() {
    printf("*This program supports decimal numbers up to five decimal places, other digits are ignored*\n");
    int i = 0, minusMem = 0, mem = 0, dot = 0, dotMem = 0, amount = 0, flag = 0, word = 0, intNumb = 0;
    double degree = 1, numb = 0;
    char a[10000] = "";
    double nums[10000] = {0};
    printf("Enter string (max 10000 symb)\n");
    fgets(&a, 10000, stdin);

    while (a[i] != 0) {
        if (a[i] == '-') {
            minusMem = i;
            i++;
            checkWord(a, &word, &i, &numb);
            if (word == 1)
                i++;
            while ((checkS(a[i]) == 1 || a[i] == ',' || a[i] == '.') && word == 0) {
                if (a[i] == ',' || a[i] == '.') {
                    dotMem = i;
                    dot++;
                }
                mem = i;
                i++;
            }
            //printf("%d", numb);
            if ((dot < 2 && mem > 0) || word == 1) {
                if (dot == 0 && word == 0)
                    numb = getNum(mem, minusMem, degree, &numb,&a[0], 0);

                if (dot == 1 && word == 0) {
                    if (mem - dotMem > 5) mem = dotMem + 5;
                    for (int d = 0; d < mem - dotMem; d++)  degree /= 10;
                    numb = getNum(mem, minusMem, degree, &numb, a, dotMem);
                }

                for (int checkArray = 0; checkArray < amount; checkArray++) {

                    //printf("%f|%f ||", numb, nums[checkArray]);
                    if (numb == nums[checkArray]) flag = 1;
                    //printf(" %d \n", flag);
                }

                if (flag == 0) {
                    nums[amount] = numb;
                    amount++;
                }
                else    flag = 0;
            }
        }
        else    i++;

        degree = 1;
        minusMem = 0;
        dotMem = 0;
        dot = 0;
        mem = 0;
        numb = 0;
        word = 0;
    }
    for (int n = 0; n < amount; n++) {
        intNumb = nums[n];
        if (intNumb == nums[n])   printf("%d ", intNumb);
        else    printf("%f ", nums[n]);
    }
    return 0;
}
