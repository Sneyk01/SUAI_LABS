#include <stdio.h>


main() {
	
	int a = 0, b = 0, c = 0, code = 0;
	
	printf("Enter 2 integers: \n");
	code = scanf("%d%d", &a, &b)

	if ((code == 2) || (b != 0)) {
		c = a % b;
		printf("%d is the remainder. \n", c);
		
	}
	else {
		printf("INPUT ERROR! \n");
		return -1;
	}
	return 0;

}
