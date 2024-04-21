	#include "../utils.h"

// Syntax analysis / Parsing: scanning the stream of tokens according to a specific
// grammar and then deciding what to do with them 
// (e.g. generating an AST — Abstract Syntax Tree).

// Setup AST tree here.
// similiaryly help to get back the command from the AST tree.

//https://stackoverflow.com/questions/52666511/create-an-ast-from-bash-in-c
// https://stackoverflow.com/questions/59602615/execute-pipes-recursively-in-abstract-syntax-tree

void parser(char *str, char *envp[])
{
	printf("the str%s", str);
	printf("%p", envp[0]);

	// int	i;
	// int singlequote;
	// int doublequote;

	// i = 0;
	// singlequote = 0;
	// doublequote = 0;

	// // TreeNode
	// while (str[i])
	// {

	// 	i++;
	// }
}
