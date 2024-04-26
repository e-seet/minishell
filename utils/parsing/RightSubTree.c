#include "../utils.h"


void	leftSubTree3(struct AST_Node *rootnode, char **strs, int end)
{
	int 			i;
	struct AST_Node *curr;
	struct AST_Node *newNode;

	i = 0;
	curr = rootnode;

	while (end > i)
	{
		printf("curr str:%s\n", strs[i]);

		// This check after the top root. Assumes that the first is a pipe
		if
		(ft_strncmp(curr->type, PIPELINE, 8) == 0)
		{
			// printf("Curr pipe. Create node\n");
			
			newNode = ft_createNode(NULL, -1);
			printf("check the new node:%s\n", newNode->type);
			
			if (curr->left == NULL)
			{
				printf("At left\n");
				curr->left = newNode;
			}
			else
			{
				printf("At right\n");
				curr ->right = newNode;
				curr = curr->right;
			}
		}

				
		else if (ft_is_pipe(strs[i]) == 1)
		{
			printf("create pipes!\n");
			newNode = ft_createNode(strs, i);
			if (curr->left == NULL)
			{
				printf("At left\n");
				
				curr->left = newNode;
			}
			else
			{
				printf("At right\n");
				curr->right = newNode;
				curr = curr->right;
			}
		}



		// If it is >> or << | skip the next as i store the file target here
		else if (
			ft_is_heredoc_redirect(strs[i]) == 1
			|| ft_is_output_redirect(strs[i]) == 1
			|| ft_is_append_output_redirect(strs[i]) == 1
			|| ft_is_input_redirect(strs[i]) == 1
		)
		{
			printf("For Redirections\n");

			// If curr left not is not null.
			// Create a new node on the right with REDIRECT
			// Create a node with redirect n value on the left
			if ((curr ->left != NULL) && (ft_strncmp((curr->left)->type, REDIRECTIONS, 12) != 0))
			{
				printf("c1: Create empty redirect for you\n");
				printf("At right.\n");

				newNode = ft_createNode(NULL, -2); // Empty node Signifying Redirect
				curr->right = newNode;
				curr = curr->right;

				printf("At append left\n");

				// Create the node
				newNode = ft_createNode(strs, i);
				curr->left = newNode;
			}
			
			// If the curr left is not null and that node is redirect
			// Create a new node and append to right
			else if (curr->left != NULL && (ft_strncmp((curr->left)->type, REDIRECTIONS, 12)) == 0)
			{
				printf("C2\n");
				printf("Append right\n");

				newNode = ft_createNode(strs, i);
				curr->right = newNode;
			}
			// the following may cause issues with redirects
			else 
			{
				printf("C3: May have issues with this!!\n");

				if (curr->left == NULL)
				{
					printf("hook to left\n");
					newNode = ft_createNode(strs, i);
					curr->left = newNode;
					// curr = curr->left;
				}
				else
				{
					printf("hook to right\n");
					newNode = ft_createNode(NULL, -2); // Empty node signifying redirect
					curr->right = newNode;
					curr = curr->right;

					newNode = ft_createNode(strs, i);
					curr->left = newNode;
				}
			}
			i++;
			printf("\n");
		}
		// Anything else other than redirect: Command, Argument
		else
		{
				
				printf("C2: Create Argument | May have issues here?\n");
				if (curr->left == NULL)
				{
					printf("hook left\n");
					newNode = ft_createNode(strs, i);
					curr->left = newNode;
				}
				else
				{
					printf("hook right\n");
					// I may need to uncomment the code below.
					// newNode = ft_createNode(NULL, -1); // Empty node signifying Commands
					// curr->right = newNode;
					// curr = curr->right;

					newNode = ft_createNode(strs, i);
					curr->right = newNode;
				}
		}
				printf("\n");
			
		i ++;
	}

}

// // Handle the right halves which may include more than 1 pipes

// void	rightSubTree(struct AST_Node *rootnode, char **strs, int start, int end)
// {
// 	struct AST_Node *curr;
// 	struct AST_Node *newNode;
// 	int	i;

// 	i = start;
// 	curr = rootnode;

// 	while (end > i)
// 	{
// 		// printf("curr str:%s\n", strs[i]);

// 		// If it is >> or <<
// 		// skip the next as i store the file target here
// 		if (
// 			ft_is_heredoc_redirect(strs[i]) == 1
// 			|| ft_is_output_redirect(strs[i]) == 1
// 			|| ft_is_append_output_redirect(strs[i]) == 1
// 			|| ft_is_input_redirect(strs[i]) == 1
// 		)
// 		{
// 			printf("Redirect\n");
// 			newNode = ft_createNode(strs, i);
// 			// printf("The current node's Type before appending:%s", curr->type);
// 			if (curr->left != NULL)
// 			{
// 				curr-> right = newNode;
// 				curr = curr->right;
// 			}
// 			else 
// 			{
// 				curr->left = newNode;
// 				curr = curr->left;
// 			}
// 			i++; //Extra ++ to skip the next value as well.
// 			printf("\n");
// 		}
// 		else
// 		{
// 			// After the pipeline, left side should be command.
// 			if 
// 			(ft_strncmp(curr->type, PIPELINE, 8) == 0
// 			)
// 			{
// 				printf("Now Create a Command? May be wrong here and causing issues\n");
// 				newNode = ft_createNode(NULL, -1);
// 				printf("check the node:%s\n", newNode->type);
// 				curr->left = newNode;
// 				curr = curr->left;

// 				printf("\n");
// 			}
// 			// // This is command
// 			// else if 
// 			// (ft_strncmp(curr->type, COMMANDS, 8) == 0
// 			// )
// 			// {
// 			// 	// printf("Now a Command\n");
// 			// 	printf("check the node type:%s\n", newNode->type);

// 			// 	newNode = ft_createNode(strs, i);
// 			// 	curr -> left = newNode;
// 			// 	curr = curr->left;
// 			// }
// 			// If not pipeline, then we create arguments
// 			else
// 			{

// 				printf("Create Argument1! May be wrong here and causing issues\n");
// 				newNode = ft_createNode(strs, i);
// 				if (curr->left == NULL)
// 				{
// 					curr->left = newNode;
// 					curr = curr->left;
// 				}
// 				else
// 				{
// 					curr->right = newNode;
// 					curr = curr->right;
// 				}

// 			printf("\n");
// 			}
// 		}
// 		i ++;
// 	}

// }


// // void checkRightSubTree(struct AST_Node *rootnode)
// // {
// // 	struct AST_Node *temp;
// // 	struct AST_Node *temp_r;

// // 	temp = rootnode;
// // 	while (temp)
// // 	{
// // 		// printf("wtf\n");
// // 		printf("temp: %s\n", temp->type);

// // 		temp_r = temp->right;
// // 		if (temp_r)
// // 		{
// // 			temp_r = temp->right;
// // 			// printf("R Type:%s\n", temp_r->type);
// // 			printf("Seperator:%s\n", temp_r->seperator);
// // 			printf("target:%s\n\n", temp_r->target);
// // 		}
		
// // 		else if (ft_strncmp(temp->type, COMMANDS, 8) == 0)
// // 		{
// // 			printf("This is a command.\n\n");
// // 			// printf("%s \n", temp->token);	
// // 		}
// // 		else if (ft_strncmp(temp->type, REDIRECTIONS, 12) == 0)
// // 		{
// // 			// printf("This is redirect\n");
// // 			printf("Seperator%s \n", temp->seperator);
// // 			printf("Target:%s\n\n", temp->target);
// // 		}
// // 		else if (ft_strncmp(temp->type, PIPELINE, 8) == 0)
// // 		{
// // 			// printf("PIPELINE\n");
// // 			printf("Seperator:%s\n\n", temp->seperator);
// // 		}
// // 		else
// // 		{
// // 			// printf("Argument?\n");
// // 			printf("Token%s\n\n", temp->token);
// // 			// printf("Target:%s \n", temp->target);

// // 		}

// // 		if (temp->left != NULL)
// // 		{
// // 			temp = temp->left;
// // 		}
// // 		else if (temp->right != NULL)
// // 		{
// // 			temp = temp->right;
// // 		}
// // 		else
// // 			break;

// // 	}

// // }

