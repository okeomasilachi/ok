#include "../main.h"

typedef struct node
{
	int value;
	struct node *nxt;
} Node;

void print_node(Node *head);


int main(void)
{
	Node a, b, c;
	a.value = 5;
	b.value = 6;
	c.value = 7;
	a.nxt = &b;
	b.nxt = &c;
	c.nxt = NULL;

	print_node(&a);
	return 0;
	
}

void print_node(Node *head)
{
	char i = 'a';
	Node *current;
	current = head;

	while (current != NULL)
	{
		printf("node at %c: = %d\n", i, current->value);
		i++;
		current = current->nxt;
	}
	
}