#ifndef STRUCT_H
# define STRUCT_H

#define PIPELINE "PIPELINE"
#define COMMANDS "COMMANDS"
#define REDIRECTIONS "REDIRECTIONS"
#define ARGUMENTS "ARGUMENTS"

// Command:
// type = COMMAND

// Redirection
// type = REDIRECTION
// seperator = 
// target =

// ARGUMENT
// tokens

// separators?

// Define a struct for a binary tree node
struct AST_Node
{
	char	*type; // To store the type: Command, Redirection, Arguments

	//Either
	// for seperator: The 9 of them. Probably should not store
	char	*seperator;
	
	//or
	// for Arguments
	char	*token;

	// Or
	// for Arguments: May not be used. since i haven't seperated it yet
	char	**tokens;

	//or 

	// For Redirect in / out target
	char	*target ;

	// original str;
	char *strs;

	struct AST_Node* left;
    struct AST_Node* right;
};


struct s_minishell
{
	char	**paths;
	char	*path;
	char	**envp;

	char	*prevpwd;
	char	*currpwd;

};


#endif
