#ifndef MAIN_H
#define MAIN_H

#include <limits.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/resource.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <unistd.h>

#define MAX_TOKENS 100
extern char **environ;

int _getline(char *buf, FILE *stream);

char *_strtok(char **str, char *delim);
void tokenize_input(char *buffer, char **tokens, char **envp, int *status);

char *eval_variable(char *variable, char **envp, int *status);

void evaluate_input(char **, char **, char **, int, int, int *);
int eval_inbuilt_command(char **, char **, char **, int, int *);
char *eval_path(char *command, char **envp);

void free_tokens(char **tokens);
void eval_exit(char **argv, char **tokens, int, int *);
void change_dir(char **argv, char **tokens, char **envp, int *status);
void set_env(char **tokens, int *status);
void unset_env(char **tokens, int *status);

void print_env(char **envp);
char *get_env(char *name, char **envp);

#endif
