#include "../utils.h"

// Syntax analysis / Parsing: scanning the stream of tokens according to a specific
// grammar and then deciding what to do with them 
// (e.g. generating an AST — Abstract Syntax Tree).

// Setup AST tree here.
// similiaryly help to get back the command from the AST tree.

//https://stackoverflow.com/questions/52666511/create-an-ast-from-bash-in-c
// sample AST to be created
//                       __ PIPELINE__
//                  ___/              \____
//                 /                       \
//         COMMAND                    __ PIPELINE _
//       /        \                  /             \
// ARGUMENTS   REDIRECTIONS      COMMAND         _ COMMAND __
//     |          |     |           |           /            \
//    cat        <<     >       ARGUMENTS    ARGUMENTS   REDIRECTIONS
//                |     |         |   |      |   |   |        |
//              "..."  file      wc  -c      tr  -d " "       >
//                                                            |
//                                                          file2
// cat << EOF > file | wc -c | tr -d " " > file2

void parser(char **strs)
{

	// check for the number of pipes and redirect
	int	i;
	int	pipecount;
	int	firstpipe;
	int	redirectcount;

	i = 0;
	pipecount = 0;
	firstpipe = 0;
	redirectcount = 0;
	while (strs[i])
	{
		if (ft_is_pipe(strs[i]) == 1)
		{
			if (firstpipe == 0)
			{
				firstpipe = i;
			}
			pipecount ++;
		}
		else if (
			ft_is_output_redirect(strs[i]) == 1
			|| ft_is_input_redirect(strs[i]) == 1
			|| ft_is_append_output_redirect(strs[i]) == 1
			|| ft_is_heredoc_redirect(strs[i]) == 1
	)
		{
			redirectcount ++;
		}
		i++;
	}
	printf("\npipe counts:%d\n", pipecount);
	printf("first pipe is at:%d\n", firstpipe);
	printf("redirect counts:%d\n\n\n\n\n\n\n\n", redirectcount);


	struct AST_Node *rootnode; // this will be the root node.

	// Now i want to build based off my pipe first
	if (pipecount != 0)
	{
		// create Root node first [Based off the first pipe token we found]
		rootnode = ft_createNode(strs, firstpipe);

		// left side is 0 to firstpipe-1
		leftSubTree(rootnode, strs, firstpipe);
		printf("end of left subtree\n\n\n\n\n\n\n");


		// checkLeftSubTree(rootnode);
		// inorderTraversal_L(rootnode);
		

		// Check if there is any redirects inside [settled]
		// otherwise is just arguments. [settled]
		// printf("\n\n\n");
		// right side is from firstpipe + 1 to i
		// printf("Right sub tree\n");
		// rightSubTree(rootnode, strs, firstpipe+1, i);

		// let's see what happen if i use the same algo for right half
		leftSubTree2(rootnode, strs, firstpipe+1, i);
		printf("checking traversal\n\n\n\n\n\n\n");
		inorderTraversal_L(rootnode);
		// checkRightSubTree(rootnode);

	}
	else
	{
	}
}
