#include <stdio.h>;


void f(int *am, int l) {
	int srZ = 0;
	for (int i = 0; i < l; i++) 
		srZ += am[i];
	srZ /= l;
	printf("\nsrZ: %d \n", srZ);
	for (int i = 0; i < l; i++)
		if (am[i] > srZ) am[i] = 0;
}

main() {
	int mass[10] = {0};

	printf("Please enter 10 integers\n");
	for (int i = 0; i < 10; i++) {
		printf("%d numder:  ", i + 1);
		while (scanf("%d", &mass[i]) != 1) {
			printf("\nInput Error! Please enter %d numder:  ", i + 1);
			getchar();
		}
	}

	printf("\n\nold mass: \n");
	for (int i = 0; i < 10; i++) printf("%d ", mass[i]);

	f(&mass[0], 10);

	printf("new mass: \n");
	for (int i = 0; i < 10; i++) printf("%d ", mass[i]);
	
}