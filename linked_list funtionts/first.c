#include "../main.h"

typedef struct node
{
	int value;
	struct node *nxt;
} Node;

void print_node(Node *head);
Node *insert_at_head(Node *head, int value);
Node *insert_at_tail(Node *head, int value);
Node *delete_at_head(Node *head);
Node *delete_at_tail(Node *head);
int lenght(Node *head);


int main(void)
{
	int len; 

	Node *a = NULL;
	a = insert_at_tail(a, 6);
	a = insert_at_tail(a, 7);
	a = insert_at_tail(a, 8);
	a = insert_at_tail(a, 9);
	puts("before delete\n");
	print_node(a);

	len = lenght(a);
	printf("%d\n", len);


	a = delete_at_tail(a);
	puts("after delete\n");
	print_node(a);

	len = lenght(a);
	printf("%d\n", len);

	return 0;

}

int lenght(Node *head)
{
	Node *cur = head;
	int len = 0;
	while (cur != NULL)
	{
		len++;
		cur = cur->nxt;
	}
	return (len);
}


Node *delete_at_head(Node *head)
{
	if (head == NULL)
		return (NULL);
	else
	{
		Node *to_return = head->nxt;
		free(head);
		return (to_return);
	}
}

Node *delete_at_tail(Node *head)
{
	if (head == NULL)
		return (NULL);
	else if (head->nxt == NULL)
	{
		free(head);
		return (NULL);
	}
	else
	{
		int i, j = 0;
		Node *current = head;
		Node *ret = NULL;
		while (current->nxt != NULL)
		{
			ret = current;
			current = current->nxt;
		}
		ret->nxt = NULL;
		free(current);
		return (head);
	}
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

Node *insert_at_tail(Node *head, int value)
{
	Node *new_node = malloc(sizeof(Node));
	new_node->value = value;
	if (head == NULL)
		return (new_node);
	else
	{
		Node *current = head;
		while (current->nxt != NULL)
			current = current->nxt;
		current->nxt = new_node;
		return (head);
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

 