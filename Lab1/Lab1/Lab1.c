#include <stdio.h>

main() {
	unsigned char a = 0;
	char b = 0, f = 1, flag = 0, code = 0, ab, code1 = 0, flag1 = 0;
	char c = 3;		//The required number system
	char NumMem[9] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };

	printf("Enter reqired number system [2..36]: \n");
	code1 = scanf("%hhd", &c);
	while (code1 != 1 || c > 36 || c < 2) {
		printf("INPUT ERROR! \n");
		printf("Enter reqired number system [2..36]: \n");
		getchar();
		code1 = scanf("%hhd", &c);
	}

	printf("Enter 1 integers: (-128...127)\n");
	code = scanf("%hhd", &ab);
	while (code != 1) {
		printf("INPUT ERROR! \n");
		printf("Enter 1 integers: \n");
		getchar();
		code = scanf("%hhd", &ab);
	}

	a = ab;
	if (c != 10) {
		for (int i = 8; i >= 1; i--) {
			b = a % c;
			a = a / c;
			NumMem[i] = b;
		}
		printf("In %d number system: ", c);
		for (int i = 1; i <= 8; i++) {
			if (NumMem[i] != 0 || flag1 == 1) {
				if (NumMem[i] >= 10) printf("%c", NumMem[i] + 55);
				if (NumMem[i] < 10)	printf("%d", NumMem[i]);
				flag1 = 1;
			}
		}

	}
	else {
		printf("%d", ab);
	}
	
	printf("\n");
	return 0;
}


	

