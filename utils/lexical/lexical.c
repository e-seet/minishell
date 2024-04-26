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
// <  :ft_is_input_redirect
// >> : ft_is_append_output_redirect
// << ft_is_heredoc_redirect
// || ft_is_conditional_or
// | ft_is_pipe
// && ft_is_double_ampersand
// ( ft_is_bracket1
// ) ft_is_bracket2

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
			(ft_is_append_output_redirect(&str[i]) == 1)
			|| (ft_is_heredoc_redirect(&str[i]) == 1) 
			// || (ft_is_conditional_or(&str[i]) == 1)
			// || (ft_is_double_ampersand(&str[i]) == 1)
		)
		{
			i = i + 2;
			num++;
			num++;
		}
		else if (
			(ft_is_output_redirect(&str[i]) == 1)
			|| (ft_is_input_redirect(&str[i]) == 1)
			|| (ft_is_pipe(&str[i]) == 1)
			|| (ft_is_bracket1(&str[i]) == 1)
			|| (ft_is_bracket2(&str[i]) == 1)
			// || (ft_is_double_ampersand(&str[i]) == 1)
		)
		{
			num++;
			num++;
			i ++;
		}
		// the num for below may need to change
		else if (
			(ft_is_bracket1(&str[i]) == 1)
			|| (ft_is_bracket2(&str[i]) == 1)
		)
		{
			num++;
			num++;
			i ++;
		}
		else
			i++;
	}

	// asdasdas + sep + asdadas + sep + sadasd 
	if (num > 1)
	{
		printf("number of strs to be calloc:%d\n", num+1);
		strs = ft_calloc(num+1, sizeof(char *));
	}
	else
		strs = ft_calloc(num+1, sizeof(char *));


	// copy all of the strs
	int backupnum;

	if (num != 0)
		backupnum = num+1;
 	else
		backupnum = 0+1;
	i = 0;
	num = 0;
	while (str[i] != '\0')
	{
		// >> <<
		if
		(
			(ft_is_append_output_redirect(&str[i]) == 1)
			|| (ft_is_heredoc_redirect(&str[i]) == 1) 
			// || (ft_is_conditional_or(&str[i]) == 1)
			// || (ft_is_double_ampersand(&str[i]) == 1)
		)
		{
			// printf("double!\n%s\n", &str[i]);
			// copying the word / str
			strs[num] = ft_calloc(i-pos+1, sizeof(char));
			ft_strlcpy(strs[num], &str[pos], i-pos+1);
			// printf("what have been copied for str: %s\n", strs[num]);
			num ++;
			pos = i;
			i = i + 2;

			// copying the seperator
			strs[num] = ft_calloc(i-pos+1, sizeof(char));
			ft_strlcpy(strs[num], &str[pos], i-pos+1);
			// printf("what have been copied for token: %s\n", strs[num]);
			num ++;
			pos = i;

		}
		// |, >, <, (, )
		else if (
			(ft_is_output_redirect(&str[i]) == 1)
			|| (ft_is_input_redirect(&str[i]) == 1)
			|| (ft_is_pipe(&str[i]) == 1)
			|| (ft_is_bracket1(&str[i]) == 1)
			|| (ft_is_bracket2(&str[i]) == 1)
			// || (ft_is_double_ampersand(&str[i]) == 1)
		)
		{
			// printf("single!%c\n%s\n",str[i], &str[i]);
			
			strs[num] = ft_calloc(i-pos+1, sizeof(char));
			ft_strlcpy(strs[num], &str[pos], i-pos+1);
			// printf("what have been copied for str: %s\n", strs[num]);
			num ++;
			pos = i;
			i ++;
			strs[num] = ft_calloc(i-pos+1, sizeof(char));
			ft_strlcpy(strs[num], &str[pos], i-pos+1);
			// printf("what have been copied for token: %s\n", strs[num]);
			num ++;
			pos = i;
		}
		else
			i++;
	}

	// the last part. I probably need to check and ensure 
	strs[num] = ft_calloc(i-pos, sizeof(char));
	ft_strlcpy(strs[num], &str[pos], i-pos);

	printf("Allocated spaces:%d, actual spaces:%d\n",  backupnum, num);

	return strs;
	// return NULL;
}

// Lexing: just split the input into tokens as you please and see useful for the parsing phase.
void lexical(char *str, struct s_minishell *t_minishell)
{
	char **strs;

	// parser(str, envp);	
	strs = ft_breakup_str(str);
	
	int i;
	i = 0;
	printf("print this if you want to know how it is seperated\n");
	while (strs[i])
	{
		printf("number:%d str:%s\n", i, strs[i]);
		i++;
	}

	parser(strs, t_minishell); // praser
	cleanupstring(t_minishell); //clean up string but sub first
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
