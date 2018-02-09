#include "BigInteger.h"
#include <time.h>

bool equal_strings(char *a, char *b);

int main(void) 
{
	char* ab = "1";
	char* bb = "5";
	srand(time(NULL));

	for (int i=0; i<10000; i++) {
		int rand1 = rand(), rand2 = rand(), int_result=0;
		int operation = rand() % 5;
		bint a = string_to_bint(int_to_string(rand1)), b = string_to_bint(int_to_string(rand2));
		bint bint_result;
		
		if (operation == 0) {
			int_result = rand1+rand2;
			bint_result = bint_add(a, b);
		}
		else if (operation == 1) {
			int_result = rand1-rand2;
			bint_result = bint_sub(a, b);
		}
		else if (operation == 2) {
			int_result = rand1*rand2;
			bint_result = bint_mul(a, b);
		}
		else if (operation == 3) { 
			int_result = rand1/rand2;
			bint_result = bint_div(a, b);			
		}
		else if (operation == 4) {
			int_result = rand1%rand2;
			bint_result = bint_mod(a, b);
		}
		if (!equal_strings(int_to_string(int_result), bint_to_string(bint_result))) {				
			printf("INTE: %d     BINT: %s\n", int_result, bint_to_string(bint_result));
			printf("rand1: %d       rand2: %d\n", rand1, rand2);
		}
	}


	return 0;
}

bool equal_strings(char *a, char *b) {
	if (strlen(a) != strlen(b)) {
		printf("(1)EQUAL STRINGS: not equal %c and %c\n", a[0], b[0]);
		printf("(2)EQUAL STRINGS: STRLEN(a): %d, STRLEN(b): %d\n", strlen(a), strlen(b));
		return false;
	}
	for (int i=0; i<strlen(a); i++) {
		if (a[i] != b[i]) {
			printf("(1)EQUAL STRINGS: not equal: %c ir %c\n", a[i], b[i]);
			return false;
		}
	}
	return true;
}