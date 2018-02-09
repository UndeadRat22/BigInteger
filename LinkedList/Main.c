#include "List.h"

List* Add(List*, List*);

void main() 
{
	char* a = "6546949873123";
	char* b =       "3457100";
	//		   6546953330223
	List* l1 = string_to_list(a);
	List* l2 = string_to_list(b);
	List* res = Add(l1, l2);
	char* str = to_string(res);
	printf("%s\n", str);
	free_list(l1);
	free_list(l2);
	free_list(res);
	return;
}

List* Add(List* a, List* b) 
{
	List* result = create_list(0);
	List *shorter, *longer;
	int min, max;
	if (a->count == b->count)
	{
		min = a->count;
		max = min;
		shorter = a;
		longer = b;
	}
	else 
	{
		shorter = get_shorter(a, b, &min);
		longer = get_longer(a, b, &max);
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
		push_front(result, (char) new_data);
	}
	if (carry > 0)
	{
		push_front(result, (char) carry);
	}
	return result;
}