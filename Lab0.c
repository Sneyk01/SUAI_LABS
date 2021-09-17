#include <stdio.h>
int a = 0, b = 0, c = 0;

int main() {
	
	printf("Enter 2 integers: \n");
	scanf("%d%d", &a, &b);

	if (b == 0) {
		while (b == 0) {
			printf("Error: division by 0, re-enter. \n");
			printf("Enter 2 integers: \n");
			scanf("%d%d", &a, &b);
		}
	}
	c = a % b;
	printf("%d is the remainder. \n", c);

	return 0;

}
