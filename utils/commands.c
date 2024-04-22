#include "utils.h"

void updatepwd(struct s_minishell *t_minishell)
{
	char *currpwd;

	currpwd = ft_calloc(1024, sizeof(char));

	currpwd = getcwd(currpwd, 1024);
	if (t_minishell->currpwd != NULL)
	{
		free(t_minishell->currpwd);
	}
	t_minishell->currpwd = currpwd;
	if (!t_minishell->currpwd)
		printf("error in getting curr pwd");

	// printf("curr pwd: %s\n", t_minishell->currpwd);
}


