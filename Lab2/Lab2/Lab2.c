#include <stdio.h>


main() {
	int i = 0, space = 1, space2 = 0, first = 1;
	char a[10000] = "";
	printf("Print string (max 10000 symb):\n");
	fgets(&a, 10000, stdin);
	while (a[i] != 10) {
		if (a[i] == ' ' || first == 1) {
			first = 0;
			i++;
			space = i;
			while (a[i] != ' ' && a[i] != 10) {
				i++;
				space2 = i;
			}
		}

		if ((space2 > 0) && (a[space2 - 1] == 'a' || a[space2 - 1] == 'e' || a[space2 - 1] == 'u' || a[space2 - 1] == 'i' || a[space2 - 1] == 'o' || a[space2 - 1] == 'y' || a[space2 - 1] == 'A' || a[space2 - 1] == 'E' || a[space2 - 1] == 'U' || a[space2 - 1] == 'I' || a[space2 - 1] == 'O' || a[space2 - 1] == 'Y')) {
			for (int f = space; f <= space2; f++) {
				printf("%c", a[f]);
			}
			//i++;
			space2 = 0;
		}
	}
}
