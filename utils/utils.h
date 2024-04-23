
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
// #include <readline/readline.h>
// #include <readline/history.h>
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

// extra: To check if allowed libraries
#include <errno.h>
#include <term.h>
#include <curses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// #include <readline/readline.h>

// mac os
// #include <editline/readline.h>

// lexical file
void			lexical(char *str);

// lexicalutils
int				ft_is_output_redirect(char *str);
int				ft_is_append_output_redirect(char *str);
int				ft_is_input_redirect(char *str);
int				ft_is_heredoc_redirect(char *str);
int				ft_is_conditional_or(char *str);

// lexicalutils2
int				ft_is_pipe(char *str);
int				ft_is_double_ampersand(char *str);
int				ft_is_bracket1(char *str);
int				ft_is_bracket2(char *str);

// program file
void			program(char *envp[]);

// parser folder
// nodeops
struct AST_Node *ft_createNode(char **strs, int num);
// parser
void			parser(char **strs);
// void	parser(char *str, char *envp[]);
 
// left sub tree
void			leftSubTree(struct AST_Node *rootnode, char **strs, int end);
void			checkLeftSubTree(struct AST_Node *rootnode);
void			inorderTraversal_L(struct AST_Node* root);

// right sub tree
void			rightSubTree(struct AST_Node *rootnode, char **strs, int start, int end);
void			checkRightSubTree(struct AST_Node *rootnode);
void			leftSubTree2(struct AST_Node *rootnode, char **strs, int i, int end);

//setup
void			setupstruct(struct s_minishell *t_minishell, char *envp[]);

//commands
void			updatepwd(struct s_minishell *t_minishell);

// change directory
void			changedirectory(char *str, struct s_minishell *t_minishell);

// env
void			exportstr(char *str, struct s_minishell *t_minishell);
void			unsetmyenv(char *str, struct s_minishell *t_minishell);
void			envvariables(struct s_minishell *t_minishell, char *envp[]);

#endif