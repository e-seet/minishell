#ifndef STRUCT_H
# define STRUCT_H

// Define a struct for a binary tree node
struct TreeNode {
    char *data;
    struct TreeNode* left;
    struct TreeNode* right;
};

struct s_minishell
{
	char	**paths;
	char	*path;
	char	**envp;
};


#endif
