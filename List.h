#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OUT_OF_MEMORY_EXCEPTION -1;
#define LIST_EMPTY_EXCEPTION -2;
#define INDEX_OUT_OF_RANGE -3;

typedef struct Node {
	char data;
	struct Node *next;
} Node;

typedef struct List {
	Node *HEAD;
	unsigned count;
} List;

List string_to_list(char*, int index);							/*returns the specified string a list of chars*/
List create_list();
int push_front(List*, char);                        /* push entry at the front of list in O(1) time */
int push_back(List*, char);                         /* push entry at the end of list in O(n) time */
char pop_head(List*);                             /* returns first value of the list */
char pop_tail(List*);                              /* returns last value of the list */
Node* get_by_index(List*);							/*returns the pointer to the specified Node*/
int insert(List*, int, char);                       /* insert entry by index [1, n] */
int delete_by_index(List*, int);                   /* delete entry by index [1, n] */
char* to_string(List);
void free_list(List*);                              /* free memory and dissolve the list */