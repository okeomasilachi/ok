#include "../main.h"

typedef struct node
{
	int value;
	struct node *nxt;
} Node;

void print_node(Node *head);
Node *insert_at_head(Node *head, int value);


int main(void)
{
	Node *a = NULL;
	a = insert_at_head(a, 6);
	a = insert_at_head(a, 7);
	a = insert_at_head(a, 8);
	a = insert_at_head(a, 9);
	print_node(a);
	return 0;
	
}

Node *insert_at_head(Node *head, int value)
{
	Node *new_node = malloc(sizeof(Node));
	new_node->value = value;
	if (head == NULL)
		return (new_node);
	else
	{
		new_node->nxt = head;
		return (new_node);
	}

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

 