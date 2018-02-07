#include "BigInteger.h"

void main() 
{
	char* a = "6546949873123";
	char* b =       "3457100";

	bint b1 = string_to_bint(a);
	bint b2 = string_to_bint(b);

	print_table(get_table(b1));

	printf("%s\n", bint_to_string(bint_add(b1, b2)));
	List* new = list_cpy(b1.list);
	printf("%s\n", list_to_string(b1.list, 0));
	printf("%s\n", list_to_string(new, 0));

	return;
}
