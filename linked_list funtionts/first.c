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
int R_lenght(Node *node);
bool is_member(Node *head, int f_value);
int count_matches(Node *node, int f_value);
void replace_matches(Node *node, int f_value, int r_value);
Node *delete_first_match(Node *head, int delete_value, bool *was_deleted);
Node *delete_all_match(Node *head, int delete_value, int *num_deleted);
Node *efficient_delete_match(Node *head, int del_value, int *num_del);
Node *append_list(Node *head1, Node *head2);
Node *revers_list(Node *head);

int main(void)
{
	int len = 0, i, j;

	Node *a = NULL, *b = NULL;
	for (i = 1; i <= 5; i++)
		a = insert_at_tail(a, i);
	for (j = 6; j <= 10; j++)
		b = insert_at_tail(b, j);
	


	puts("before");
	print_node(a);
	puts("l 2");
	print_node(b);
	puts("after");
	a = append_list(a, b);
	print_node(a);
	
	a = revers_list(a);
	print_node(a);
	return 0;

}

Node *revers_list(Node *head)
{
	if (head == NULL) return NULL;
	if (head->nxt == NULL) return head;

	Node *current = head;
	Node *next = head->nxt;

	current->nxt = NULL;

	while (next != NULL)
	{
		Node *tmp = next->nxt;
		next->nxt = current;
		current = next;
		next = tmp;
	}
	return (current);	
}


Node *append_list(Node *head1, Node *head2)
{
	if (head1 == NULL) return head2;
	Node *current = head1;
	while (current->nxt != NULL) current = current->nxt;
	current->nxt = head2;
	return (head1);
}


Node *efficient_delete_match(Node *head, int del_value, int *num_del)
{
	*num_del = 0;

	if (head == NULL) return (NULL);

	Node *cur, *tmp, *new_head;

	cur = head;
	while (cur != NULL && cur->value == del_value)
	{
		tmp = cur;
		cur = cur->nxt;
		free(tmp);
		*num_del = *num_del + 1;
	}
	new_head = cur;
	while (cur != NULL && cur->nxt != NULL)
	{
 		if (cur->nxt->value == del_value)
		{
			tmp = cur->nxt;
			cur->nxt = cur->nxt->nxt;
			free(tmp);
			*num_del = *num_del + 1;
		}
		else cur = cur->nxt;
	}
	return (new_head);
}


Node *delete_all_match(Node *head, int delete_value, int *num_deleted)
{
	Node *current = head;
	bool deleted = false;
	*num_deleted = 0;

	do
	{
		current = delete_first_match(current, delete_value, &deleted);
		if (deleted) *num_deleted = *num_deleted + 1;
	} while (deleted);
	
	return (current);
}


Node *delete_first_match(Node *head, int delete_value, bool *was_deleted)
{
	if (head == NULL)
	{
		*was_deleted = false;
		return (NULL);
	}
	if (head->value == delete_value)
	{
		Node *temp = head->nxt;
		free(head);
		*was_deleted = (true);
		return (temp);
	}
	Node *current = head->nxt;
	Node *prev = head;
	while (current != NULL)
	{
		if (current->value == delete_value)
		{
			prev->nxt = current->nxt;
			free(current);
			*was_deleted = true;
			return (head);
		}
		prev = current;
		current = current->nxt;
	}
	*was_deleted = false;
	return (head);
}


void replace_matches(Node *node, int f_value, int r_value)
{
	if (node != NULL)
	{
		if (node->value == f_value)
			node->value = r_value;
		replace_matches(node->nxt, f_value, r_value);
	}
}

int count_matches(Node *node, int f_value)
{
	if (node == NULL) return (0);
	else if (node->value == f_value)
		return (1 + count_matches(node->nxt, f_value));
	else return (count_matches(node->nxt, f_value));

}


bool is_member(Node *head, int f_value)
{
	if (head == NULL) return false;
	else if (head->value == f_value) return true;
	else return is_member(head->nxt, f_value);
}


int R_lenght(Node *node)
{
	if (node == NULL) return (0);
	else return (1 + R_lenght(node->nxt));
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
	int i = 1;
	Node *current;
	current = head;

	while (current != NULL)
	{
		printf("node at %d: = %d\n", i, current->value);
		i++;
		current = current->nxt;
	}
	
}

 