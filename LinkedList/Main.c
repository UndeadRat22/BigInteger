#include "BigInteger.h"

void main() 
{
	char* a = "1";
	char* b = "211";

	bint ba = string_to_bint(a);
	bint bb = string_to_bint(b);

	bint sub = bint_sub(ba, bb);
	free_list(ba.list);
	free_list(bb.list);

	printf("%s\n", bint_to_string(sub));
	free_list(sub.list);
}
