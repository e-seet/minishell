#include "utils/utils.h"

//check if the last character is a \n and subtract accordingly
// go to the position before \0 and check if it is a \n
int	linechecker(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	if (str[i - 1] == '\n')
		return (1);
	else
		return (0);
}


// starts the program and get the input from user.
int	checkforexit(char *envp[])
{
	char	*str;
	// char	*paths;
	struct s_minishell *t_minishell;

	t_minishell = ft_calloc(1, sizeof(t_minishell));
	
	//setup 
	setupstruct(t_minishell, envp);


	printf("\033[1;31m\n");
	str = NULL;
	while (1)
	{
		write(1, "minishell> ", 11);
		str = get_next_line(0);
		if (str == NULL
			|| ((ft_strncmp(str, "exit", ft_strlen(
							"exit")) == 0) && (ft_strlen(str)
					- linechecker(str)) == ft_strlen("exit")))
					{
						printf("break\n");
						break ;
					}
		else
		{

			
			// 1. lexical
			lexical(str);

			//  2. do parsing and all you want to do here.
			// Create fork and create the program

			// 3 expand before running the program.
			// replace variable [$...] to whatever it is?

		}
		free(str);
		str = NULL;
	}
	if (str != NULL)
		free(str);
	return (0);
}

/*
1. i will also need some kind of mechanism to expand env
eg: $abc = /root/eseet/...
i need to be able to expand $abc

So what do i really need? to handle?
""
''
$

2. Handle extra quotations and all when it is just a single string.

3.remove quotes from words / things not interfered with seperators

4. Bonus: Handle *
*/

int main(int argc, char *argv[], char *envp[])
{
	// printf("argv:%d %p\n",argc, argv[0]);
	if (argc == 1)
	{
		if (ft_strncmp("./minishell", argv[0], 11) == 0)
		{
			checkforexit(envp);
		}
	}
	return (0);
}