/*
    int d;
    for (i = 0; i < wordCount; i++) {
        d = 0;
        while(wordArray[i][d] != 0)
            printf("%c", wordArray[i][d++]);
        printf("\n %d %d \n",i, wordCount);
    }
 */

#define strLen 10000

#include <stdio.h>
#include <stdlib.h>

struct wordList;

typedef struct wordList {
    char *wordAdr;
    int wordLen;
    int wordCount;
    struct wordList *prev;
    struct wordList *next;
};


int findWordCount(char string[strLen], int findNum) {
    int inWord = 0, wordCount = 0, i = 0, wordStart = 0;
    while (string[i] != 0) {
        if (string[i] != ' ' && string[i] != '\t' && string[i] != '\n' && inWord == 0) wordStart = i;
        if (string[i] != ' ' && string[i] != '\t' && string[i] != '\n') inWord = 1;
        else {
            if (inWord == 1) wordCount++;
            inWord = 0;
        }
        if (wordCount == findNum) return wordStart;
        i++;
    }
    if (inWord == 1) wordCount++;
    return wordCount;
}

char** createArray(char string[strLen], int wordCount) {
    int i = 0, numWord = 0, inWord = 0, wordStart = 0, wordLen = 0, wordStartOld = 0;
    char** wordArray = (char**) malloc(wordCount * sizeof(char*));
    for (numWord = 1; numWord <= wordCount; numWord++) {
        wordStart = findWordCount(string, numWord);
        wordStartOld = wordStart;
        while (string[wordStart] != ' ' && string[wordStart] != '\t' && string[wordStart] != '\n') {
            wordLen++;
            wordStart++;
        }
        wordArray[numWord - 1]  = (char*) malloc((wordLen + 1) * sizeof(char));
        wordStart = wordStartOld;
        i = 0;
        while (string[wordStart] != ' ' && string[wordStart] != '\t' && string[wordStart] != '\n') {
            wordArray[numWord - 1][i++] = string[wordStart];
            wordStart++;
        }
        wordArray[numWord -      1][i] = 0;
    }
    return wordArray;
}

void sortArray(int wordCount, char** wordArray) {
    int len = 0, minLen = 0, symbNumb = 0, mem = 0;
    char* temp = 0;
    for (int i = 0; i < wordCount - 1; i++) {
        minLen = 9999;
        for (int puz = i; puz < wordCount; puz++) {
            symbNumb = 0;
            len = 0;
            while (wordArray[puz][symbNumb++] != 0) len++;
            if (minLen > len) {
                minLen = len;
                mem = puz;
            }
        }
        temp = wordArray[mem];
        wordArray[mem] = wordArray[i];
        wordArray[i] = temp;
    }
}

int main() {
    int wordCount = 0, i = 0;
    char inputString[strLen] = "";
    char** wordArray;
    printf("Enter string!\n");
    fgets(inputString, 10000, stdin);
    //wordCount = findWordCount(inputString, -1);
    //wordArray = createArray(inputString, wordCount);

    int d;
    for (int i = 0; i < wordCount; i++) {
        d = 0;
        while(wordArray[i][d] != 0)
            printf("%c", wordArray[i][d++]);
        printf(" ");
    }
    printf("\n");
    sortArray(wordCount, wordArray);
    for (int i = 0; i < wordCount; i++) {
        d = 0;
        while(wordArray[i][d] != 0)
            printf("%c", wordArray[i][d++]);
        printf(" ");
    }
    return 0;
}
