#include "BigInteger.h"
#include <stdio.h>

bint bint_cpy(bint source)
{
	return (bint) {list_cpy(source.list), source.sign};
}

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
		bigint.list = string_to_list(string+1);
	}
	else
	{
		bigint.sign = positive;
		bigint.list = string_to_list(string);
	}
	return bigint;
}

char* bint_to_string(bint biginteger)
{
	if (biginteger.sign == positive)
	return list_to_string(reverse_list(biginteger.list), 0);
	else return list_to_string(reverse_list(biginteger.list), '-');
}


bint bint_add(bint a, bint b)
{
	Sign s;
	if (a.sign == positive && b.sign == positive)
		s = positive;
	else if (b.sign == negative && a.sign == negative)
		s = negative;
	else if (a.sign == negative) {          /* kai paduodam i sub, du minusai pavirsta pliusu, todel keiciam neigiamo sk. zenkla */
        a.sign = positive;
		return bint_sub(b, a);
    }
	else {                                  /* b.sign == negative */
        b.sign = positive;                  
        return bint_sub(a, b);
    }
	
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
		push_back(result, (char)new_data);
	}
	if (carry > 0)
	{
		push_back(result, (char)carry);
	}
	return list_to_bint(result, s);
}

bint bint_sub(bint a, bint b)
{
	int i = 0;
	bint result = { create_list(0), 0 };
	if (a.sign != b.sign) {										// a-(-b) = a+b arba -a-b = -(a+b)
		b.sign = a.sign ? negative : positive;
		return bint_add(a, b);
	}
	/* jei a < b, tai skaiciuojam principu: a-b = -(b-a) */
	if (bint_equal(a, b))
		return string_to_bint("0");
	if (bint_greater_than(a, b)) {
		bool carry = false;
		Node *head1 = a.list->HEAD, *head2 = b.list->HEAD;
		while (head1 && head2) {
			if (carry) {
				head1->data--;
				carry = false;
			}
			int tmp = head1->data - head2->data;
			if (tmp < 0) {
				carry = true;
				tmp += 10;
			}
			push_back(result.list, tmp);
			head1 = head1->next;
			head2 = head2->next;
			i++;
		}
		if (carry) {
			head1->data--;
			for (; i < a.list->count; i++) {
				push_back(result.list, head1->data);
				head1 = head1->next;
			}
			/* tikrinam, ar skaiciaus kaireje nera nuliu, tam viso reik reversint 2 kartus */
			List *reversed = reverse_list(result.list);
			Node *curr = reversed->HEAD;
			while (curr->data == 0 && curr) {
				pop_head(reversed);
				curr = curr->next;
			}
			result.list = reverse_list(result.list);
		}
		else {
			result = bint_sub(b, a);
			result.sign = negative;
		}
		return result;
	}
}

bint bint_mul(bint a, bint b)
{
	if (is_zero(a) || is_zero(b))
		return string_to_bint("0");
	Sign s = div_mult_sign(a.sign, b.sign);
	mtable t = get_table(a);
	
	bint result = {create_list(0), s};

	int i;
	
	for (i = 0; i < b.list->count; i++) 
	{
		bint value = bint_cpy(t.values[get_by_index(b.list, i)->data]);
		value.sign = s;
		int j = i;
		while (j > 0)
		{
			push_front(value.list, 0);
			j--;
		}
		result = bint_add(result, value);
	}

	return result;
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
	return a == b ? positive : negative;
}

mtable get_table(bint val)
{
	int val_lenght = val.list->count;
	mtable table;
	table.values[0] = list_to_bint(create_list(val.list->count), val.sign);
	table.values[1] = bint_cpy(val);
	int i, j;
	for (int i = 2; i < 10; i++) 
	{
		table.values[i] = bint_cpy(val);
		for (int j = 0; j < i - 1; j++)
		{
			table.values[i] = bint_add(table.values[i], val);
		}
	}
	return table;
}

bool bint_equal(bint a, bint b) {
	Node *head1=a.list->HEAD, *head2=b.list->HEAD;
	if (a.list->count != b.list->count)
		return false;
	while (head1 && head2) {
		if (head1->data != head2->data)
			return false;
		head1 = head1->next;
		head2 = head2->next;
	}
	return true;
}

bool bint_greater_than(bint a, bint b) {
	Node *head1=NULL, *head2=NULL;
	if (a.list->count < b.list->count)
		return false;
		else if (a.list->count > b.list->count)
			return true;
	a.list = reverse_list(a.list);
	b.list = reverse_list(b.list);
	head1 = a.list->HEAD;
	head2 = b.list->HEAD;
	while (head1 && head2) {
		if (head1->data > head2->data)
			return true;
			else if (head1->data < head2->data)
				return false;
		head1 = head1->next;
		head2 = head2->next;
	}
	return false;
}

void print_table(mtable table) 
{
	for (int i = 0; i < 10; i++) 
	{
		printf("table[%d] = %s\n",i , _strrev(bint_to_string(table.values[i])));
	}
}