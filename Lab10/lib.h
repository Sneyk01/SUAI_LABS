//
// Created by prgle on 26.03.2022.
//
#ifndef LAB10_LIB_H
#define LAB10_LIB_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static const char PATH[] = "D:\\Project\\C\\Lab10\\test.c";
static const char SYMBOLS_DATA[] = "+-*/%={}<>&!|";

FILE* open_file(char *path);
void analyze_string(const char* src, FILE* output);
int smart_space(const char* symbol, int direction);
int save_pointer(const char* symbol, char type[6], int minus);
char* get_str(FILE* file);

#endif //LAB10_LIB_H
