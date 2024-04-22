#include "../utils.h"

struct AST_Node *ft_createNode(char **strs, int num)
{

	struct AST_Node *node = ft_calloc(1, sizeof(struct AST_Node));
	

	// Create a command node	
	if ((strs == NULL) && (num == -1))
	{
		node->type = COMMANDS;
		node->left = NULL;
		node->right = NULL;
	}
	else if ( (strs == NULL) && (num == -2))
	{
		node->type = REDIRECTIONS;
		node->left = NULL;
		node->right = NULL;
	}
	// PIPELINE
	else if (ft_is_pipe(strs[num]) == 1)
	{
		node->type = PIPELINE;
		node->seperator = strs[num];
		node->left = NULL;
		node->right = NULL;
	}
	// REDIRECTIONS
	else if (
		ft_is_append_output_redirect(strs[num]) == 1
		|| ft_is_heredoc_redirect(strs[num]) == 1
		|| ft_is_input_redirect(strs[num]) == 1
		|| ft_is_output_redirect(strs[num]) == 1
	)
	{
		node->type = REDIRECTIONS;
		node->seperator = strs[num];
		node->target = strs[num + 1];
		node->left = NULL;
		node->right = NULL;
	}
	// Argument
	else
	{
		node->type = ARGUMENTS;
		node->token = strs[num];
		node->left = NULL;
		node->right = NULL;
	}
	return node;
}
