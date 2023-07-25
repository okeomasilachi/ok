#include "shell.h"

/**
 * f_tokenizer - the initializer for string tokenization
 * @tokenizer: struct for storing the tokens
 * @input_string: string to tokenize
 *
 * Return: void
*/
void f_tokenizer(Tokenizer *tokenizer, char *input_string)
{
	tokenizer->cur_tok_st = input_string;
	tokenizer->nxt_tok_st = input_string;
}

/**
 * s_tok - function for tokenizing strings
 * @tokenizer: struct where token are stored
 * @delimiters: the delimeters for the tokenization
 *
 * Return: pointer to token
 * error: NULL if no more tokens are found
*/
char *s_tok(Tokenizer *tokenizer, const char *delimiters)
{
	char *token;

	if (tokenizer->cur_tok_st == NULL)
		return (NULL);
	/* Skip leading delimiters */
	tokenizer->cur_tok_st += strspn(tokenizer->cur_tok_st, delimiters);
	/* Check if end of string is reached */
	if (*tokenizer->cur_tok_st == '\0')
	{
		tokenizer->cur_tok_st = NULL;
		return (NULL);
	}
	tokenizer->nxt_tok_st = tokenizer->cur_tok_st;
	/* Find the end of the current token */
	tokenizer->nxt_tok_st += strcspn(tokenizer->nxt_tok_st, delimiters);
	if (*tokenizer->nxt_tok_st != '\0')
	{
		*tokenizer->nxt_tok_st = '\0';
		tokenizer->nxt_tok_st++;
	}
	else
	{
		tokenizer->nxt_tok_st = NULL;
	}
	token = tokenizer->cur_tok_st;
	tokenizer->cur_tok_st = tokenizer->nxt_tok_st;

	return (token);
}

/**
 * prs - parses input command to tokens
 * @oki: struct of type okeoma
 * @coms: string to the parsed
 *
 * Return: void
*/
void prs(okeoma *oki, char *coms)
{
	char *com_cpy = NULL, *dl = " \t\n\r";
	size_t count = 0, cnt = 0;

	if (oki->cmd)
	{
		com_cpy = strdup(coms);
		f_tokenizer(&oki->baxi, coms);
		oki->tok = s_tok(&oki->baxi, dl);
		while (oki->tok)
		{
			cnt++;
			oki->tok = s_tok(&oki->baxi, dl);
		}
		cnt++;
		oki->av = malloc(sizeof(char *) * (cnt + 1));
		f_tokenizer(&oki->baxi, com_cpy);
		oki->tok = s_tok(&oki->baxi, dl);
		while (oki->tok)
		{
			oki->av[count] = malloc(sizeof(char) * (_strlen(oki->tok) + 1));
			_strcpy(oki->av[count], oki->tok);
			oki->tok = s_tok(&oki->baxi, dl);
			count++;
		}
		oki->av[count] = NULL;
		free(com_cpy);
		com_cpy = NULL;
		count = 0, cnt = 0;
	}
}

/**
 * prs_2 - parses input command to tokens
 * @oki: struct of type okeoma
 *
 * Return: void
*/
void prs_2(okeoma *oki)
{
	char *com_cpy = NULL, *dl = ";\n";
	size_t count = 0, cnt = 0;

	if (oki->cmd)
	{
		com_cpy = strdup(oki->tok2);
		f_tokenizer(&oki->Hook, oki->tok2);
		oki->tok = s_tok(&oki->Hook, dl);
		while (oki->tok)
		{
			cnt++;
			oki->tok = s_tok(&oki->Hook, dl);
		}
		cnt++;
		oki->command = malloc(sizeof(char *) * (cnt + 1));
		f_tokenizer(&oki->Hook, com_cpy);
		oki->tok = s_tok(&oki->Hook, dl);
		while (oki->tok)
		{
			oki->command[count] = malloc(sizeof(char) * (_strlen(oki->tok) + 1));
			_strcpy(oki->command[count], oki->tok);
			oki->tok = s_tok(&oki->Hook, dl);
			count++;
		}
		oki->command[count] = NULL;
		free(com_cpy);
		com_cpy = NULL;
		count = 0, cnt = 0;
	}
}
