#include "../utils.h"

// Lexical analysis is the first phase of compiling a program, where the source code is scanned to identify these tokens.
// The scanner (or lexer) reads the characters of the source code and groups them into tokens based on the language's syntax rules.
// These tokens are then passed on to the next phase of the compiler for further processing.
// For example, in the C statement int x = 10;, the tokens are int, x, =, and 10, each representing a different kind of lexical 
// element in the C language.

// how the source code is divided into tokens. 
// Tokens are the smallest individual units of a program, 
// such as keywords, identifiers, literals, and operators.

// Check for sepeartor, if found. Add to list.
// > : ft_is_output_redirect
// >> : ft_is_append_output
// <  :ft_is_input_redirect
// << ft_is_heredoc
// || ft_is_conditional_or
// | ft_is_pipe
// && ft_is_double_ampersand
// ( ft_is_bracket1
// ) ft_is_bracket2

int	ft_is_output_redirect(char *str)
{
	int	i;
	
	i = 0;
	if (str[i] == '>')
	{
		return (1);
	}
	return (0);
}

int	ft_is_append_output(char *str)
{
	int	i;
	
	i = 0;
	if (str[i] == '>' && str[i+1] == '>')
	{
		return (1);
	}
	return (0);
}

int	ft_is_input_redirect(char *str)
{
	int	i;
	
	i = 0;
	if (str[i] == '<')
	{
		return (1);
	}
	return (0);
}

int	ft_is_heredoc(char *str)
{
	int	i;
	
	i = 0;
	if (str[i] == '<' && str[i+1] == '<')
	{
		return (1);
	}
	return (0);
}


int	ft_is_conditional_or(char *str)
{
	int	i;
	
	i = 0;
	if (str[i] == '|' && str[i+1] == '|')
	{
		return (1);
	}
	return (0);
}


int	ft_is_pipe(char *str)
{
	int	i;
	
	i = 0;
	if (str[i] == '|')
	{
		return (1);
	}
	return (0);
}

int	ft_is_double_ampersand(char *str)
{
	int	i;
	
	i = 0;
	if (str[i] == '&' && str[i + 1] == '&' )
	{
		return (1);
	}
	return (0);
}


// (
int	ft_is_bracket1(char *str)
{
	int	i;
	
	i = 0;
	if (str[i] == '(')
	{
		return (1);
	}
	return (0);
}

// )
int	ft_is_bracket2(char *str)
{
	int	i;
	
	i = 0;
	if (str[i] == ')')
	{
		return (1);
	}
	return (0);
}

char	**ft_breakup_str(char *str)
{
	char	**strs;
	int		i;
	int		pos;
	int		num;

	i = 0;
	num = 0;
	pos = 0;
	// iterate through the str and find number of brokendown str
	while (str[i] != '\0')
	{
		if
		(
			(ft_is_append_output(&str[i]) == 1)
			|| (ft_is_heredoc(&str[i]) == 1) 
			|| (ft_is_conditional_or(&str[i]) == 1)
			|| (ft_is_double_ampersand(&str[i]) == 1)
		)
		{
			i = i + 2;
			num++;
		}
		else if (
			(ft_is_output_redirect(&str[i]) == 1)
			|| (ft_is_input_redirect(&str[i]) == 1)
			|| (ft_is_pipe(&str[i]) == 1)
			|| (ft_is_bracket1(&str[i]) == 1)
			|| (ft_is_bracket2(&str[i]) == 1)
			|| (ft_is_double_ampersand(&str[i]) == 1)
		)
		{
			num++;
			i ++;
		}
		else
			i++;
	}

	// asdasdas + sep + asdadas + sep + sadasd 
	if (num > 1)
	{
		printf("number of strs to be calloc:%d\n", (num - 1) * 2);
		strs = ft_calloc((num - 1) * 2, sizeof(char *));
	}
	else
		strs = ft_calloc(num, sizeof(char *));


	// copy all of the strs
	int backupnum = (num - 1) * 2;
 	i = 0;
	num = 0;
	while (str[i] != '\0')
	{
		if
		(
			(ft_is_append_output(&str[i]) == 1)
			|| (ft_is_heredoc(&str[i]) == 1) 
			|| (ft_is_conditional_or(&str[i]) == 1)
			|| (ft_is_double_ampersand(&str[i]) == 1)
		)
		{
			// copying the word / str
			strs[num] = ft_calloc(i-pos, sizeof(char));
			ft_strlcpy(strs[num], &str[pos], i-pos+1);
			printf("what have been copied for str: %s\n", strs[num]);
			num ++;
			pos = i;
			i = i + 2;

			// copying the seperator
			strs[num] = ft_calloc(i-pos, sizeof(char));
			ft_strlcpy(strs[num], &str[pos], i-pos+1);
			printf("what have been copied for token: %s\n", strs[num]);
			num ++;
			pos = i;

		}
		else if (
			(ft_is_output_redirect(&str[i]) == 1)
			|| (ft_is_input_redirect(&str[i]) == 1)
			|| (ft_is_pipe(&str[i]) == 1)
			|| (ft_is_bracket1(&str[i]) == 1)
			|| (ft_is_bracket2(&str[i]) == 1)
			|| (ft_is_double_ampersand(&str[i]) == 1)
		)
		{
			strs[num] = ft_calloc(i-pos, sizeof(char));
			ft_strlcpy(strs[num], &str[pos], i-pos+1);
			printf("what have been copied for str: %s\n", strs[num]);
			num ++;
			pos = i;
			i ++;
			strs[num] = ft_calloc(i-pos, sizeof(char));
			ft_strlcpy(strs[num], &str[pos], i-pos+1);
			printf("what have been copied for token: %s\n", strs[num]);
			num ++;
			pos = i;
		}
		else
			i++;
	}

	// the last part. I probably need to check and ensure 
	strs[num] = ft_calloc(i-pos, sizeof(char));
	ft_strlcpy(strs[num], &str[pos], i-pos);

	printf("formula num:%d, actual num:%d\n",  backupnum, num);

	return strs;
	// return NULL;
}

// Lexing: just split the input into tokens as you please and see useful for the parsing phase.
void lexical(char *str, char *envp[])
{
	printf("temp %p\n\n", envp[0]);

	char **strs;

	// parser(str, envp);	
	strs = ft_breakup_str(str);
	
	int i;
	i = 0;

	while (strs[i])
	{
		printf("number:%d str:%s\n", i, strs[i]);
		i++;
	}

	// if (ft_strncmp(str, "echo", 4) == 0)
	// {
	// 	printf("echo stuff\n");
	// }
	// else if (ft_strncmp(str, "exit", 4) == 0)
	// {
	// 	printf("exit now!\n");
	// }
	// else if (ft_strncmp(str, "env", 3) == 0)
	// {
	// 	printf("to print out env or stuff");
	// }
	// else if (ft_strncmp(str, "export", 6) == 0)
	// {
	// 	printf("export\n");
	// }
	// else if (ft_strncmp(str, "unset", 5) == 0)
	// {
	// 	printf("unset env\n");

	// }
	// else if (ft_strncmp(str, "pwd", 3) == 0)
	// {
	// 	printf("get pwd\n");

	// }
	// else if (ft_strncmp(str, "cd", 2) == 0)
	// {
	// 	printf("cd\n");
	// }

	// // the rest are not built in. so we should handle it
	// else
	// {
	// 	// other things
	// }

}