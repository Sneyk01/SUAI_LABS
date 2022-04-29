#include "lib.h"

int main() {
    FILE *src = open_file(PATH);
    FILE *output = fopen("D:\\Project\\C\\Lab10\\test_copy.c", "wt");
    if (src == -1) return -1;

    char *cur_string;

    while (feof(src) == 0) {
        cur_string = get_str(src);
        analyze_string(cur_string, output);
        free (cur_string);
    }

    fclose(src);
    fclose(output);

    return 0;
}
