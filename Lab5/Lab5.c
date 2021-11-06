#include <stdio.h>
int checkSymbol(char symbol) {
    if (symbol == ' ' || symbol == '\t' || symbol == '\n')    return 1;
    return 2;
}

int main() {
    printf("On this program word - is any sequence of symbols excluding whitespace.\n");
    int i = 0, inWord = 0, wordCount = 0, longWord = 0, maxLong = 0, firstS = 0, length = 0;
    int firstMemMax = 0, memMax = 0, firstMem = 0, mem = 0, firstMemWord = 0, memWord = 0;
    char string[10000] = "";
    char word[1000] = "";
    char newString[11000] = "";
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
            mem = i - 1;
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
    //for (i = firstMem; i <= mem; i++) printf("%c", word[i]);
    //printf("\n");
    i = 0;
    //Enter_String
    printf("Enter string:\n");
    invalidString:
    fgets(string, 10000, stdin);
    while(string[i] != 0){
        length ++;
        if (checkSymbol(string[i]) == 2) inWord = 1;
        if (inWord == 1 && firstS == 0) {
            firstMem = i;
            firstS = 1;
        }
        if (checkSymbol(string[i]) == 1 && inWord == 1) {
            wordCount++;
            mem = i - 1;
            longWord = (mem - firstMem) + 1;
            if (longWord > maxLong) {
                maxLong = longWord;
                firstMemMax = firstMem;
                memMax = mem;
            }
            firstS = 0;
        }
        if (checkSymbol(string[i]) == 1) inWord = 0;
        i++;
    }
    if(wordCount == 0) {
        printf("Invalid string! Please enter string:\n");
        i = 0;
        length = 0;
        goto invalidString;
    }
    //BuildNewString
    for(i = 0; i < firstMemMax; i++) newString[i] = string[i];
    int iOld = i;
    for(i = firstMemWord; i <= memWord; i++)    newString[iOld++] = word[i];
    newString[iOld++] = ' ';
    for(i = firstMemMax; i < length; i++) newString[iOld++] = string[i];
    i = 0;
    while(newString[i] != 0) printf("%c", newString[i++]);
    return 0;
}
