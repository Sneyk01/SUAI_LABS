#include "lib.h"

int main() {
    FILE* src = open_file(PATH);
    int* i = input_file(src);

    if (i == -1)
        return -1;

    printf("Your multiply: ");
    output(i);

    printf("Enter degree:\n");
    int degree = get_degree();

    if (degree > i[0]) printf("New multiply: 0");
    else {
        deg(i, degree);
        printf("New multiply: ");
        output(i);
    }

    FILE* res = fopen(PATH_RES, "wt");
    output_file(res, i);

    free(i);
    fclose(src);
    fclose(res);

    return 0;
}
