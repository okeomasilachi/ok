#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdarg.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <ctype.h>
#include <limits.h>

#define BUFFER_SIZE 1024

extern char **environ;

/**
 * struct okeoma - structs fro the strtok funtion
 * @cur_tok_st: holds the current token
 * @nxt_tok_st: holds the next token
*/
typedef struct okeoma
{
	char *cur_tok_st;
	char *nxt_tok_st;
} Tokenizer;

typedef struct
{
	char *cmd;
	char **av;
	char *tok;
	char *Name;
	char *ec;
	char *ok;
	char *old;
	char *new;
	char **command;
	int y;
	int status;
	int i;
	size_t n;
	size_t com_num;
	Tokenizer tokens;
	Tokenizer Hook;
	Tokenizer baxi;
	pid_t child_pid;
	bool it;
} okeoma;

void interactive(okeoma *info);
void non_interactive(okeoma *info);

void *p_Input();
char *read_in();

void help_command(okeoma *info);
void unsetenv_command(okeoma *info);
void setenv_command(okeoma *info);
void exit_command(okeoma *info);
void cd_command(okeoma *info);
int execute_command(okeoma *info);
char *find_executable(okeoma *info);
int execute_builtin_command(okeoma *info);
void B_exc(okeoma *info);
char *env_pos(okeoma *info);
void free_all(okeoma *info);

void f_tokenizer(okeoma *info, char *cm);
char *s_tok(okeoma *info, const char *delimiters);
void prs(okeoma *info, size_t del_n);
void prs_2(okeoma *info, size_t del_n);
void _in(okeoma *info, char **argv);

void _fee(int count, ...);
void read_input(char *buffer, int *buffer_pos, int *buffer_size);
char *_getline(char *buffer, int *buffer_pos, int *buffer_size);

#endif /* MAIN_H */