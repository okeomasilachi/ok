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
#define v (void)
#define MAX_PATH 4096

extern char **environ;

/**
 * struct environ_list - struct to store the env in a linked list
 * @NAME: name of the environ
 * @value: value
 * @next: pointer to the next Node
*/
typedef struct environ_list
{
	char *NAME;
	char *value;
	struct environ_list *next;
} env_list;

/**
 * struct list - struct to hold the alias of the shell
 * @NAME: alias to replace
 * @value: value of the alias
 * @next: pointer to the next Node
*/
typedef struct list
{
	char *NAME;
	char *value;
	struct list *next;
} alias;

/**
 * struct onyedibia - structs for the strtok funtion
 * @cur_tok_st: holds the current token
 * @nxt_tok_st: holds the next token
*/
typedef struct onyedibia
{
	char *cur_tok_st;
	char *nxt_tok_st;
} Tokenizer;

/**
 * struct variables - struct that holds all nessacery parameters
 * @command:holds argumentents for the ';' shell operation
 * @av: holds the arguments to be executed
 * @tok: holds tokens for s_tok
 * @tok2: holds tokens for s_tok
 * @N: holds the name of the program on execution
 * @ec: holds the full path for the execve funtion
 * @ok: support variable
 * @old: holds the value of the OLDPWD
 * @path: holds the path
 * @cmd: the initial commandline intake
 * @y: hold variable for the implementation of the "&&" and "||"
 * @status: holds the exit status of the last executed program
 * @i: for loop
 * @check: parameter check
 * @n: for the strlen of a string
 * @c: the number of command of the current shell process
 * @tokens: s_tok initialiser
 * @Hook: s_tok initialiser
 * @baxi: s_tok initialiser
 * @head: holds the env in a linked list
 * @pos: holds all aliases
 * @mypid: holds the process id of the shell
 * @child_pid: holds pid for the fork function
 * @it: hole the isatty value
*/
typedef struct variables
{
	char **command;
	char **av;
	char *tok;
	char *tok2;
	char *N;
	char *ec;
	char *ok;
	char *old;
	char *path;
	char *cmd;
	int y;
	int status;
	int i;
	int check;
	size_t n;
	ssize_t c;
	Tokenizer tokens;
	Tokenizer Hook;
	Tokenizer baxi;
	env_list *head;
	alias *pos;
	pid_t mypid;
	pid_t child_pid;
	bool it;
} okeoma;

void *p_Input();
void read_in(okeoma *oki);
void get_env_command(okeoma *oki);
void find_char(const char *dest, int character);
int find_set(char *str);
void unsetenv_command(okeoma *oki);
void setenv_command(okeoma *oki);
void exit_command(okeoma *oki);
void cd_command(okeoma *oki);
int execute_command(okeoma *oki);
char *find_executable(okeoma *oki);
int execute_builtin_command(okeoma *oki);
void B_exc(okeoma *oki);
void file(okeoma *oki, char *argv);
char *read_file(const char *filename);
char *read_lines(int fd);
int open_file(const char *filename);
void free_all(okeoma *oki);
char *s_tok(Tokenizer *tokenizer, const char *delimiters);
void f_tokenizer(Tokenizer *tokenizer, char *input_string);
void prs(okeoma *oki, char *coms);
void prs_2(okeoma *oki);
void _in(okeoma *oki, char **argv);
void fr__(size_t count, ...);
void read_input(char *buffer, int *buffer_pos, int *buffer_size);
char *_getline(char *buffer, int *buffer_pos, int *buffer_size);
void p(int stream, const char *format, ...);
void print_integer(int num, int n);
void print_string(char *s, int n);
void write_string(int n, const char *s);
int _isspace(int c);
void free_list(env_list *head);
char *get_env(env_list *env, const char *NAME);
env_list *list_from_env(char **env);
bool is_value(env_list *head, const char *value);
bool is_NAME(env_list *head, const char *NAME);
void print(env_list *head);
env_list *insert_env(env_list *head, const char *NAME, const char *value);
env_list *delete_match(env_list *head, char *delete_NAME);
void delete_duplicate(env_list *head);
env_list *revers_list(env_list *head);
void set_env_value(env_list *env, const char *NAME, const char *value);
char *get_cwd(void);
bool checker(char *arr);
char *second(okeoma *oki, char *av);
char *first(env_list *head, char *av);
void int_char(int n1, int n2, char **str);
void r_char(int value, char *str, int base);
char *replace(env_list *head, okeoma *oki, char *value);
void free_recursive(alias *head);
bool check_NAME(alias *head, const char *NAME);
void print_alias(alias *head, okeoma *oki);
void print_s_alias(alias *head, const char *NAME, okeoma *oki);
alias *insert(alias *head, const char *NAME, const char *value);
char *get_value(char *str);
void alias_(okeoma *oki);
char *command(alias *head, char *check);
bool alias_checker(alias *head, char *arr);
char *rem(char *str);
char **env_from_list(env_list *head);
char *strbind(const char *name, const char *value);
size_t list_len(env_list *head);
int empty(const char *str);
FILE *file_handle(okeoma *oki, int argc, char **argv);

#endif /* MAIN_H */
