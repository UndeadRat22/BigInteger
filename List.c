#include "List.h"

List* create_list(unsigned int size) {
	List* l = malloc(sizeof(List));
	l->count = 0;
	l->HEAD = NULL;
	while (size > 0)
	{
		push_front(l, 0);
		size--;
	}
	return l;
}

List* string_to_list(char* str)
{
	List* l = create_list(0);
	int len = strlen(str);
	if (str[len-1] == '\n') len--;
	for (int i = 0; i < len; i++)
	{
		push_front(l, str[i] - 0x30);
	}
	return l;
}

int push_front(List *list, char data) {
	Node *new = malloc(sizeof(Node));
	if (!new) 
		return OUT_OF_MEMORY_EXCEPTION;
	new->data = data;
	new->next = list->HEAD;
	list->HEAD = new;
	list->count++;
	return 1;
}

int push_back(List *list, char data) {
	Node **HEAD = &(list->HEAD);
	while (*HEAD)
		HEAD = &(*HEAD)->next;
	*HEAD = malloc(sizeof(*HEAD));
	if (!HEAD) 
		return OUT_OF_MEMORY_EXCEPTION;
	(*HEAD)->data = data;
	(*HEAD)->next = NULL;
	list->count++;
	return 1;
}

char pop_head(List *list) {
	Node *tmp = list->HEAD;
	if (!tmp) 
		return LIST_EMPTY_EXCEPTION;
	list->HEAD = list->HEAD->next;
	char value = tmp->data;
	free(tmp);
	list->count--;
	return value;
}

char pop_tail(List *list) {
	Node **HEAD = &(list->HEAD);
	if (!(*HEAD))
		return LIST_EMPTY_EXCEPTION;
	while ((*HEAD)->next)
		HEAD = &(*HEAD)->next;
	char value = (*HEAD)->data;
	free(*HEAD);
	*HEAD = NULL;
	list->count--;
	return value;
}

Node* get_by_index(List* list, int index)
{
	Node* result = list->HEAD;
	int i = 0;
	if (list->count - 1 < index)
		return INDEX_OUT_OF_RANGE;
	while (i != index && result)
	{
		result = result->next;
		i++;
	}
	if (index == i)
		return result;
	return INDEX_OUT_OF_RANGE;
}

int insert(List *list, int index, char data) {
	Node *new = NULL, **HEAD = &(list->HEAD);
	int i = 0;
	while (*HEAD && i != index - 1) {
		HEAD = &(*HEAD)->next;
		i++;
	}
	if (!(*HEAD)) return INDEX_OUT_OF_RANGE;
	new = malloc(sizeof(Node));
	if (!new) return OUT_OF_MEMORY_EXCEPTION;
	new->data = data;
	new->next = *HEAD;
	*HEAD = new;
	list->count++;
	return 1;
}

int delete_by_index(List *list, int index) {
	struct Node* tmp = NULL, **HEAD = &(list->HEAD);
	int i = 0;
	while (*HEAD && i != index - 1) {
		HEAD = &(*HEAD)->next;
		i++;
	}
	if (!(*HEAD)) return INDEX_OUT_OF_RANGE;
	tmp = *HEAD;
	*HEAD = (*HEAD)->next;
	list->count--;
	free(tmp);
	return 0;
}

char* to_string (List* list) {
	char* str = malloc((list->count + 1) * sizeof(char));
	if (str == NULL) return OUT_OF_MEMORY_EXCEPTION;
	int i = 0;
	Node **HEAD = &(list->HEAD);
	while (*HEAD)
	{
		str[i] = (*HEAD)->data + 0x30;
		HEAD = &(*HEAD)->next;
		i++;
	}
	str[i] = '\0';
	return _strrev(str);
}

void free_list(List *list) {
	Node *head = list->HEAD, *tmp = NULL;
	while (head) {
		tmp = head->next;
		free(head);
		head = tmp;
	}
	free(list);
}