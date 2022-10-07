#include <stdio.h>;
#define LenArr 10

double SQR(double num, int degree) {
	double mem = num;
	for (int d = 2; d <= degree; d++) {
		num *= mem;
		//printf(" st %d ", i);
	}
	return num;
}

double SQRT(double num, int degree) {
	int nF = 0;
	double result = 50, resultOld = num, difference = 1;;
	while (num - SQR(result, degree) > 0.00001 || num - SQR(result, degree) < -0.00001) {
		//printf("%f %f |", resultOld, result);
		if (nF > 0)	resultOld = result;
		else nF++;
		result = (result * (degree - 1) + (num / SQR(result, degree - 1))) / degree;
		if (resultOld - result < 0) difference = result - resultOld;
		else difference = resultOld - result;
		//printf("%f %f \n", resultOld, result);
	}
	//printf("Avarage double: %f\n", result);
	return result;
}

void EditArr(int* arrF, int l) {
	int flag = 0, avInt = 1;
	for (int i = 0; i < l; i++)	avInt *= arrF[i];
	if (avInt < 0) avInt *= -1;
	avInt = SQRT(avInt, l);
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

	EditArr(&arr[0], LenArr);

	printf("new array: \n");
	for (int i = 0; i < LenArr; i++) printf("%d ", arr[i]);
}
