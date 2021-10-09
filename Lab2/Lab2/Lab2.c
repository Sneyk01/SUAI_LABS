#include <stdio.h>


main() {
	int i = 0, fs = 1, space = 0, firstSS = 1;
	char a[10000] = "";
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
		
		if ((space - fs > 0) && (a[space - 1] == 'a' || a[space - 1] == 'e' || a[space - 1] == 'u' || a[space - 1] == 'i' || a[space - 1] == 'o' || a[space - 1] == 'y' || a[space - 1] == 'A' || a[space - 1] == 'E' || a[space - 1] == 'U' || a[space - 1] == 'I' || a[space - 1] == 'O' || a[space - 1] == 'Y')) {
			for (int f = fs; f < space; f++)	printf("%c", a[f]);
			printf(" ");
			space = 0;
		}

		if (a[i] == '\n') {
			i++;
			firstSS = 1;
		}
	}
}
