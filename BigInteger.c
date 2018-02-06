#include "BigInteger.h"
#include <stdio.h>

BigInteger list_to_big_int(List* list, Sign sign)
{
	BigInteger bigint;
	bigint.list = list;
	bigint.sign = sign;
	return bigint;
}

BigInteger string_to_big_int(char* string) 
{
	BigInteger bigint;
	if (string[0] == '-')
	{
		bigint.sign = negative;
		bigint.list = string_to_list(string, 1);
	}
	else
	{
		bigint.sign = positive;
		bigint.list = string_to_list(string, 0);
	}
	return bigint;
}

char* big_Integer_to_string(BigInteger biginteger)
{
	if (biginteger.sign == positive)
	return list_to_string(biginteger.list, 0);
	else return list_to_string(biginteger.list, '-');
}


BigInteger Add(BigInteger a, BigInteger b) 
{
	Sign s;
	if (a.sign == positive && b.sign == positive)
		s = positive;
	else if (b.sign == negative && a.sign == negative)
		s = negative;
	else if (a.sign == negative)
		return Subtract(b, a);
	else return Subtract (a, b);

	List* result = create_list(0);
	List *shorter, *longer;
	int min, max;
	if (a.list->count == b.list ->count)
	{
		min = a.list->count;
		max = min;
		shorter = a.list;
		longer = b.list;
	}
	else
	{
		shorter = get_shorter(a.list, b.list, &min);
		longer = get_longer(a.list, b.list, &max);
	}
	int i, carry = 0;
	for (i = 0; i < max; i++)
	{
		int shorter_data = 0;
		int longer_data = get_by_index(longer, i)->data;
		if (i < min)
			shorter_data = get_by_index(shorter, i)->data;
		int new_data = shorter_data + longer_data + carry;
		carry = 0;
		while (new_data > 9)
		{
			new_data -= 10;
			carry++;
		}
		push_front(result, (char)new_data);
	}
	if (carry > 0)
	{
		push_front(result, (char)carry);
	}
	return list_to_big_int(result, s);
}