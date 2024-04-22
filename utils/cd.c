#include "utils.h"

void changedirectory(char *str, struct s_minishell *t_minishell)
{
	printf("str:%s", str);

	// back to home directory
	// "cd "
	// The home directory can be retrieved by: echo $HOME
	if (ft_strncmp(str, "cd ", ft_strlen("cd ") == 0))
	{
		// to do
	}
	else if (ft_strncmp(str, "cd ~", ft_strlen("cd ~") == 0))
	{
		// To do
		// tilde as a shortcut to home directory
		// cd ~/Document
	}
	else if (ft_strncmp(str, "cd -", ft_strlen("cd -")) == 0)
	{
		// back to the previous directory that i was in
		// cd -
		if (chdir(t_minishell->prevpwd) != 0)
		{
			printf("Error navigating to:%s", t_minishell->prevpwd);
			perror("chdir: change directory error\n");
		}
		else
		{
			t_minishell->prevpwd = t_minishell->currpwd;
			
			char *currpwd;
			currpwd = ft_calloc(1024, sizeof(char));
			currpwd = getcwd(currpwd, 1024);
			t_minishell->currpwd = currpwd;
		}			
	}
	else
	{
		printf("else\n");
		// go up 1 level
		// "cd .."
		char **temp;
		char *dir;

		temp = ft_split(str, ' ');
		// printf("temp[1]:%s\n\n", temp[1]);
		dir = ft_calloc(ft_strlen(temp[1]) + 1, sizeof(char));
		
		ft_strlcpy(dir, temp[1], ft_strlen(temp[1]));

		printf("cd %s\n", dir);
		
		if (chdir(dir) != 0)
		{
			printf("Error navigating to:%s", dir);
			perror("chdir: change directory error\n");
		}
		else
		{
			t_minishell->prevpwd = t_minishell->currpwd;
			
			char *currpwd;
			currpwd = ft_calloc(1024, sizeof(char));
			currpwd = getcwd(currpwd, 1024);
			t_minishell->currpwd = currpwd;
		}
		// Works
		// "cd ." // does nothing .. so ignore

		// change to absolute / relative directory
		// more exmaples
		// Relative Paths
		// cd ../
		// cd ../../
		// cd ../42
		// remain in same directory
		// cd ./ 
		// cd ./anotherfile.txt
		// cd /Users/eddieseet/MDesktop/Curr/minishell/utils
		// cd /Users/eddieseet/MDesktop
		// cd /bin
		// cd /etc/hosts



		// not sure if required.
		// export CDPATH=.:~/Documents
		// cd directory_name
	}

}