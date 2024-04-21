// original code from pipex

char	*findprocesspath(char **paths)
{
	int		i;
	char	*path;

	i = 0;
	while (paths[i])
	{
		path = ft_strjoin(paths[i], "/");
		path = ft_strjoin(path,
				pipexstruct->argvs3[0]);
		free(path);
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

void	program(char *envp[])
{
	int		execveresult;
	char	**paths;

	execveresult = -1;
	path = findpath(envp);
	paths = ft_split(path + 5, ':');

	path = findprocesspath(paths);
	if (path == NULL)
	{
		perror("3 Access Path not found");
		free(path);
		// exit (0);
	}

	// path is the path to execute eg: bin
	// argvs: is the command splitted eg: ls -l to ls, -l. "grep eseet": grep, eseet
	execveresult = execve(pipexstruct->path, pipexstruct->argvs3, envp);

	// if ((pipexstruct->curr != pipexstruct -> opened) || pipexstruct->p1fd >= 0)
	// 	execveresult = execve(pipexstruct->path, pipexstruct->argvs3, envp);
	// if (execveresult == -1)
	// 	perror("Execve weent wrong while executing. Terminate now");
	// free(pipexstruct->path);
	exit (0);
}