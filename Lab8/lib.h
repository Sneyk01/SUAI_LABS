//
// Created by prgle on 15.02.2022.
//


#ifndef LAB8_LIB_H
#define LAB8_LIB_H

#include <stdio.h>
#include <stdlib.h>


static const char PATH[] = "D:\\Project\\C\\Lab8\\src.txt";
static const char PATH_RES[] = "D:\\Project\\C\\Lab8\\res.txt";


int* input();
int* input_file(FILE* src);
FILE* open_file(char* path);
void output_file(FILE* src, int* data);
int get_num(FILE* src, int* flag);
void output(int* data);
void deg(int* data, int degr);
int get_degree();

#endif //LAB8_LIB_H
