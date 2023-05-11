#ifndef MAIN_H
#define MAIN_H

#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <sys/wait.h>

void tokenize_input(char *buffer, char **tokens);
void evaluate_input(char **tokens, char **argv, char **env);
void print_env(char **envp);

void sigint_handler(int signum);
void sigquit_handler(int signum);

#endif
