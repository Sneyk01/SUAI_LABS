#include <stdio.h>

main() {
	int num = 0;
	char a = 0, b = 0, f = 1, flag = 0, code = 0;
	int c = 3;					//The required number system
	char NumMem[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};

	printf("Enter 1 integers: (-127...127)\n");
	code = scanf("%d", &num);
	while (code != 1 || num < -127 || num > 127) {
		printf("INPUT ERROR! \n");
		printf("Enter 1 integers: \n");
		getchar();
		code = scanf("%hhd", &num);
	}

	a = num;
	if (a < 0) {
		a *= -1;
		NumMem[0] = c - 1;
		for (int i = 8; i >= 1; i--) {
			b = a % c;
			a = a / c;
			NumMem[i] = b;
		}

		//for (int i = 0; i <= 8; i ++)	printf("%d.", NumMem[i]);
		for (int i = 8; i >= 1; i--) {
			NumMem[i] = ((c - 1) - NumMem[i]);
			if (i == 8 || flag == 1) {
				if ((NumMem[i] + 1) > (c - 1)) flag = 1;
				else {
					NumMem[i] += 1;
					flag = 0;
				}
			}
		}
		//for (int i = 0; i <= 8; i++)	printf("%d.", NumMem[i]);		
	}


	else {
		for (int i = 8; i >= 1; i --) {
			b = a % c;
			a = a / c;
			NumMem[i] = b;
		}
	}

	printf("%d'", NumMem[0]);
	for (int i = 1; i <= 8; i++)	printf("%d.", NumMem[i]);

	printf("\n");
	return 0;
}


	

