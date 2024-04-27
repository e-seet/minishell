#include "utils.h"


char *inorderTraversal(struct AST_Node* root, char *str1, struct s_minishell *t_minishell, int temp)
{
	char *str2;
	
	str2 = NULL;

    if (root != NULL)
	{
        temp = temp + 1;
		printf("temp:%d\n", temp);
		printf("type:%s\n", root->type);
		str1 = inorderTraversal(root->left, str1, t_minishell, temp);

		if (ft_strncmp(root->type, COMMANDS, 8) == 0)
		{
			// printf("This is a command.\n\n");
		}
		else if (ft_strncmp(root->type, REDIRECTIONS, 12) == 0)
		{
			// printf("This is redirect\n");
			if (root->seperator != NULL && root->target != NULL)
			{
				printf("redirect? %s \n", root->seperator);
				printf("Target:%s\n", root->target);


				if (root->seperator != NULL)
				{

					if (str1 == NULL)
						str1 = root->seperator;
					else if (str2 == NULL)
					{
						str2 = root->seperator;
						str1 = ft_strjoin(str1, str2);
						str2 = NULL;
					}
					else
					{
						str1 = ft_strjoin(str1, str2);
						str2 = NULL;
						str2 = root->seperator;
						str1 = ft_strjoin(str1, str2);
						str2 = NULL;
					}
				}

				if (root->target != NULL)
				{
					if (str1 == NULL)
						str1 = root->target;
					else if (str2 == NULL)
					{
						str2 = root->target;
						str1 = ft_strjoin(str1, str2);
						str2 = NULL;
					}
					else
					{
						str1 = ft_strjoin(str1, str2);
						str2 = NULL;
						str2 = root->target;
						str1 = ft_strjoin(str1, str2);
						str2 = NULL;
					}
				}

			}
		}
		else if (ft_strncmp(root->type, PIPELINE, 8) == 0)
		{
			// printf("PIPELINE\n");
			if (root->seperator != NULL)
			{

				// if (str1 != NULL)
				// 	printf("str1:%s\n\n", str1);
				// else
				// 	printf("str1 is empty\n");
				printf("Show pipe:%s\n\n", root->seperator);

				if ( root->seperator != NULL)
				{
					if (str1 == NULL)
						str1 =  root->seperator;
					else if (str2 == NULL)
					{
						str2 =  root->seperator;
						str1 = ft_strjoin(str1, str2);
						str2 = NULL;
					}
					else
					{
						str1 = ft_strjoin(str1, str2);
						str2 = NULL;
						str2 =  root->seperator;
						str1 = ft_strjoin(str1, str2);
						str2 = NULL;
					}
				}

				if (t_minishell->commandlen == 0)
				{
					// int temp;
					// temp = 0;

					t_minishell->commandlen = t_minishell->commandlen + 2;
					t_minishell->commands = ft_calloc(t_minishell->commandlen, sizeof(char *));

					//what im trying to do here is to split

				}


				// i need to store the pipe
				// need to allocate space.
			}
		}
		else
		{
			// printf("Argument\n");
			printf("Token here %d: %s\n",temp ,root->token);
			if (root->token != NULL)
			{
				if (str1 == NULL)
				{
					str1 = root->token;
				}
				else if (str2 == NULL)
				{
					str2 = root->token;
					str1 = ft_strjoin(str1, str2);
					str2 = NULL;
				}
				else 
				{
					str1 = ft_strjoin(str1, str2);
					str2 = NULL;
					str2 = root->token;
					str1 = ft_strjoin(str1, str2);
					str2 = NULL;
				}
			}
		}
 
		str1 = inorderTraversal(root->right, str1, t_minishell, temp);
		
    }
	return str1;
}


// char *inorderTraversal(struct AST_Node* root, char *str1, struct s_minishell *t_minishell, int temp)
// {
// 	char *str2;
	
// 	str2 = NULL;

//     if (root != NULL)
// 	{
//         temp = temp + 1;
// 		printf("temp:%d\n", temp);
// 		printf("type:%s\n", root->type);
// 		str1 = inorderTraversal(root->left, str1, t_minishell, temp);

// 		if (ft_strncmp(root->type, COMMANDS, 8) == 0)
// 		{
// 			// printf("This is a command.\n\n");
// 		}
// 		else if (ft_strncmp(root->type, REDIRECTIONS, 12) == 0)
// 		{
// 			// printf("This is redirect\n");
// 			if (root->seperator != NULL && root->target != NULL)
// 			{
// 				// test
// 				return str1;

// 				printf("redirect? %s \n", root->seperator);
// 				printf("Target:%s\n", root->target);

// 				if (root->seperator != NULL)
// 				{

// 					if (str1 == NULL)
// 						str1 = root->seperator;
// 					else if (str2 == NULL)
// 					{
// 						str2 = root->seperator;
// 						str1 = ft_strjoin(str1, str2);
// 						str2 = NULL;
// 					}
// 					else
// 					{
// 						str1 = ft_strjoin(str1, str2);
// 						str2 = NULL;
// 						str2 = root->seperator;
// 						str1 = ft_strjoin(str1, str2);
// 						str2 = NULL;
// 					}
// 				}

// 				if (root->target != NULL)
// 				{
// 					if (str1 == NULL)
// 						str1 = root->target;
// 					else if (str2 == NULL)
// 					{
// 						str2 = root->target;
// 						str1 = ft_strjoin(str1, str2);
// 						str2 = NULL;
// 					}
// 					else
// 					{
// 						str1 = ft_strjoin(str1, str2);
// 						str2 = NULL;
// 						str2 = root->target;
// 						str1 = ft_strjoin(str1, str2);
// 						str2 = NULL;
// 					}
// 				}


// 			}
// 		}
// 		else if (ft_strncmp(root->type, PIPELINE, 8) == 0)
// 		{
// 			// printf("PIPELINE\n");
// 			if (root->seperator != NULL)
// 			{

// 				// if (str1 != NULL)
// 				// 	printf("str1:%s\n\n", str1);
// 				// else
// 				// 	printf("str1 is empty\n");
// 				printf("Show pipe:%s\n\n", root->seperator);

// 				if (root->seperator != NULL)
// 				{
// 					//test
// 					// if i put here, all no pipe
// 					// return str1;

// 					if (str1 == NULL)
// 						str1 =  root->seperator;
// 					else if (str2 == NULL)
// 					{
// 						str2 =  root->seperator;
// 						str1 = ft_strjoin(str1, str2);
// 						str2 = NULL;
// 					}
// 					else
// 					{
// 						str1 = ft_strjoin(str1, str2);
// 						str2 = NULL;
// 						str2 =  root->seperator;
// 						str1 = ft_strjoin(str1, str2);
// 						str2 = NULL;
// 					}

// 				}

// 				// if (t_minishell->commandlen == 0)
// 				// {
// 				// 	// int temp;
// 				// 	// temp = 0;

// 				// 	t_minishell->commandlen = t_minishell->commandlen + 2;
// 				// 	t_minishell->commands = ft_calloc(t_minishell->commandlen, sizeof(char *));

// 				// 	//what im trying to do here is to split

// 				// }


// 				// i need to store the pipe
// 				// need to allocate space.
// 			}
// 		}
// 		else
// 		{
// 			// printf("Argument\n");
// 			printf("Token here %d: %s\n",temp ,root->token);
// 			if (root->token != NULL)
// 			{
// 				if (str1 == NULL)
// 				{
// 					str1 = root->token;
// 				}
// 				else if (str2 == NULL)
// 				{
// 					str2 = root->token;
// 					str1 = ft_strjoin(str1, str2);
// 					str2 = NULL;
// 				}
// 				else 
// 				{
// 					str1 = ft_strjoin(str1, str2);
// 					str2 = NULL;
// 					str2 = root->token;
// 					str1 = ft_strjoin(str1, str2);
// 					str2 = NULL;
// 				}
// 			}
// 		}
 
// 		str1 = inorderTraversal(root->right, str1, t_minishell, temp);
		
//     }
// 	return str1;
// }


void cleanupstring(struct s_minishell *t_minishell)
{

	char *str1; 
	printf("\n\n\n\n\n\n\n\n");

	int temp;
	temp = 0;

	printf("string clean up in order traverse\n");	
	str1 = inorderTraversal(t_minishell->rootnode, NULL, t_minishell, temp);
	printf("end:%s\n", str1);
	// printf("check:%s \n", t_minishell->command)
	// sub $
	// clean up empty str
}