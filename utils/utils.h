
#ifndef UTILS_H
# define UTILS_H

#define RED "\033[1;31m";

// libft
# include "../libft/libft.h"
// gnl
# include "../get_next_line/get_next_line.h"

// my structs that is required
# include "struct.h"

// libraries required
#include <readline/readline.h>
#include <readline/history.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <unistd.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>
#include <termios.h>
#include <termcap.h>

// lexical file
void	lexical(char *str, char *envp[]);

// program file
void	program(char *envp[]);

// parser file
void	parser(char *str, char *envp[]);

//setup
void	setupstruct(struct s_minishell *t_minishell, char *envp[]);

#endif