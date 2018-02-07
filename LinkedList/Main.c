#include "BigInteger.h"

void main() 
{
	char* a = "6546949873123";
	char* b =       "3457100";

	bint ba = string_to_bint(a);
	bint bb = string_to_bint(b);
	
	bint sub = bint_sub(ba, bb);

	printf("%s\n", bint_to_string(sub));
}
