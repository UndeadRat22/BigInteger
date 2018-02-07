#include "List.h"

List* create_list(unsigned int size) {
	List* l = calloc(1, sizeof(List));
	while (size > 0)
	{
		print_error(push_front(l, 0));
		size--;
	}
	return l;
}

List* string_to_list(char* str, int start_index)
{
	List* l = create_list(0);
	int len = strlen(str);
	if (str[len - 1] == '\n') len--;
	if (start_index >= len)
		print_error(INDEX_OUT_OF_RANGE_EXCEPTION);
	for (int i = start_index; i < len; i++)
	{
		print_error(push_front(l, str[i] - 0x30));
	}
	return l;
}

List* list_cpy(List* original)
{
	List* new_list = create_list(0);
	Node* head = original->HEAD;
	while (head)
	{
		push_back(new_list, head->data);
		head = head->next;
	}
	return new_list;
}

int push_front(List *list, char data) {
	Node *new = malloc(sizeof(Node));
	if (!new) 
		return OUT_OF_MEMORY_EXCEPTION;
	new->data = data;
	new->next = list->HEAD;
	list->HEAD = new;
	list->count++;
	return ALL_GOOD;
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
	return ALL_GOOD;
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
		return INDEX_OUT_OF_RANGE_EXCEPTION;
	while (i != index && result)
	{
		result = result->next;
		i++;
	}
	if (index == i)
		return result;
	return INDEX_OUT_OF_RANGE_EXCEPTION;
}

int insert(List *list, int index, char data) {
	Node *new = NULL, **HEAD = &(list->HEAD);
	int i = 0;
	while (*HEAD && i != index - 1) {
		HEAD = &(*HEAD)->next;
		i++;
	}
	if (!(*HEAD)) return INDEX_OUT_OF_RANGE_EXCEPTION;
	new = malloc(sizeof(Node));
	if (!new) return OUT_OF_MEMORY_EXCEPTION;
	new->data = data;
	new->next = *HEAD;
	*HEAD = new;
	list->count++;
	return ALL_GOOD;
}

int delete_by_index(List *list, int index) {
	struct Node* tmp = NULL, **HEAD = &(list->HEAD);
	int i = 0;
	while (*HEAD && i != index - 1) {
		HEAD = &(*HEAD)->next;
		i++;
	}
	if (!(*HEAD)) return INDEX_OUT_OF_RANGE_EXCEPTION;
	tmp = *HEAD;
	*HEAD = (*HEAD)->next;
	list->count--;
	free(tmp);
	return ALL_GOOD;
}

char* list_to_string (List* list, char optional) {
	char* str;
	int i = 0;
	if (optional != '-') 
		str = malloc((list->count + 1) * sizeof(char));
	else {
		str = malloc((list->count + 2) * sizeof(char));
		i++;
		str[0] = optional;
	}
	if (str == NULL) return OUT_OF_MEMORY_EXCEPTION;
	Node **HEAD = &(list->HEAD);
	while (*HEAD)
	{
		str[i] = (*HEAD)->data + 0x30;
		HEAD = &(*HEAD)->next;
		i++;
	}
	str[i] = '\0';
	return str;
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

void print_error(ErrorCode code) 
{
	switch (code)
	{
	case OUT_OF_MEMORY_EXCEPTION:
		fprintf(stderr, "Out of memory !\n");
		exit(OUT_OF_MEMORY_EXCEPTION);

	case LIST_EMPTY_EXCEPTION:
		fprintf(stderr, "List Empty !\n");
		break;

	case INDEX_OUT_OF_RANGE_EXCEPTION:
		fprintf(stderr, "Index out of range !\n");
		break;
	case ALL_GOOD:
	default:
		break;
	}
	return;
}

List* get_longer(List* a, List* b, int* lenght)
{
	*lenght = MAX(a->count, b->count);
	return (a->count == *lenght) ? a : b;
}

List* get_shorter(List* a, List* b, int* lenght)
{
	*lenght = MIN(a->count, b->count);
	return (b->count == *lenght) ? b : a;
}

List* reverse_list(List *list)
{
	if (list == NULL || list->HEAD == NULL)
	{
		print_error(LIST_EMPTY_EXCEPTION);
		return list;
	}
	Node* head = list->HEAD;
	Node* new_head = NULL;
	while (head)
	{
		Node* next = head->next;
		head->next = new_head;
		new_head = head;
		head = next;
	}
	list->HEAD = head;
	return list;
}
