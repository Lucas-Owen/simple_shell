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

void tokenize_input(char *buffer, char **tokens);
void evaluate_input(char **tokens, char **argv, char **env);
int eval_inbuilt_command(char *command, char** argv, char **envp);
char *eval_path(char *command, char **envp);

void print_env(char **envp);
char *get_env(char *name, char **envp);

void sigint_handler(int signum);
void sigquit_handler(int signum);

#endif
