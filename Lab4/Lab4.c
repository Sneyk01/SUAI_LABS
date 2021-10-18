#include <stdio.h>
int checkS(char symb) {
    if (symb > 47 && symb < 58) return 1;
    return 0;
}


int main() {
    int i = 0, minusMem = 0, mem = 0, dot = 0, dotMem = 0, amount = 0, flag = 0;
    double degree = 1, numb = 0;
    char a[10000] = "";
    double nums[10000] = {0};
    printf("Enter string (max 10000 symb)\n");
    fgets(&a, 10000, stdin);

    while (a[i] != 0) {
        if (a[i] == '-') {
            minusMem = i;
            i ++;
            while (checkS(a[i]) == 1 || a[i] == ',' || a[i] == '.') {
                if (a[i] == ',' || a[i] == '.') {
                    dot++;
                    dotMem = i;
                }
                mem = i;
                i++;
            }

            if (dot < 2) {
                if (dot == 0) {
                    for (int bf = mem; bf > minusMem; bf--) {
                        numb += (a[bf] - 48) * degree;
                        degree *= 10;
                    }
                }
                if (dot == 1) {
                    for (int d = 0; d < mem - dotMem; d++) degree /= 10;
                    //printf("\n%f\n", degreeF);
                    for (int bf = mem; bf > minusMem; bf--) {
                        if (bf != dotMem) {
                            //printf("%c|",a[bf]);
                            //printf("%f|%f ", (a[bf] - 48) * degree, degree);
                            numb += (a[bf] - 48) * degree;
                            degree *= 10;
                        }
                    }
                }

                degree = 1;
                numb *= -1;
                for (int checkArray = 0; checkArray < amount; checkArray++)
                    if (numb == nums[checkArray]) flag = 1;
                if (flag == 0) {
                    nums[amount] = numb;
                    amount++;
                    //printf("%f|%d ", numb, amount);
                } else flag = 0;
            }
        }
        else {
            i ++;
        }
        minusMem = 0;
        dotMem = 0;
        dot = 0;
        mem = 0;
        numb = 0;
    }
    for (int k = 0; k < amount; k++)
        printf("%f ", nums[k]);
    return 0;
}
