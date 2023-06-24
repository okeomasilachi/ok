#include "main.h"


char *value(char *str)
{
	char *val = strdup(str);

	if (strstr(val, "$") != NULL)
	{
		val = (strstr(val, "$") + 1);
		return (val);
	}

	return (NULL);
}

bool checker(char *arr)
{
	if (arr == NULL) return false;
	else if (strstr(arr, "$") != NULL) return true;
	else return false;
}

void r_char(int value, char* str, int base)
{
	int i, is_neg, rem, len, st, ed;
	char temp;

	if (value == 0)
	{
		str[0] = '0';
		str[1] = '\0';
		return;
	}
	i = 0;
	is_neg = 0;
	
	if (value < 0 && base == 10)
	{
		is_neg = 1;
		value = -value;
	}
	while (value != 0)
	{
		rem = value % base;
		str[i++] = (rem > 9) ? (rem - 10) + 'A' : rem + '0';
		value /= base;
	}
	if (is_neg)
		str[i++] = '-';

	str[i] = '\0';
	len = strlen(str);
	st = 0;
	ed = len - 1;
	while (st < ed)
	{
		temp = str[st];
		str[st] = str[ed];
		str[ed] = temp;
		st++;
		ed--;
	}
}


void int_char(int n1, int n2, char **str)
{
	str[0] = malloc(20);
	str[1] = malloc(20);

	r_char(n1, str[0], 10);
	r_char(n2, str[1], 10);
}

char *first(env_list *head, char *av)
{
	env_list *cur = head;
	char *tok = NULL, *rep = NULL, *rem = NULL, *va = NULL, *new;
	int len;
	size_t n_size;

	va = strdup(av);
	while (cur != NULL)
	{
		len = strlen(cur->NAME) + 2;
		tok = malloc(len);
		strcat(tok, "$");
		strcat(tok, cur->NAME);
		if ((rep = strstr(va, tok)) != NULL)
		{
			len = strlen(tok);
			if(strncmp(rep, tok, len) == 0)
			{
				rem = strdup(rep + len);
				n_size = strlen(cur->value) + strlen(rem) + 1;
				new = malloc(n_size);
				strcpy(new, cur->value);
				strcat(new, rem);
				memcpy(rep, new, n_size);
				free(rem), free(new), free(tok);
				return (va);
			}
		}
		cur = cur->next;
	}
	free(tok), free(va);
	return (av);
}


char *second(okeoma *oki, char *av)
{
	char *val = NULL, *rem = NULL, *va = NULL, *new;
	char *expand[] = {"$$", "$?"}, *ex[2];
	int len, i = 0;
	size_t n_size;

	if (checker(av) == true)
	{
		va = strdup(av);
		val = strstr(va, "$");
		int_char(oki->mypid, oki->status, ex);
		while (expand[i] != NULL)
		{
			if ((val = strstr(va, expand[i])) != NULL)
			{
				len = strlen(expand[i]);
				if(strncmp(val, expand[i], len) == 0)
				{
					rem = strdup(val + len);
					n_size = strlen(ex[i]) + strlen(rem) + 1;
					new = malloc(n_size);
					strcpy(new, ex[i]);
					strcat(new, rem);
					memcpy(val, new, n_size);
					free(rem), free(new);
					return (va);
				}
			}
			i++;
		}
	}
	free(va);
	return (av);
}

char *replace(env_list *head, okeoma *oki,char *value)
{
	bool check;
	char *sec = strdup(value);
				
	check = checker(sec);
	while (check == true)
	{
		sec = first(head, sec);
		sec = second(oki, sec);
		
		check = checker(sec);
	}
	return (sec);
}

/*int main(void)
{
	char al[] = "echo $HOME $$ $? $PWD okeoma$$jkn";
	char *ve = malloc(20);
	bool check;
	okeoma *me = malloc(sizeof(okeoma));
	me->mypid = getpid();
	me->status = 100;
	me->head = list_from_env(environ);

	strcpy(ve, al);
	ve = replace(me->head, me, ve);
	printf("%s\n", ve);

	return (0);
}*/
