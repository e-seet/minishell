/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draft_bash.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aadenan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 16:21:47 by aadenan           #+#    #+#             */
/*   Updated: 2024/05/05 14:34:18 by aadenan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Draft bash v2.0
// Improved version of very mini mini bash for my own reference
// Resolved signal issues for Ctrl+c, Ctrl+\, Ctrl+d
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/wait.h>
#include <sys/types.h>

#define MAX_ARGS 64

void parse_input(char *input, char **args)
{
    char *token;  // Declare a pointer to hold each token (word) extracted from the input
    int i = 0;    // Initialize a counter for the array index

    // Extract the first token from the input using strtok() function
    // The delimiters for tokenization are space, tab, and newline characters
    token = strtok(input, " \t\n");

    // Iterate through the tokens until there are no more tokens or the maximum number
    // of arguments is reached
    while (token != NULL && i < MAX_ARGS - 1)
    {
        // Store the token in the args array at the current index
        args[i] = token;
        // Move to the next token in the input string
        token = strtok(NULL, " \t\n");
        // Increment the index counter to move to the next position in the args array
        i++;
    }

    // Set the next element in the args array to NULL to mark the end of the argument list
    args[i] = NULL;
}

void execute_command(char **args)
{
    pid_t pid;   // Process ID variable
    int status;  // Status of the child process

    // Create a new process by forking the current process
    pid = fork();
    // Check for fork failure
    if (pid < 0)
    {
        // Print an error message and exit if fork fails
        perror("fork");
        exit(EXIT_FAILURE);
    }
    // If pid is 0, this is the child process
    else if (pid == 0)
    {
        // Execute the command in the child process using execvp
        // execvp replaces the current process with a new process as specified by the arguments
        // args[0] is the command to be executed, and args is the array of arguments
        // including the command
        // If execvp returns -1, an error occurred
        if (execvp(args[0], args) == -1)
        {
            // Print an error message if execvp fails and exit the child process
            perror("exec");
            exit(EXIT_FAILURE);
        }
    }
    // If pid is greater than 0, this is the parent process
    else
    {
        // Parent process waits for the child process to complete
        do
            // waitpid suspends execution of the calling process until a child specified
            // by pid argument has changed state
            waitpid(pid, &status, WUNTRACED);
        // Loop until the child process either exits normally or is terminated by a signal
        while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }
}

void cd(char **args)
{
    // Check if the second argument (directory) is missing
    if (args[1] == NULL)
        // Print an error message to stderr if the directory argument is missing
        fprintf(stderr, "cd: missing argument\n");
    else
    {
        // Change the current working directory to the directory specified by args[1]
        // chdir() function returns 0 on success, -1 on failure
        if (chdir(args[1]) != 0)
            // Print an error message if chdir fails
            perror("cd");
    }
}

void handle_sigint(int sig)
{
    printf("\n");
    // Move the cursor to the beginning of the next line
    rl_on_new_line();
    // Redisplay the readline prompt (redraw the current input line)
    rl_redisplay();
}

int main(void)
{
    char *input;
    char *args[MAX_ARGS];

    // Register signal handler for SIGINT (Ctrl+c)
    signal(SIGINT, handle_sigint);
    // Ignore SIGQUIT (Ctrl+\)
    signal(SIGQUIT, SIG_IGN);

    // Infinite loop to continuously accept user input
    while (1)
    {
        // Read a line of input with readline
        input = readline("Bash me up$: ");

        // Check if Ctrl+D (EOF) is encountered
        if (input == NULL)
	{
            printf("exit\n");
            break;
        }

	// Parse user input into arguments
	parse_input(input, args);
	
	// If no arguments provided, continue to next iteration
	if (args[0] == NULL)
	{
	    continue;
	}

	// Remove empty str function here?

        // Check if the user wants to exit
        if (strcmp(args[0], "exit") == 0)
	{
	    printf("exit\n");
            free(input); // Free memory
            break; // Exit the loop
        }
	else if (strcmp(args[0], "cd") == 0)
	{
	    // Call cd function to change directory
	    cd(args);
	}
	// Execute other commands
	else
	{
	    // Call function to execute the command
	    execute_command(args);
	}

        // Add the input to history
        if (input)
            add_history(input);

        // Display the input
        // printf("You entered: %s\n", input);

        // Free the memory allocated for the input
        free(input);
    }

    return 0;
}

