#include "utils.h"

// find the long long path in envp.
// returns a long string of paths
// need to use ft_split to get back the various paths
// ft_split(path + 5, ':');
// 5 to skip the first few characters
char	*findpath(char *envp[])
{
	int		i;
	char	*path;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp("PATH=", envp[i], 5) == 0)
		{
		
				path = envp[i];
			break ;
		}
		i++;
	}
	if (ft_strncmp("PATH=", path, 5) == 0)
		return (path);
	else
		return (NULL);
}

// paths is to execute a program using execve
// will need to loop through it to find the right bin to execute the command.

void setupstruct(struct s_minishell *t_minishell, char *envp[])
{
	char *currpwd;

	int i = 0;
	while(envp[i])
	{
		i++;
	}
	t_minishell->envp = ft_calloc(i+1, sizeof(char *));
	i--;
	t_minishell->envplen = i;

	// we set up the env variables here. 
	// need to update whenever we set and unset too
	envvariables(t_minishell, envp); //temp here

	t_minishell->path = findpath(envp);
	t_minishell->paths = ft_split(t_minishell->path + 5, ':');
	
	currpwd = ft_calloc(1024, sizeof(char));

	currpwd = getcwd(currpwd, 1024);
	t_minishell->currpwd = currpwd;
	if (!t_minishell->currpwd)
		printf("error in getting curr pwd");
	printf("curr pwd: %s\n", t_minishell->currpwd);


	// For Paths and Path
	// print if required to know the content
	// printf("path:%s\n\n", t_minishell->path);
	// int i;
	// i = 0;
	// while (t_minishell->paths[i])
	// {
	// 	printf("path%d: %s\n", i, t_minishell->paths[i]);
	// 	i++;
	// }


		
}