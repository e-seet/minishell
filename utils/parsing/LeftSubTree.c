#include "../utils.h"

// Note: as this is the first pipe
// threfore there should only be redirects that will cause a right subtree.
// So we need to handle that by checking for the 4 redirects
// Note: the strs are seperated by seperators (">", ">>", "<", "<<", "(", ")", "&&", "|", "||")
// redirects: ">" ">>" "<<" "<"
//"(", ")",
//  "&&", "||" Not required

void	leftSubTree(struct AST_Node *rootnode, char **strs, int end)
{
	int 			i;
	struct AST_Node *curr;
	struct AST_Node *newNode;

	i = 0;
	curr = rootnode;

	while (end > i)
	{
		// printf("curr str:%s\n", strs[i]);
		// If it is >> or <<
		// skip the next as i store the file target here
		if (
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
				newNode = ft_createNode(NULL, -2); // Empty node Signifying Redirect
				curr->right = newNode;
				curr = curr->right;

				// Create the node
				newNode = ft_createNode(strs, i);
				curr->left = newNode;
			}
			
			// If the curr left is not null and that node is redirect
			// Create a new node and append to right
			else if (curr->left != NULL && (ft_strncmp((curr->left)->type, REDIRECTIONS, 12)) == 0)
			{
				printf("C2\n");
				newNode = ft_createNode(strs, i);
				curr->right = newNode;
			}
			// the following may cause issues with redirects
			else 
			{
				printf("C3: May have issues with this\n");

				if (curr->left == NULL)
				{
					newNode = ft_createNode(strs, i);
					curr->left = newNode;
					// curr = curr->left;
				}
				else
				{
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
		// Anything else other than redirect: Command, Argument, Pipeline
		else
		{
			printf("else!\n");
			// This check after the real root.
			if
			(ft_strncmp(curr->type, PIPELINE, 8) == 0 && i == 0)
			{
				printf("C1: Now Create a Command\n");
				newNode = ft_createNode(NULL, -1); // Empty node signifying Commands
				curr -> left = newNode;
				curr = curr ->left;

				printf("Follow up by whatever it is\n");
				newNode = ft_createNode(strs, i);
				printf("Check the type:%s\n", newNode->type);
				curr -> left = newNode;
				// printf("checked my connection worked %s\n\n", curr->left->type);
			}

			else
			{
				printf("C2: Create Argument | May have issues here\n");
				if (curr->left == NULL)
				{
					newNode = ft_createNode(strs, i);
					curr->left = newNode;
				}
				else
				{
					// I may need to uncomment the code below.
					// newNode = ft_createNode(NULL, -1); // Empty node signifying Commands
					// curr->right = newNode;
					// curr = curr->right;

					newNode = ft_createNode(strs, i);
					curr->right = newNode;
				}
				printf("\n");
			}
			
		}
		i ++;
	}

}


void inorderTraversal_L(struct AST_Node* root)
{
    if (root != NULL)
	{
        inorderTraversal_L(root->left);
        // printf("%d ", root->data);

		if (ft_strncmp(root->type, COMMANDS, 8) == 0)
		{
			printf("This is a command.\n\n");

		}
		else if (ft_strncmp(root->type, REDIRECTIONS, 12) == 0)
		{
			printf("This is redirect\n");
			if (root->seperator != NULL && root->target != NULL)
			{
				printf("Not Null!\n");
				printf("What kind of redirect? %s \n", root->seperator);
				printf("Target:%s\n\n", root->target);
			}
		}
		else if (ft_strncmp(root->type, PIPELINE, 8) == 0)
		{
			printf("PIPELINE\n");
			printf("Show pipe:%s\n\n", root->seperator);
		}
		else
		{
			printf("Argument\n");
			printf("Token: %s\n\n", root->token);
		}

        inorderTraversal_L(root->right);
    }
}

//check left sub tree
// void checkLeftSubTree(struct AST_Node *rootnode)
// {
// 	struct AST_Node *temp; // this will be the root node.
// 	struct AST_Node *temp_r; // this will be the root node.

// 	temp = rootnode;
// 	while (temp)
// 	{
// 		// printf("wtf\n");
// 		printf("temp: %s\n", temp->type);

// 		temp_r = temp->right;
// 		if (temp_r)
// 		{
// 			temp_r = temp->right;
// 			// printf("R Type:%s\n", temp_r->type);
// 			printf("Seperator:%s\n", temp_r->seperator);
// 			printf("target:%s\n\n", temp_r->target);
// 		}
		
// 		else if (ft_strncmp(temp->type, COMMANDS, 8) == 0)
// 		{
// 			printf("This is a command.\n\n");
// 		}
// 		else if (ft_strncmp(temp->type, REDIRECTIONS, 12) == 0)
// 		{
// 			printf("This is redirect\n");
// 			printf("What kind of redirect? %s \n", temp->seperator);
// 			printf("Target:%s\n\n", temp->target);
// 		}
// 		else if (ft_strncmp(temp->type, PIPELINE, 8) == 0)
// 		{
// 			printf("PIPELINE\n");
// 			printf("Show pipe:%s\n\n", temp->seperator);
// 		}
// 		else
// 		{
// 			printf("Argument\n");
// 			printf("Token: %s\n\n", temp->token);
// 		}

// 		if (temp->left != NULL)
// 		{
// 			temp = temp->left;
// 		}
// 		else if (temp->right != NULL)
// 		{
// 			temp = temp->right;
// 		}
// 		else
// 			break;
// 	}
// }





void	leftSubTree2(struct AST_Node *rootnode, char **strs, int end)
{
	int 			i;
	struct AST_Node *curr;
	struct AST_Node *newNode;

	i = 0;
	curr = rootnode;

	while (end > i)
	{
		// printf("curr str:%s\n", strs[i]);


		if (curr->left == NULL)
		{
			newNode = ft_createNode(NULL, -1);
			curr->left = newNode;
		}

		// If it is >> or <<
		// skip the next as i store the file target here
		else if (
			ft_is_heredoc_redirect(strs[i]) == 1
			|| ft_is_output_redirect(strs[i]) == 1
			|| ft_is_append_output_redirect(strs[i]) == 1
			|| ft_is_input_redirect(strs[i]) == 1
		)
		{
			printf("Redirect\n");

			// If curr left not is not null.
			// Create a new node on the right with REDIRECT
			// Create a node with redirect n value on the left
			if ((curr ->left != NULL) && (ft_strncmp((curr->left)->type, REDIRECTIONS, 12) != 0))
			{
				printf("c1: Create empty redirect for you\n");
				
				// the issue is here: For extra line after im done
				newNode = ft_createNode(NULL, -2);
				curr -> right = newNode;
				curr = curr -> right;

				newNode = ft_createNode(strs, i);
				curr -> left = newNode;
			}
			// If the curr left is not null and that node is redirect
			// Create a new node and append to right
			else if (curr->left != NULL && (ft_strncmp((curr->left)->type, REDIRECTIONS, 12)) == 0)
			{
				printf("C2\n");
				newNode = ft_createNode(strs, i);
				curr->right = newNode;
			}
			// the following may cause issues with redirects
			else 
			{
				printf("C3\n");
				newNode = ft_createNode(strs, i);
				curr->left = newNode;
				curr = curr->left;
			}
			i++;
			printf("\n");
		}
		else
		{
			// After the pipeline, left side should be command.
			if
			(ft_strncmp(curr->type, PIPELINE, 8) == 0)
			{
				// printf("Now Create a Command\n");
				newNode = ft_createNode(NULL, -1);
				curr -> right = newNode;
				curr = curr ->right;

				printf("Follow up by whatever it is\n");
				newNode = ft_createNode(strs, i);
				printf("Check the type:%s\n", newNode->type);
				curr -> left = newNode;
				// printf("checked my connection worked %s\n\n", curr->left->type);
			}
			else
			{
				printf("Create Argument2\n");
				if (curr->left == NULL)
				{
					newNode = ft_createNode(strs, i);
					curr->left = newNode;
				}
				else 
				{
					// here i should create another buffer
					newNode = ft_createNode(NULL, -1);
					curr -> right = newNode;
					curr = curr ->right;

					newNode = ft_createNode(strs, i);
					curr->left = newNode;

				}
				printf("\n");
			}
			
		}
		i ++;
	}

}
