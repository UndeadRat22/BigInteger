#include "List.h"

#define bint BigInteger

typedef enum Sign{
	positive = 0,
	negative = 1,
} Sign;

typedef struct BigInteger 
{
	List* list;
	Sign sign;
} BigInteger;


BigInteger string_to_bint(char* );
char* big_integer_to_string(BigInteger);

BigInteger bint_add(BigInteger a, BigInteger b);	/* a + b*/
BigInteger bint_sub(BigInteger a, BigInteger b);	/* a - b*/
BigInteger bint_mul(BigInteger a, BigInteger b);	/* a * b*/
BigInteger bint_div(BigInteger a, BigInteger b);	/* a / b*/