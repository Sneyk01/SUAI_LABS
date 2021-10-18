#include <stdio.h>
int checkV(char symb) {
	if (symb == 'a' || symb == 'A') return 1;
	if (symb == 'e' || symb == 'E') return 1;
	if (symb == 'u' || symb == 'U') return 1;
	if (symb == 'i' || symb == 'I') return 1;
	if (symb == 'o' || symb == 'O') return 1;
	if (symb == 'y' || symb == 'Y') return 1;
	return 0;
}

main() {
	int i = 0, fs = 1, space = 0, firstSS = 1, vowels = 0, vowelsC = 0;
	char a[10000] = "";
	printf("Enter count of vowels:\n");
	while (scanf("%d", &vowels) != 1) {
		while (getchar() != '\n') {}
		printf("Inout Error! Enter count of vowels : \n");
	}
	while (getchar() != '\n') {}
	printf("Print string (max 10000 symb):\n");
	fgets(&a, 10000, stdin);
	while (a[i] != 0) {
		if (a[i] == ' ' || a[i] == '\t' || firstSS == 1) {
			if (a[i] == ' ' || a[i] == '\t')	fs = i + 1;
			else fs = i;
			if (firstSS == 0) i++;
			firstSS = 0;
			while (a[i] != ' ' && a[i] != '\t' && a[i] != 0 && a[i] != '\n') {
				i++;
				space = i;
			}
		}

		if (space - fs > 0) {
			for (int f = fs; f < space; f++)
				if (checkV(a[f]) == 1) vowelsC++;
			//space = 0;
			if (vowelsC >= vowels)
			{
				for (int f = fs; f < space; f++)
					printf("%c", a[f]);
				printf(" ");
			}
			space = 0;
			vowelsC = 0;
		}


		if (a[i] == '\n') {
			i++;
			firstSS = 1;
		}
	}
}
