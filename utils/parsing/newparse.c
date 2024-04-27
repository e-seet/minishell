#include "../utils.h"

void removespaces(struct s_minishell *t_minishell, int start, int len, int pos)
{
	printf("removespaces\n");
	// start of empty
	// len how many spaces

	char *str = t_minishell->commands[pos];
	
	int newlen = ft_strlen(str) - len + 1;

	char *newstr = ft_calloc(newlen, sizeof(char));

	int i = 0;

	while (start > i)
	{
		newstr[i] = str[i];
		i++;
	}

	while (newlen > i)
	{
		newstr[i] = str[i + len];
		i++;
	}

	free(t_minishell->commands[pos]);
	t_minishell->commands[pos] = newstr;
}

void	removeemptystr(struct s_minishell *t_minishell, int pos)
{
	int i;
	char *str;
	
	// char *cleanedstr;
	// cleanedstr = NULL;

	// int doublequote;
	// int singlequote;

	// doublequote = 0;
	// singlequote = 0;
	
	i = 0;
	int len = 1;
	str = t_minishell->commands[pos];

	while (str[i] != '\0')
	{
		// check that is is a quotation
		if
		(
			ft_is_double_quote(&str[i]) == 1
		)
		{
			while (str[i + len] != '\0')
			{
				if (ft_is_whitespaces(&str[i+len]) == 1)
				{
					len++;
				}
				else if
				(
					ft_is_double_quote(&str[i + len]) == 1
				)
				{
					removespaces(t_minishell, i, len + 2, pos); //start and ending so +2
					break ;
				}
				else
				{
					break;
				}
			}
		}
		else if
		(
			ft_is_single_quote(&str[i]) == 1			
		)
		{
			while (str[i + len] != '\0')
			{
				if (ft_is_whitespaces(&str[i+len]) == 1)
				{
					len++;
				}
				else if
				(
					ft_is_single_quote(&str[i + len]) == 1
				)
				{
					removespaces(t_minishell, i, len + 2, pos); //start and ending so +2
					break ;
				}
				else
				{
					break;
				}
			}

		}

		i ++;
	}
}

char *findtheenvvariable(char *variablename, struct s_minishell *t_minishell)
{
	int i;

	i = 0;
	char *variablename_replacement;

	variablename_replacement = NULL;

	// printf("variable name:%s\n", variablename);
	// printf("variable: %s, %zu\n" ,&variablename[1], ft_strlen(&variablename[1]));

	while (t_minishell->envp[i])
	{
		char **envpvariable = ft_split(t_minishell->envp[i], '=');
		// printf("i:%d,%s || %s\n", i, envpvariable[0], envpvariable[1]);

		if (ft_strncmp(envpvariable[0], &variablename[1], ft_strlen(&variablename[1])) == 0)
		{
			// printf("found\n");
			// free(variablename);
			variablename_replacement = ft_calloc(ft_strlen(envpvariable[1]) + 1, sizeof(char));
			ft_strlcpy(variablename_replacement, envpvariable[1], ft_strlen(envpvariable[1]) +1 );
			break;
		}
		i++;
	}
	return variablename_replacement;
}

// loop through all the variables to find matching and replace if required
void replacement(char *variablename, char *str, int len1, struct s_minishell *t_minishell, int pos)
{
	printf("replacement\n");
	char *newstr;
	int i;
	int len2;
	int len3;
	char *envvariable;

	newstr = NULL;
	envvariable = findtheenvvariable(variablename, t_minishell);

	// something to replace it
	if (envvariable != NULL)
	{
		newstr = ft_calloc(ft_strlen(envvariable) + ft_strlen(str) + 1, sizeof(char));
		
		// until i
		i = 0;
		// until variable name end 
		len2 = ft_strlen(envvariable);

		// copy the first half
		while (len1 > i)
		{
			newstr[i] = str[i];
			i++;
		}


		// copy the new one
		while (len2--)
		{
			newstr[i + len2] = envvariable[len2];
		}
		i = i  + ft_strlen(envvariable) + 1;
		
		// second half of whatever that is remaining
		len3 = ft_strlen(str) - len1;
		while (len3--)
		{
			newstr[i + len3] = str[len1 + len3];
			i++;
		}

		free(t_minishell->commands[pos]);
		t_minishell->commands[pos] = newstr;
		// free(str);
		// str = newstr;
		// printf("newstr:%s", newstr);

	}

}


// Break and return accordingly
char	*getvariablename(char *str, int i)
{
	int len;
	char *variable;
	int temp;
	
	temp = 0;
	len = 0;
	while (str[i+len] != ' ' && str[i+len] != '\0')
	{
		len ++;
	}
	variable = ft_calloc(len+1, sizeof(char));
	while (len > temp)
	{
		variable[temp] = str[i + temp];
		temp ++;
	}
	variable[temp] = '\0';
	return (variable);
}

// void	checkforvariable(char *str, struct s_minishell *t_minishell)
void	checkforvariable(struct s_minishell *t_minishell, int pos)
{
	int i;
	char *variablename;
	char *str;

	str = t_minishell->commands[pos];

	i = 0;
	while (str[i])
	{
		if (ft_is_dollar(&str[i]) == 1)
		{
			// get the variable name of interest
			variablename = getvariablename(str, i);	
			printf("variable name:%s\n", variablename);
			// printf("variable name:%s", variablename);
			// note i may have more than 1 variable in a single string too

			replacement(variablename, str, i, t_minishell, pos);
			// break;

		}
		i++;
	}
}

void	subvariable(struct s_minishell *t_minishell)
{
	int i = 0;

	while (t_minishell->commandlen > i)
	{
		// Convert any variale with t_minishell->envp
		checkforvariable(t_minishell, i);
		printf("\n");
		i ++;
	}

	printf("check it is replaced\n\n");
	
	i = 0;
	while (t_minishell->commandlen > i)
	{
		printf("i:%d, %s\n", i, t_minishell->commands[i]);
		i ++;
	}
	// printf("\n\n\nend of subvariable\n");
}

void removeallwhitespaces(struct s_minishell *t_minishell)
{
	int i = 0;

	while (t_minishell->commandlen > i)
	{
		// remove strings like " " '   '
		// should do towards the end
		removeemptystr(t_minishell, i);
		printf("\n");
		i ++;
	}

	i = 0;
	while (t_minishell->commandlen > i)
	{
		printf("i:%d, %s\n", i, t_minishell->commands[i]);
		i ++;
	}
}

// strs is broken up by the 4 redirects
// the 2 brackets

// Example: command > file.txt
// This command runs command and writes its output to file.txt, overwriting the file if it already exists. If the file doesn't exist, it will be created.

// Example: command >> file.txt
// This command runs command and appends its output to the end of file.txt. If the file doesn't exist, it will be created.

// ls > files.txt
// This command runs ls to list the files in the current directory and redirects its output to the file files.txt. If files.txt already exists, it will be overwritten; otherwise, a new file will be created.

// echo "This is a new line" >> files.txt
// This command appends the text "This is a new line" to the end of the file files.txt. If files.txt doesn't exist, it will be created. If it does exist, the text will be added to the end of the file without overwriting its contents.
void newparse(char **strs, int i, struct s_minishell *t_minishell)
{
	int end;
	char *command;
	char **commands;

	end = i;
	i = 0;

	// printf("%d, %p, %p", i, strs, t_minishell);

	command = NULL;
	while (i < end)
	{
		// currently is a pipe
		if (ft_is_pipe(strs[i]) == 1 || ft_is_semicolon(strs[i]) == 1)
		{
			// printf("found pipe\n");	
			// printf("command:%s \n", command);

			if (t_minishell->commandlen == 0)
			{
				t_minishell->commands = ft_calloc(1, sizeof(char *));
				t_minishell->commands[0] = ft_calloc(ft_strlen(command) + 1, sizeof(char));
				ft_strlcpy(t_minishell->commands[0], command, ft_strlen(command));
				t_minishell->commandlen = t_minishell->commandlen + 1;	


				free(command);
				command = NULL;
				printf("command:%s", t_minishell->commands[0]);
			}
			else
			{
				int old = 0;
				// int new = 0;

				t_minishell->commandlen = t_minishell->commandlen + 1;	
				commands = ft_calloc(t_minishell->commandlen+1, sizeof(char *));


				while (t_minishell->commandlen -1 > old)
				{
					commands[old] = ft_calloc(ft_strlen(t_minishell->commands[old])+1, sizeof(char));
					ft_strlcpy(commands[old], t_minishell->commands[old], ft_strlen(t_minishell->commands[old]) +1);

					// printf("new:%s\n", commands[old]);
					// printf("old:%s\n", t_minishell->commands[old]);

					free(t_minishell->commands[old]);
					old ++;
				}

				commands[old] = ft_calloc(ft_strlen(command), sizeof(char));
				ft_strlcpy(commands[old], command, ft_strlen(command)+1);
				t_minishell->commands = commands;

				free(command);
				command = NULL;

			}

		}
		// May need 
		// else if (ft_is_semicolon(strs[i]) == 1)

		// << < >> >
		else if (
			ft_is_heredoc_redirect(strs[i]) == 1
			|| ft_is_output_redirect(strs[i]) == 1
			|| ft_is_append_output_redirect(strs[i]) == 1
			|| ft_is_input_redirect(strs[i]) == 1
		)
		{
			// printf("found redirect\n");
			if (command == NULL)
			{
				command = ft_calloc(ft_strlen(strs[i]), sizeof(char));
				ft_strlcpy(command, strs[i], ft_strlen(strs[i])+1);
			}
			else
			{
				command = ft_strjoin(command, strs[i]);
			}

		}
		else
		{
			
			if (command == NULL)
			{
				command = ft_calloc(ft_strlen(strs[i]), sizeof(char));
				ft_strlcpy(command, strs[i], ft_strlen(strs[i]) +1);
			}
			else
			{
				command = ft_strjoin(command, strs[i]);
			}

		}
		i ++;
	}

	// for last command
	if (t_minishell->commandlen == 0)
	{
		t_minishell->commands = ft_calloc(1, sizeof(char *));
		t_minishell->commands[0] = ft_calloc(ft_strlen(command) + 1, sizeof(char));
		ft_strlcpy(t_minishell->commands[0], command, ft_strlen(command)+1);
		t_minishell->commandlen = t_minishell->commandlen + 1;	

		free(command);
		command = NULL;
		printf("command:%s", t_minishell->commands[0]);
	}
	else
	{
		int old = 0;
		// int new = 0;

		t_minishell->commandlen = t_minishell->commandlen + 1;	
		commands = ft_calloc(t_minishell->commandlen+1, sizeof(char *));


		while (t_minishell->commandlen -1 > old)
		{
			commands[old] = ft_calloc(ft_strlen(t_minishell->commands[old])+1, sizeof(char));
			ft_strlcpy(commands[old], t_minishell->commands[old], ft_strlen(t_minishell->commands[old]) +1);

			// printf("new:%s\n", commands[old]);
			// printf("old:%s\n", t_minishell->commands[old]);

			free(t_minishell->commands[old]);
			old ++;
		}

		commands[old] = ft_calloc(ft_strlen(command) + 1, sizeof(char));
		ft_strlcpy(commands[old], command, ft_strlen(command)+1 );
		t_minishell->commands = commands;

		free(command);
		command = NULL;

	}

	int checker = 0;
	while (t_minishell->commandlen > checker)
	{
		// printf("commands:%s\n", t_minishell->commands[checker]);
		checker ++;
	}
	
	// substitute if there are any required ones
	subvariable(t_minishell);

	// not using now! because it will remove something like this
	// tr -d " "
	removeallwhitespaces(t_minishell);


	// temp running progra
	// runnin the first command. 
	// May need to fork beforehand

	printf("to run program for now\n\n\n");
	int processid = fork();

	if (processid == 0)
	{
		printf("child\n");
		program(t_minishell, 0);
	}
	else
	{
		printf("parent\n");
		waitpid(processid, NULL, 0);
	}


}