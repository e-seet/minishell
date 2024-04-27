// original code from pipex
#include "../utils.h"

char	*findprocesspath(char **paths, struct s_minishell *t_minishell, int commandid)
{
	int		i;
	char	*path;

	i = 0;


	char	**firstcommand = ft_split(t_minishell->commands[commandid], ' ');
	printf("firstcommand:%p\n\n", firstcommand);
	while (paths[i])
	{
		path = ft_strjoin(paths[i], "/");
		
		//temp
		path = ft_strjoin(path, firstcommand[0]);
		// path = ft_strjoin(path, "echo");
		// path = ft_strjoin(path, "ls");
		

		if (access(path, F_OK) == 0)
			break ;
		free (path);
		path = NULL;
		i++;
	}
	if (path != NULL && access(path, F_OK) == 0)
		return (path);
	else
		return (NULL);
}

void			program(struct s_minishell *t_minishell, int commandid)
{
	int		execveresult;
	char	**paths;
	char	*path;

	execveresult = -1;
	
	paths = NULL;
	paths = ft_split(t_minishell->path + 5, ':');

	// char *command = "ls -l"
	// char *commands = ft_split(command, ' ');


	path = findprocesspath(paths, t_minishell, commandid);
	if (path == NULL)
	{
		perror("3 Access Path not found");
		free(path);
		// exit (0);
	}

	// argvs: is the command splitted eg: ls -l to ls, -l. "grep eseet": grep, eseet

	// needs to be in this format
	// char *commands[] = {"/bin/echo", getenv("HOME"), NULL};
	
	// char *commands[] = {"ls", NULL};
	// char *commands[] = {"ls","-l", NULL};

	// printf("check the command:%s\n\n", t_minishell->commands[commandid]);
	

	// execveresult = execve(path, commands, t_minishell->envp);
	execveresult = execve(path, ft_split(t_minishell->commands[commandid], ' '), t_minishell->envp);

	// if ((pipexstruct->curr != pipexstruct -> opened) || pipexstruct->p1fd >= 0)
	// 	execveresult = execve(pipexstruct->path, pipexstruct->argvs3, envp);

	if (execveresult == -1)
		perror("Execve weent wrong while executing. Terminate now");
	// free(pipexstruct->path);
	// exit (0);
}