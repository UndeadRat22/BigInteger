#include "BigInteger.h"
#include <stdio.h>

bint list_to_bint(List* list, Sign sign)
{
	bint bigint;
	bigint.list = list;
	bigint.sign = sign;
	return bigint;
}

bint string_to_bint(char* string)
{
	bint bigint;
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

char* big_integer_to_string(bint biginteger)
{
	if (biginteger.sign == positive)
	return list_to_string(biginteger.list, 0);
	else return list_to_string(biginteger.list, '-');
}


bint bint_add(bint a, bint b)
{
	Sign s;
	if (a.sign == positive && b.sign == positive)
		s = positive;
	else if (b.sign == negative && a.sign == negative)
		s = negative;
	else if (a.sign == negative)
		return bint_sub(b, a);
	else return bint_sub (a, b);

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
	return list_to_bint(result, s);
}
bint bint_sub(bint a, bint b)
{
	return string_to_bint("0");
}

bint bint_mul(bint a, bint b)
{
	if (is_zero(a) || is_zero(b))
		return string_to_bint("0");

	Sign s = div_mult_sign(a.sign, b.sign);
}



int is_zero(bint val)
{
	Node* head = val.list->HEAD;
	while (head)
	{
		if (head->data != 0)
			return 0;
		head = head->next;
	}
	return 1;
}

Sign div_mult_sign(Sign a, Sign b)
{
	a == b ? positive : negative;
}

mtable get_table(bint val)
{
	mtable table;
}