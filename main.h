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

#define BUFFER_SIZE 1024
#define STO 1
#define STE 2
#define v (void)
#define MAX_PATH 4096

extern char **environ;

void print(int stream, const char *format, ...);
int empty(const char *str);
void remov(char *str);
void line(char *cmd);
void handel_comment(const char *dest);

/* Built ins */
void cd_command(char **av, char **argv, size_t command_count,
char *command, char **colon);
void exit_command(char **av, char **argv, size_t command_count,
char *command, char **colon);

char *get_cwd(void);

int execute_builtin_command(char **av, char **argv, size_t command_count,
char *command, char **colon);
char *find_executable(char **av);
int execute_command(char **av, char **argv, int status,
size_t command_count, char st);
int exec(char *command, char **av, char **argv,
size_t command_count, char st, int status, char **colon);

void non_loop(char **av, char *command, size_t command_count,
FILE *fd, int status, char **argv, char **colon);
void _loop(int argc, char **av, char *command, size_t command_count,
FILE *fd, int status, char **argv, char **colon);

char *string(char *str, const char *del);
char **split_vector(char *cmd, char *dl);

void arg_free(char **av, char **colon);

int _strncmp(const char *s1, const char *s2, size_t n);
char *_strcat(char *dst, const char *src);
char *_strdup(const char *str);
size_t _strlen(const char *str);
char *_strstr(const char *str, const char *find);
char *_strcpy(char *dest, const char *src);
char *_strncpy(char *s1, const char *sc, size_t n);
int _strcmp(const char *s1, const char *s2);
char *_strchr(const char *str, int ch);
int _isdigit(int c);
int _atoi(const char *nptr);
int _isspace(int c);

char *get_env(const char *name);
int set_env(const char *name, const char *value, int overwrite);
int put_env(const char *string);


#endif /* MAIN_H */
