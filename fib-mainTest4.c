#include <stdio.h> 
#include <stdlib.h> 
#include <limits.h> 
#include "Fibonacci.h"

// print a HugeInteger (followed by a newline character) 
void hugePrint(HugeInteger *p) {

	if (p == NULL || p->digits == NULL) { 
		printf("(null pointer)\n");
		return;
	}

	int i;
	for (i = p->length - 1; i >= 0; i--) {
		printf("%d", p->digits[i]); 
	}

	printf("\n");
}

int main(void) { 

	int i;
	HugeInteger *p;

	for (i = 0; i <= 1000; i++) { 

		printf("F(%d) = ", i); 
		hugePrint(p = fib(i)); 
		hugeDestroyer(p); 
	}

	return 0;
}