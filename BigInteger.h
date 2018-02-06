#include "List.h"

typedef enum Sign{
	positive = 0,
	negative = 1,
} Sign;

typedef struct BigInteger 
{
	List* list;
	Sign sign;
} BigInteger;


BigInteger string_to_big_int(char* );
char* big_Integer_to_string(BigInteger);

BigInteger Add(BigInteger a, BigInteger b);			/* a + b*/
BigInteger Subtract(BigInteger a, BigInteger b);	/* a - b*/