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

/* extern char **environ; */

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
	env_list *head;
	alias *pos;
	pid_t mypid;
	pid_t child_pid;
	bool it;
} okeoma;

/* alias functions */
void free_recursive(alias *head);
bool check_NAME(alias *head, const char *NAME);
void print_alias(alias *head, okeoma *oki);
void print_s_alias(alias *head, const char *NAME, okeoma *oki);
alias *insert(alias *head, const char *NAME, const char *value);
bool null_check(char *ok);
char *get_value(char *str);
bool alias_checker(alias *head, char *arr);
char *command(alias *head, char *check);
int number(char *str, char *match);
int position(char *str, char *srh);
char *rem(char *str);

/* built-ins */
void cd_command(okeoma *oki);
void exit_command(okeoma *oki);
void setenv_command(okeoma *oki);
void unsetenv_command(okeoma *oki);
void get_env_command(okeoma *oki);
void alias_(okeoma *oki);
char *get_cwd(void);

/* env & env_list functions */
env_list *list_from_env(char **env);
char **env_from_list(env_list *head);
env_list *insert_env(env_list *head, const char *NAME, const char *value);
env_list *delete_match(env_list *head, char *delete_NAME);
void free_list(env_list *head);
void set_env_value(env_list *env, const char *NAME, const char *value);
char *get_env(env_list *env, const char *NAME);
bool is_value(env_list *head, const char *value);
bool is_NAME(env_list *head, const char *NAME);
void print(env_list *head);
size_t list_len(env_list *head);
char *strbind(const char *name, const char *value);

/* variable exapantion functions */
bool checker(char *arr);
void r_char(int value, char *str, int base);
void int_char(int n1, int n2, char **str);
char *first(env_list *head, char *av);
char *second(okeoma *oki, char *av);
char *replace(env_list *head, okeoma *oki, char *value);

/* input functions */
void read_input(char *buffer, int *buffer_pos, int *buffer_size);
char *_getline(char *buffer, int *buffer_pos, int *buffer_size);
void *p_Input();
void read_in(okeoma *oki);

/* general free functions */
void free_all(okeoma *oki);
void fr__(size_t count, ...);

/* stream write functions (mini-dprintf) */
void p(int stream, const char *format, ...);
void print_integer(int num, int n);
void write_string(int n, const char *s);
void print_string(char *s, int n);
int _isspace(int c);

/* parser's */
char *str_tok(char *str, const char *del);
char *string(char *str, const char *del);
void prs(okeoma *oki, char *coms);
void prs_2(okeoma *oki);

/* miscellaneous */
void sig(int num);
void line(char *cmd);
void _in(okeoma *oki, char **argv, char **env);
void remov(char *str);
void File(char *filename, okeoma *oki);

/* shell main processing functions */
int execute_builtin_command(okeoma *oki);
int execute_command(okeoma *oki);
char *find_executable(okeoma *oki);
void B_exc(okeoma *oki);
FILE *file_handle(okeoma *oki, int argc, char **argv);

/* string & memory manipulators */
char *_strcat(char *dest, const char *src);
char *_strchr(const char *s, int c);
char *_strncpy(char *dest, char *src, int n);
int _strcmp(char *s1, const char *s2);
char *_strstr(char *haystack, const char *needle);
int _isdigit(int c);
size_t _strlen(const char *str);
char *_strdup(const char *str);
int _strncmp(const char *s1, const char *s2, size_t n);
size_t _strcspn(const char *str, const char *reject);
void *_memcpy(void *dest, const void *src, size_t n);
void *_memmove(void *dest, const void *src, size_t n);
int _atoi(const char *nptr);
void *_realloc(void *ptr, size_t size);
char *_strcpy(char *dest, const char *src);

/* support functions */
void find_char(const char *dest, int character);
int find_set(char *str);
int empty(const char *str);

/* loops */
void file_loop(okeoma *oki, size_t n, ssize_t byte_r, char st, FILE *fd);
void non_loop(okeoma *oki, size_t n, ssize_t byte_r, char st, FILE *fd);
void _loop(int argc, okeoma *oki, size_t n, ssize_t byte_r, char st, FILE *fd);


#endif /* MAIN_H */
