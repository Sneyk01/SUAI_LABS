#include <stdio.h>;
#define LenArr 10

void EditArr(int* arrF, int l) {
	int avInt = 0;
	for (int i = 0; i < l; i++)	avInt += arrF[i];
	avInt /= l;
	printf("\nAverage integer: %d \n", avInt);
	for (int i = 0; i < l; i++)	if (arrF[i] > avInt) arrF[i] = 0;
}

main() {
	int arr[LenArr] = { 0 };
	char symb = 1;
	printf("Please enter 10 integers\n");
	for (int i = 0; i < LenArr; i++) {
		printf("%d numder:  ", i + 1);
		while (scanf("%d", &arr[i]) != 1) {
			while (getchar() != '\n') {}
			printf("Input Error! Please enter %d numder:  ", i + 1);	
		}
	}

	printf("\n\nold array: \n");
	for (int i = 0; i < LenArr; i++) printf("%d ", arr[i]);

	EditArr(&arr[0], 10);

	printf("new array: \n");
	for (int i = 0; i < LenArr; i++) printf("%d ", arr[i]);

}