/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aadenan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 12:33:32 by aadenan           #+#    #+#             */
/*   Updated: 2024/05/01 16:42:53 by aadenan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Just a very mini mini bash version for my own reference
// Why Ctrl + c not displaying back the prompt?
// Why Ctrl + \ not ignoring "^\"?
// Why Ctrl + d showed "%"?
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_ARGS 64
#define MAX_COMMAND_LENGTH 1024

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
	fflush(stdout);
}

int main(void)
{
    char input[MAX_COMMAND_LENGTH]; // Buffer to store user input command
    char *args[MAX_ARGS];           // Array to store parsed arguments of the command

    // Register signal handler for SIGINT (Ctrl+C)
    signal(SIGINT, handle_sigint);
    // Ignore SIGQUIT (Ctrl+\)
    signal(SIGQUIT, SIG_IGN);

    // Print shell start message
    printf("Shell started.\n");

    // Infinite loop to continuously accept user input
    while (1)
    {
        // Print shell prompt
        printf("Very mini bash ~$ ");
        // Flush output buffer to ensure prompt is immediately displayed
        fflush(stdout);

        // Read user input from stdin
        if (fgets(input, MAX_COMMAND_LENGTH, stdin) == NULL)
        {
            // Break the loop if Ctrl+D (EOF) is entered
            break;
        }

        // Parse user input into arguments
        parse_input(input, args);

        // If no arguments provided, continue to next iteration
        if (args[0] == NULL)
        {
            continue;
        }

        // Check if user wants to exit the shell
        if (strcmp(args[0], "exit") == 0)
	{
            // Break the loop if "exit" command is entered
            break;
        }
        // Check if user wants to change directory
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
    }

    // Exit the shell
    return EXIT_SUCCESS;
}
