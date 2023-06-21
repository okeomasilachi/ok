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
#include <signal.h>
#include <time.h>

#define BUFFER_SIZE 1024

#define STO 1
#define STE 2

extern char **environ;

typedef struct
{
	char *NAME;
	char *value;
	struct env_list *next;
} env_list;

/**
 * struct okeoma - structs for the strtok funtion
 * @cur_tok_st: holds the current token
 * @nxt_tok_st: holds the next token
*/
typedef struct
{
	char *cur_tok_st;
	char *nxt_tok_st;
} Tokenizer;

typedef struct variables
{
	char **command;
	char **av;
	char *tok;
	char *tok2;
	char *Name;
	char *ec;
	char *ok;
	char *old;
	char *new;
	char *cmd;
	int y;
	int status;
	int i;
	size_t n;
	ssize_t com_num;
	Tokenizer tokens;
	Tokenizer Hook;
	Tokenizer baxi;
	env_list *head;
	pid_t child_pid;
	bool it;
} okeoma;

void interactive(okeoma *oki);
void non_interactive(okeoma *oki);

void *p_Input();
void read_in(okeoma *oki);

void env_command(okeoma *oki);
void get_env_command(okeoma *oki);
void find_char(okeoma *oki);
int find_set(char *str);
void unsetenv_command(okeoma *oki);
void setenv_command(okeoma *oki);
void exit_command(okeoma *oki);
void cd_command(okeoma *oki);
int execute_command(okeoma *oki);
char *find_executable(okeoma *oki);
int execute_builtin_command(okeoma *oki);
void B_exc(okeoma *oki);
void process(okeoma *oki);
void file(okeoma *oki, char *argv);
char *read_file(const char *filename);
char *read_lines(int fd);
int open_file(const char *filename);
char *env_pos(okeoma *oki);
void free_all(okeoma *oki);
int _put(const char *str);
int _putchar(char c);
char *s_tok(Tokenizer *tokenizer, const char *delimiters);
void f_tokenizer(Tokenizer *tokenizer, char *input_string);
void prs(okeoma *oki, char *coms);
void prs_2(okeoma *oki);
void _in(okeoma *oki, char **argv);
void my_free(size_t count, ...);
void read_input(char *buffer, int *buffer_pos, int *buffer_size);
char *_getline(char *buffer, int *buffer_pos, int *buffer_size);
void p(int stream, const char *format, ...);
void print_integer(int num, int n);
void print_string(char *s, int n);
void write_string(int n, const char *s);
int _isspace(int c);

void free_list(alias *head);
char *get_env(alias *env, const char *NAME);
alias *list_from_env(char **env);
bool is_value(alias *head, const char *value);
bool is_NAME(alias *head, const char *NAME);
void print(alias *head);
alias *insert_env(alias *head, char *NAME, char *value);
alias *delete_match(alias *head, char *delete_NAME);
void delete_duplicate(alias *head);
alias *revers_list(alias *head);
void set_env_value(alias *env, const char *NAME, const char *value);
/*-------------------------------------------------------------------*/
void _alias(okeoma *oki);
void define_alias(alias *head, char *name);
alias *add_alias(alias *head, char *name, char *value);
void print_aliases(alias *head, char *name);
void process_array(alias *head, char **array);
int replace_with_alias(alias *head, char *str);



#endif /* MAIN_H */