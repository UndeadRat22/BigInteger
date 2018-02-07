#include "BigInteger.h"

void main() 
{
	char* a = "901";
	char* b = "1002";

	bint ba = string_to_bint(a);
	bint bb = string_to_bint(b);

	print_table(get_table(ba));

	printf("%s\n", bint_to_string(bint_add(ba, bb)));
	printf("%s\n", list_to_string(ba.list, 0));
	bint result = bint_mul(ba, bb);
	printf("hello?");
	printf("%s\n", bint_to_string(result));
	return;
}
