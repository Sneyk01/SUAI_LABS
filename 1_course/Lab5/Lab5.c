#include <stdio.h>
#include <stdlib.h>
int checkSymbol(char symbol) {
    if (symbol == ' ' || symbol == '\t' || symbol == '\n')    return 1;
    return 2;
}

void longWord (int wordCount, int maxAddress, int firstMemWord, int memWord, char* word, char** wordArray) {
    int i = 0, wap = 0;
    for(i = 0; i < wordCount; i++) {
        if (i == maxAddress) {
            for (int fmw = firstMemWord; fmw < memWord; fmw++)
                printf("%c",word[fmw]);
            printf(" ");
        }
        while(wordArray[i][wap] != 0) printf("%c",wordArray[i][wap++]);
        printf(" ");
        wap = 0;
    }
}

void equalsWord (int wordCount, int firstMemWord, int memWord, char* word, char** wordArray) {
    int i = 0, wap = 0, len1 = 0, len0 = -1, d = 0;
    for(i = 0; i < wordCount; i++) {
        if (len0 == len1) {
            for (int fmw = firstMemWord; fmw < memWord; fmw++)  printf("%c",word[fmw]);
            printf(" ");
        }
        len0 = 0;
        len1 = 0;
        while(wordArray[i][wap] != 0) {
            printf("%c",wordArray[i][wap++]);
            len0++;
        }
        printf(" ");
        wap = 0;
        d = i + 1;
        if (d < wordCount)
            while (wordArray[d][wap++] != 0)    len1++;
        else len1 = -1;
        wap = 0;
    }
}

int main() {
    printf("On this program word - is any sequence of symbols excluding whitespace.\n");
    int i = 0, inWord = 0, wordCount = 0, firstS = 0, length = 0, lenWord = 0, maxLen = 0, wap = 0;
    int maxAddress = 0, firstMem = 0, mem = 0, firstMemWord = 0, memWord = 0, select = 0;
    char string[10000] = "";
    char word[1000] = "";
    printf("Enter one word:\n");
    invalidWord:
    fgets(word, 1000, stdin);
    while (word[i] != 0) {
        if (checkSymbol(word[i]) == 2) inWord = 1;
        if (inWord == 1 && firstS == 0) {
            firstMem = i;
            firstS = 1;
        }
        if (checkSymbol(word[i]) == 1 && inWord == 1) {
            wordCount++;
            mem = i;
        }
        if (checkSymbol(word[i]) == 1) inWord = 0;
        i++;
    }
    i = 0;
    if (inWord == 1) wordCount++;
    if (wordCount != 1) {
        wordCount = 0;
        firstS = 0;
        printf("Invalid data. Please enter ONE word:\n");
        goto invalidWord;
    }
    wordCount = 0;
    firstMemWord = firstMem;
    memWord = mem;
    i = 0;
    //Enter_String
    printf("Enter string:\n");
    invalidString:
    fgets(string, 10000, stdin);
    while(string[i] != 0){
        length ++;
        if (checkSymbol(string[i]) == 2) inWord = 1;
        if (checkSymbol(string[i]) == 1 && inWord == 1) wordCount++;
        if (checkSymbol(string[i++]) == 1) inWord = 0;
    }
    if (inWord == 1) wordCount++;
    if(wordCount == 0) {
        printf("Invalid string! Please enter string:\n");
        i = 0;
        length = 0;
        goto invalidString;
    }
    i = 0;
    char** wordArray = (char**) malloc(wordCount * sizeof(char*));
    for (int count = 0; count < wordCount; count++) {
        lenWord = 0;
        inWord = 0;
        while (checkSymbol(string[i]) == 2 || inWord == 0) {
            if (checkSymbol(string[i]) == 2 && inWord == 0) firstMem = i;
            if (checkSymbol(string[i++]) == 2) inWord = 1;
            if (inWord == 1) lenWord++;
        }
        mem = i;
        wordArray[count] = (char*) malloc(lenWord + 1 * sizeof(char));
        if (maxLen < lenWord)   {
            maxLen = lenWord;
            maxAddress = count;
        }
        lenWord = 0;
        for (int wa = firstMem; wa < mem; wa++)
            wordArray[count][lenWord++] = string[wa];
        wordArray[count][lenWord] = 0;
    }
    //BuildNewString
    errorChoose:
    printf("Choose edit string mode:\n(1 - insert a word before longest word; 2 - insert a word between equals length words)\n");
    if (scanf("%d", &select) != 1 || select < 1 || select > 2) {
        while (getchar() != 10) {}
        printf("Input error!\n");
        goto errorChoose;
    }
    if (select == 1) longWord(wordCount, maxAddress, firstMemWord, memWord, word, wordArray);
    else    equalsWord(wordCount, firstMemWord, memWord, word, wordArray);

    for (int count = 0; count < wordCount; count++)
        free(wordArray[count]);
    free(wordArray);

    return 0;
}
