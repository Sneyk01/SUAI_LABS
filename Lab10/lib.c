#include "lib.h"

FILE* open_file(char *path) {
    FILE *src;
    src = fopen(path, "rt");
    if (src == NULL) {
        printf("File open error!");
        return -1;
    }
    return src;
}


int save_pointer(const char* symbol, char type[6], int minus) {     // special condition for pointers
    if (strstr(symbol - minus, type) == symbol - minus)
        return 1;
    return 0;
}


int smart_space(const char* symbol, int direction) {
    char prev_symbol;
        if (direction == 0)
            prev_symbol = *(symbol - 1);
        else
            prev_symbol = *(symbol + 1);        // next symbol :p

    int flag = 1;
    //if (direction == 0) printf("%d||%c ", *(symbol + 1) == '\0', *(symbol + 1));
    if (direction == 0 && (prev_symbol == ' ')) {
        if (*(symbol + 1) == ' ' || *(symbol + 1) == '\0')                  // space is already standing
            return 0;
        else
            return 2;                                                       // space is only behind
    }

    if (direction == 1 && (prev_symbol == ' ' || prev_symbol == '\0'))      // space is already standing
        return 0;

    if (*symbol == '/' && prev_symbol == '/')
        flag = 2;
    if (*symbol == '+' && prev_symbol == '+')
        flag = 2;
    if (*symbol == '-' && prev_symbol == '-')
        flag = 2;
    if (*symbol == '=' && prev_symbol == '=')
        flag = 2;
    if (*symbol == '+' && prev_symbol == '=')
        flag = 2;
    if (*symbol == '-' && prev_symbol == '=')
        flag = 2;
    if (*symbol == '*' && prev_symbol == '=')
        flag = 2;
    if (*symbol == '/' && prev_symbol == '=')
        flag = 2;
    if (*symbol == '=' && prev_symbol == '<')
        flag = 2;
    if (*symbol == '=' && prev_symbol == '>')
        flag = 2;
    if (*symbol == '=' && prev_symbol == '!')
        flag = 2;
    if (*symbol == '|' && prev_symbol == '|')
        flag = 2;

    if (direction == 1) {
        if (*symbol == '=' && prev_symbol == '+')
            flag = 2;
        if (*symbol == '=' && prev_symbol == '-')
            flag = 2;
        if (*symbol == '=' && prev_symbol == '*')
            flag = 2;
        if (*symbol == '=' && prev_symbol == '/')
            flag = 2;
        if (*symbol == '<' && prev_symbol == '=')
            flag = 2;
        if (*symbol == '>' && prev_symbol == '=')
            flag = 2;
        if (*symbol == '!' && prev_symbol == '=')
            flag = 2;
    }

    //printf("%p|%p ", strstr(symbol - 3, "int"), symbol - 3);
    if ((direction == 0) && (*symbol == '*')) {
        if (save_pointer(symbol, "int", 3))
            flag = 2;
        if (save_pointer(symbol, "char", 4))
            flag = 2;
        if (save_pointer(symbol, "void", 4))
            flag = 2;
        if (save_pointer(symbol, "bool", 4))
            flag = 2;
        if (save_pointer(symbol, "long", 4))
            flag = 2;
        if (save_pointer(symbol, "short", 5))
            flag = 2;
        if (save_pointer(symbol, "float", 5))
            flag = 2;
        if (save_pointer(symbol, "double", 5))
            flag = 2;
    }

    if ((direction == 1) && (*symbol == '*')) {
        if (save_pointer(symbol, "int", 4))
            flag = 2;
        if (save_pointer(symbol, "char", 5))
            flag = 2;
        if (save_pointer(symbol, "void", 5))
            flag = 2;
        if (save_pointer(symbol, "bool", 5))
            flag = 2;
        if (save_pointer(symbol, "long", 5))
            flag = 2;
        if (save_pointer(symbol, "short", 6))
            flag = 2;
        if (save_pointer(symbol, "float", 6))
            flag = 2;
        if (save_pointer(symbol, "double", 7))
            flag = 2;
    }

    return flag;
}


void analyze_string(const char *src, FILE* output) {
    int i = 0, i2 = 0, i3 = 0, first_symbol = 1, check_prev = 0, spec = 0, res = 0, grid = 0;
    char cur_symbol, *cur_pointer, *prev_pointer, new_string[1000];

    while (src[i] != 0 && src[i] != '\n') {
        cur_pointer = &src[i];
        cur_symbol = src[i++];
        i2 = 0;

        if (cur_symbol == '#')          // Don't touch this string (almost)
            grid = 1;

        while (SYMBOLS_DATA[i2] != 0 && first_symbol == 0 && spec % 2 == 0 && grid == 0) {  // Check the symbols array

            if (cur_symbol == SYMBOLS_DATA[i2++]) {
                res = smart_space(cur_pointer, 0);

                if (res == 1) {
                    new_string[i3++] = ' ';
                    check_prev = 1;
                    prev_pointer = cur_pointer;
                    //printf(" %c (%d %c)", cur_symbol, check_prev, *prev_pointer);
                    break;
                } else if (res == 2) {
                    check_prev = 1;
                    prev_pointer = cur_pointer;
                    break;
                }
            }
        }
        if (check_prev == 1 && cur_pointer != prev_pointer && *prev_pointer != '&') {   // check prev symbols
            res = smart_space(prev_pointer, 1);
            //printf(" ||%c (%d %c)", cur_symbol, res, *prev_pointer);
            if (res == 1)
                new_string[i3++] = ' ';
            check_prev = 0;
        }

        if (grid == 1 && cur_symbol == '<' && *(cur_pointer - 1) != ' ')    // #<
            new_string[i3++] = ' ';
        new_string[i3++] = cur_symbol;

        if (cur_symbol == '"')
            spec++;                         // Don't touch the body string

        if (cur_symbol == ',' && *(cur_pointer + 1) != ' ')
            new_string[i3++] = ' ';

        if (cur_symbol != '\t' && cur_symbol != ' ') first_symbol = 0;  // Need to skip all tab and spaces at the start
    }

    new_string[i3++] = '\n';
    new_string[i3++] = 0;
    fprintf(output, "%s", new_string);
}


char* get_str(FILE* file) {
    char chr;
    char *str1 = 0;
    int len = 0;
    while ((chr = getc(file)) != '\n') {
        if (chr == -1)
            break;
        str1 = (char* ) realloc(str1, len + sizeof(char) + 2);          //len + new symbol + 2 [\n,0]
        str1[len++] = chr;
    }
    if (len == 0)
        str1 = (char* ) malloc(2 * sizeof(char));
    str1[len++] = '\n';
    str1[len] = 0;
    return str1;
}
