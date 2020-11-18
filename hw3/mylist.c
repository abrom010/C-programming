#include "mylist.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct temp {
	char* str;
	struct temp* prev;
	struct temp* next;
} node;

node* head = NULL;
node* tail = NULL;
int count=0;

void insert(char* str)
{
	int string_size = strlen(str);

	// If empty list, create head
	if(head==NULL)
	{
		head = (node*)malloc(sizeof(node*) * 2 + sizeof(char*));

		head->str = (char*)malloc(string_size);
		memcpy(head->str,str,string_size);

		head->prev = NULL;
		head->next = NULL;

	}
	// If no tail, create tail and connect to head
	else if (tail==NULL)
	{
		tail = (node*)malloc(sizeof(node*) * 2 + sizeof(char*));

		tail->str = (char*)malloc(string_size);
		memcpy(tail->str, str, string_size);

		tail->prev = head;
		tail->next = NULL;

		head->next = tail;

	}
	else
	{
		// Start at head, stop when end of list or next node is greater
		node* left = head;
		while(left->next!=NULL && strcmp((left->next)->str, str) < 0) {
			left = left->next;
		}
		
		// If current node is the tail
		if (left->next == NULL)
		{
			// In the case that we just append to the list
			if (strcmp(left->str, str) < 0)
			{
				tail = (node*)malloc(sizeof(node*) * 2 + sizeof(char*));

				left->next = tail;
				tail->prev = left;

				tail->str = (char*)malloc(string_size);
				memcpy(tail->str, str, string_size);
			}
			// In the case that we insert before the tail
			else
			{
				node* right = left;
				left = right->prev;
				node* middle = (node*)malloc(sizeof(node*) * 2 + sizeof(char*));

				middle->prev = left;
				middle->next = right;

				left->next = middle;
				right->prev = middle;

				middle->str = (char*)malloc(string_size);
				memcpy(middle->str, str, string_size);
			}
		}
		// In the case that we insert before the list
		else if (left->prev == NULL && strcmp(left->str, str) > 0)
		{
			head = (node*)malloc(sizeof(node*) * 2 + sizeof(char*));

			left->prev = head;
			head->next = left;

			head->str = (char*)malloc(string_size);
			memcpy(head->str, str, string_size);
		}
		// Every other case is the same
		else
		{
			node* right = left->next;
			node* middle = (node*)malloc(sizeof(node*) * 2 + sizeof(char*));

			middle->prev = left;
			middle->next = right;

			left->next = middle;
			right->prev = middle;

			middle->str = (char*)malloc(string_size);
			memcpy(middle->str, str, string_size);
		}

	}
	count++;
}


void delete(char* str)
{
	node* current = head;
	while (strcmp(current->str,str)!=0 && current->next != NULL)
	{ 
		current = current->next;
	}

	if (current->prev == NULL)
	{
		if (current->next == NULL)
		{
			head = NULL;
			tail = NULL;
		}
		else
		{
			head = current->next;
			head->prev = NULL;
		}
	}
	else if (current->next == NULL)
	{
		if (strcmp(current->str, str)!=0) return;
		tail = current->prev;
		tail->next = NULL;
	}
	else
	{
		node* left = current->prev;
		node* right = current->next;

		left->next = right;
		right->prev = left;
	}
	free(current);
	count--;
}

void list(int reverse_order)
{
	if(head==NULL) {
		printf("<empty>\n");
	} else {
		if(reverse_order) {
			int cnt = count;
			node* current = tail;
			while(current!=NULL) {
				printf("%d: %s\n", cnt, current->str);
				current = current->prev;
				cnt--;
			}
		} else {
			int cnt = 0;
			node* current = head;
			while(current!=NULL) {
				printf("%d: %s\n", cnt, current->str);
				current = current->next;
				cnt++;
			}
		}
	}
}
