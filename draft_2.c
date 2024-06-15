/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draft_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aadenan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 11:08:06 by aadenan           #+#    #+#             */
/*   Updated: 2024/06/14 15:00:02 by aadenan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// SIGINT during heredoc("<<") does not work correctly.
// fork issue for ("<<")?
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <fcntl.h>
#include <errno.h>
#include <ctype.h>
#define MAX_LINE 1024
#define MAX_TOKENS 100

int exit_status = 0;
int in_heredoc = 0;
int sigint_flag = 0;

// handle Cmd + C
// check if in heredoc, if so, clear flag
// and repalce the line
void default_sigint(int sig)
{
	if (in_heredoc == 0)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	in_heredoc = 0;
	exit_status = 130;
}

//
void heredoc_sigint(int sig)
{
	printf("\nSIGINT in heredoc\n");
	sigint_flag = 1;
	in_heredoc = 0;
}

// !!not used
// char* expand_env_variable(const char* input) 
// {
//     // Maximum length of expanded string
//     size_t max_len = 2048; // Adjust as needed
//     char* expanded = (char*)malloc(max_len);
//     if (expanded == NULL)
// 	{
//         fprintf(stderr, "Memory allocation failed.\n");
//         exit(EXIT_FAILURE);
//     }

//     size_t input_len = strlen(input);
//     size_t out_pos = 0;

//     for (size_t i = 0; i < input_len; ++i)
// 	{
//         if (input[i] == '$' && input[i + 1] == '{')
// 		{
//             // Found a possible environment variable
//             size_t j = i + 2;
//             while (input[j] != '\0' && input[j] != '}')
// 			{
//                 ++j;
//             }
//             if (input[j] == '}') 
// 			{
//                 // Valid environment variable found
//                 size_t name_len = j - i - 2;
//                 char* name = (char*)malloc(name_len + 1);
//                 if (name == NULL) 
// 				{
//                     fprintf(stderr, "Memory allocation failed.\n");
//                     exit(EXIT_FAILURE);
//                 }
//                 memcpy(name, &input[i + 2], name_len);
//                 name[name_len] = '\0';
//                 const char* value = getenv(name);
//                 if (value != NULL)
// 				 {
//                     size_t value_len = strlen(value);
//                     if (out_pos + value_len > max_len - 1) 
// 					{
//                         max_len *= 2;
//                         expanded = (char*)realloc(expanded, max_len);
//                         if (expanded == NULL) {
//                             fprintf(stderr, "Memory allocation failed.\n");
//                             exit(EXIT_FAILURE);
//                         }
//                     }
//                     memcpy(&expanded[out_pos], value, value_len);
//                     out_pos += value_len;
//                     i = j; // Skip the rest of the environment variable
//                 }
//                 free(name);
//             }
//         } else 
// 		{
//             expanded[out_pos++] = input[i];
//         }

//         if (out_pos >= max_len - 1) 
// 		{
//             // Increase buffer size if needed
//             max_len *= 2;
//             expanded = (char*)realloc(expanded, max_len);
//             if (expanded == NULL) 
// 			{
//                 fprintf(stderr, "Memory allocation failed.\n");
//                 exit(EXIT_FAILURE);
//             }
//         }
//     }

//     expanded[out_pos] = '\0';
//     return expanded;
// }

// Expand environment variables in a string
// Convert from $xx to the path in env variable
char* expand_variables(const char* input) 
{
    char* result = malloc(strlen(input) + 1);
    int i = 0, j = 0;
    while (input[i] != '\0') 
	{
        if (input[i] == '$' && input[i + 1] != '\0') 
		{
            i++;
            char varName[100];
            int k = 0;
            while (input[i] != '\0' && (isalnum(input[i]) || input[i] == '_')) 
			{
                varName[k++] = input[i++];
            }
            varName[k] = '\0';
            char* varValue = getenv(varName);
            if (varValue) 
			{
                strcpy(&result[j], varValue);
                j += strlen(varValue);
            }
        }
		else
		{
            result[j++] = input[i++];
        }
    }
    result[j] = '\0';
    return result;
}

// Tokenize input considering quotes
// !! Eddie to look through again
char** tokenize(char* input)
{
    char** tokens = malloc(MAX_TOKENS * sizeof(char*));
    char* token = malloc(strlen(input) + 1);
    char *tmp;

	// i control input
	// j control token
	// k controls tokens
	int i = 0, j = 0, k = 0;

    int inSingleQuote = 0, inDoubleQuote = 0, onlyDollar = 0;

    while (input[i] != '\0')
    {
		// !!
		// ?? Why need to check for single and double quotation
		// There is single and double quotation
		if (input[i] == '$' && !inSingleQuote && !inDoubleQuote)
		{
    		onlyDollar = 1;
		}
		
		// !! 
		// ?? Why need to check it is in double quotation
        if (input[i] == '\'' && !inDoubleQuote)
		{
            inSingleQuote = !inSingleQuote;
        }
		// !! Why this
		// There is single quote and now encountered double quote
		else if (input[i] == '"' && !inSingleQuote)
		{
			inDoubleQuote = !inDoubleQuote;
            if (!inDoubleQuote)
			{
                token[j] = '\0';				
                char* expanded = expand_variables(token);
                strcpy(token, expanded);
                free(expanded);
                j = strlen(token);
            }
        }
		// !! Why this?
		// There is double and single quotation
		// no dollar sign
		// Met space
		else if (input[i] == ' ' && !inSingleQuote && !inDoubleQuote && onlyDollar == 0)
		{
            if (j > 0)
	    	{
                token[j] = '\0';
                tokens[k++] = strdup(token);
                j = 0;
            }
        }

		// handle env variable
		else if ((!inSingleQuote && !inDoubleQuote && onlyDollar == 1) && (input[i] == ' '
				|| input[i + 1] == '\0' || input[i + 1] == ' '))
		{
			if (token[j] == ' ')
			{
					token[j] = '\0';
			}
    		else
			{
				token[j] = input[i];
			}
    		char *expanded = expand_variables(token);
    		strcpy(token, expanded);
    		free(expanded);
    		j = strlen(token);
    		onlyDollar = 0;
		}
		else
		{
            token[j++] = input[i];
        }
        i++;
    }

    if (j > 0)
    {
        token[j] = '\0';
        if (inDoubleQuote)
		{
            char* expanded = expand_variables(token);
            strcpy(token, expanded);
            free(expanded);
        }
        tokens[k++] = strdup(token);
    }
    tokens[k] = NULL;
    for (int l = 0; tokens[l] != NULL; l++)
	    printf("tokens: %s\n", tokens[l]);
    free(token);
    return tokens;
}

// Handle redirections: >, >>, <, <<
int handleRedirections(char** command)
{
    int fd;
    for (int i = 0; command[i] != NULL; i++) 
	{
        if (strcmp(command[i], ">") == 0) 
		{
            fd = open(command[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
            if (fd == -1) 
			{
                perror("open");
                return -1;
            }
            dup2(fd, STDOUT_FILENO);
            close(fd);
            command[i] = NULL;
        } 
		else if (strcmp(command[i], ">>") == 0) 
		{
            fd = open(command[i + 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
            if (fd == -1) 
			{
                perror("open");
                return -1;
            }
            dup2(fd, STDOUT_FILENO);
            close(fd);
            command[i] = NULL;
        } 
		else if (strcmp(command[i], "<") == 0) 
		{
            fd = open(command[i + 1], O_RDONLY);
            if (fd == -1) 
			{
                perror("open");
                return -1;
            }
            dup2(fd, STDIN_FILENO);
            close(fd);
            command[i] = NULL;
        }
		
		else if (strcmp(command[i], "<<") == 0)
		{
            char* endMarker = command[i + 1];
            char line[1024];
            int pipefd[2];
            pipe(pipefd);
	    	in_heredoc = 1;
            if (fork() == 0)
		    {
				printf("Children process...\n");
				signal(SIGINT, heredoc_sigint);
                close(pipefd[0]);
                while (1)
				{
				    printf("> ");
                    fgets(line, sizeof(line), stdin);
					if (sigint_flag == 1)
					{
						close(pipefd[1]);
					exit(0);
					}
					if (feof(stdin))
					{
						printf("\nCtrl + D pressed during heredoc\n");
						break;
					}
					if (strncmp(line, endMarker, strlen(endMarker)) == 0
							&& line[strlen(endMarker)] == '\n')
					{
						break;
					}
                    write(pipefd[1], line, strlen(line));
                }
                close(pipefd[1]);
                exit(0);
            }
			else
			{
				wait(NULL);
				printf("Parent process...\n");
				close(pipefd[1]);
				dup2(pipefd[0], STDIN_FILENO);
				close(pipefd[0]);
				//wait(NULL);
				signal(SIGINT, SIG_DFL);
			}
			command[i] = NULL;
		}
    }
    return 0;
}

// Built-in command implementations
void builtin_echo(char** args) 
{
    int flag = 0;
    int nFlag = 0;
    int i = 1;

    for (int idx = 0; args[idx] != NULL; idx++)
    {
        if(strcmp(args[idx], ">") == 0 || strcmp(args[idx], ">>") == 0)
		{
			flag = 1;
			break;
		}
    }
    if (flag == 0) 
	{
        if (args[1] && strcmp(args[1], "-n") == 0) 
		{
            nFlag = 1;
            i++;
        }
        for (; args[i] != NULL; i++) 
		{
            if (i > 1 + nFlag) 
			{
                printf(" ");
            }
        }
        if (!nFlag) 
		{
            //printf("\n");
        }
    }
}

void builtin_cd(char** args) 
{
    if (args[1] == NULL)
	{
        fprintf(stderr, "cd: missing argument\n");
    } 
	else 
	{
        if (chdir(args[1]) != 0) 
		{
            perror("cd");
        }
    }
}

void builtin_pwd() 
{
    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) != NULL) 
	{
		return;
    } 
	else
	{
        perror("pwd");
    }
}

void builtin_export(char** args) 
{
    for (int i = 1; args[i] != NULL; i++) 
	{
        char* equalSign = strchr(args[i], '=');
        if (equalSign) 
		{
            *equalSign = '\0';
            if (setenv(args[i], equalSign + 1, 1) != 0) 
			{
                perror("export");
            }
            *equalSign = '=';
        } 
		else 
		{
            fprintf(stderr, "export: invalid format\n");
        }
    }
}

void builtin_unset(char** args) 
{
    for (int i = 1; args[i] != NULL; i++) 
	{
        if (unsetenv(args[i]) != 0) 
		{
            perror("unset");
        }
    }
}

void builtin_env() 
{
    extern char **environ;
    for (char **env = environ; *env != 0; env++) 
	{
        printf("%s\n", *env);
    }
}

void builtin_exit(char** args) 
{
    int exit_status = 0;
    if (args[1] != NULL) 
	{
        exit_status = atoi(args[1]);
    }
    exit(exit_status);
}

// Handle built-in commands
int handleBuiltins(char** args) 
{
    if (strcmp(args[0], "echo") == 0) 
	{
        builtin_echo(args);
        return 1;
    }
	else if (strcmp(args[0], "cd") == 0) 
	{
        builtin_cd(args);
        return 1;
    }
	else if (strcmp(args[0], "pwd") == 0) 
	{
        builtin_pwd();
        return 1;
    }
	else if (strcmp(args[0], "export") == 0) 
	{
        builtin_export(args);
        return 1;
    }
	else if (strcmp(args[0], "unset") == 0) 
	{
        builtin_unset(args);
        return 1;
    }
	else if (strcmp(args[0], "env") == 0)
	{
        builtin_env();
        return 1;
    }
	else if (strcmp(args[0], "exit") == 0)
	{
        builtin_exit(args);
        return 1;
    }
    return 0;
}

// handle the execution if there is no pipes
void executeCommand(char** command)
{
    if (handleBuiltins(command) == -1)
	{
        return;
    }
    if (strcmp(command[0], "cd") == 0 || strcmp(command[0], "export") == 0
		    || strcmp(command[0], "unset") == 0)
        return;
    pid_t pid = fork();
    if (pid < 0)
    {
        perror("fork failed");
		exit_status = -1;
        return;
    }
    if (pid == 0)
    {
        if (handleRedirections(command) == -1)
        {
            exit(EXIT_FAILURE);
        }
        if (execvp(command[0], command) == -1)
        {
            perror("execvp failed");
            exit(EXIT_FAILURE);
        }
    }
    else
    {
        int status;
        wait(&status);
        // Optionally handle the status
    }
    exit_status = 0;
}

// Handling of execution with pipes
// Will handle any redirection with dup2 here as well
// !! not used as well? 
// void executePipe(char** leftCmd, char** rightCmd)
// {
//     // Execute two commands connected by a single pipe
//     int pipefd[2];
//     if (pipe(pipefd) < 0)
//     {
//         perror("pipe");
//         exit(EXIT_FAILURE);
//     }

//     if (fork() == 0)
//     {
//         dup2(pipefd[1], 1);
//         close(pipefd[0]);
//         close(pipefd[1]);
//         execvp(leftCmd[0], leftCmd);
//         perror("execvp");
//         exit(EXIT_FAILURE);
//     }

//     if (fork() == 0)
//     {
//         dup2(pipefd[0], 0);
//         close(pipefd[1]);
//         close(pipefd[0]);
//         execvp(rightCmd[0], rightCmd);
//         perror("execvp");
//         exit(EXIT_FAILURE);
//     }

//     close(pipefd[0]);
//     close(pipefd[1]);
//     wait(NULL);
//     wait(NULL);
// }

// prepare pipes
// handle redirection
// handle execution
// close pipes
void executeMultiplePipes(char*** commands, int n) 
{
    int pipefds[2 * (n - 1)];

	// initialize the int array with pipe()
	// Each pipe prepares 2 index
	// pipefds[0] (read), pipesfd[1] (write)
	// pipefds[1] (read), pipesfd[2] (write)
    for (int i = 0; i < n - 1; i++) 
	{
        if (pipe(pipefds + i * 2) < 0) 
		{
            perror("pipe");
            exit(EXIT_FAILURE);
        }
    }

    for (int i = 0; i < n; i++) 
	{
        pid_t pid = fork();
        if (pid == 0) 
		{
            // If not the first command, get input from previous pipe
            if (i != 0) 
			{
				// even pipe so it is read
                if (dup2(pipefds[(i - 1) * 2], 0) < 0) 
				{
                    perror("dup2");
                    exit(EXIT_FAILURE);
                }
            }

            // If not the last command, output to next pipe
            if (i != n - 1) 
			{
				// odd pipe so it is write
                if (dup2(pipefds[i * 2 + 1], 1) < 0) 
				{
                    perror("dup2");
                    exit(EXIT_FAILURE);
                }
            }

            // Close all pipe file descriptors
			// !! huh? Why here?
            for (int j = 0; j < 2 * (n - 1); j++) 
			{
                close(pipefds[j]);
            }

            // Handle redirections (dup2 all here)
            if (handleRedirections(commands[i]) < 0) 
			{
                exit(EXIT_FAILURE); // Exit if redirection fails
            }

            // Execute the command
            execvp(commands[i][0], commands[i]);
            perror("execvp");
            exit(EXIT_FAILURE);
        }
		else if (pid < 0) 
		{
            perror("fork");
            exit(EXIT_FAILURE);
        }
    }

    // Close all pipe file descriptors in parent
    for (int i = 0; i < 2 * (n - 1); i++) 
	{
        close(pipefds[i]);
    }

    // Wait for all children to finish
    for (int i = 0; i < n; i++) 
	{
        wait(NULL);
    }
}

// Adding " " if required
static char *modify_input(const char *input)
{
    if (input == NULL) 
		return NULL;

    char *new_input;
    int i = 0;
    int j = 0;
    int len = 0;

    // Calculate the length of the new string
	// eg: xx>>yy
	// reformat to xx >> yy
    while (input[i] != '\0')
    {
        if (input[i] == '>')
        {
            if (input[i] == '>' && input[i + 1] == '>')
            {
                if (i > 0 && input[i - 1] != ' ')
                    len++;
                len += 3; // Adding space for ' >> '
                i++; // Skip the next '>'
            }
            else
            {
                if (input[i - 1] != ' ' && input[i + 1] != ' ')
                    len += 3;
            }
        }
        if (input[i] == '<')
        {
            if (input[i] == '<' && input[i + 1] == '<')
            {
                if (i > 0 && input[i - 1] != ' ')
                    len++;
                len += 3; // Adding space for ' << '
                i++; // Skip the next '<'
            }
            else
            {
                if (input[i - 1] != ' ' && input[i + 1] != ' ')
                    len += 3;
            }
        }
        else
        {
            len++;
        }
        i++;
    }

    new_input = (char *)malloc(sizeof(char) * (len + 1));
    if (new_input == NULL)
        return NULL; // Check for malloc failure

    i = 0;

    // Construct the new string
    while (input[i] != '\0')
    {
        if (input[i] == '>' && input[i - 1] != ' ' && input[i + 1] != ' ')
        {
            if (i > 0 && input[i - 1] != ' ')
                new_input[j++] = ' ';
            new_input[j++] = '>';
            if (input[i + 1] == '>')
            {
                new_input[j++] = '>';
                i++;
                if (input[i + 1] != '\0' && input[i + 1] != ' ')
                    new_input[j++] = ' ';
            }
            else
            {
                if (input[i + 1] != '\0' && input[i + 1] != ' ')
                {
                    new_input[j++] = ' ';
                }
            }
            i++;
        }
        else if (input[i] == '<' && input[i - 1] != ' ' && input[i + 1] != ' ')
        {
            if (i > 0 && input[i - 1] != ' ')
                new_input[j++] = ' ';
            new_input[j++] = '<';
            if (input[i + 1] == '<')
            {
                new_input[j++] = '<';
                i++;
                if (input[i + 1] != '\0' && input[i + 1] != ' ')
                    new_input[j++] = ' ';
            }
            else
            {
                if (input[i + 1] != '\0' && input[i + 1] != ' ')
                {
                    new_input[j++] = ' ';
                }
            }
            i++;
        }
        else
        {
            new_input[j++] = input[i++];
        }
    }
    new_input[j] = '\0';

    return new_input;
}

// Function to execute a sequence of commands, potentially with pipes
void executeSequence(char* input)
{

    // this changes the string by adding spaces
	char *corrected_input = modify_input(input);
    printf("Corrected input: %s\n", corrected_input);

    // Count number of pipes in the command
    int pipeCount = 0;
    for (char* temp = corrected_input; *temp != '\0'; temp++) 
	{
        if (*temp == '|') pipeCount++;
    }

    if (pipeCount > 0) 
	{
        // Tokenize command by pipes
        char** commands = malloc((pipeCount + 2) * sizeof(char*));
        int i = 0;
        char* pipeToken = strtok(corrected_input, "|");
        while (pipeToken != NULL) 
		{
            commands[i++] = pipeToken;
			// Go to the next occurance of | in corrected_input
            pipeToken = strtok(NULL, "|");
        }
        commands[i] = NULL; // Null-terminate the array

        // Tokenize each command and store in a 2D array
        char*** tokenizedCommands = malloc((pipeCount + 1) * sizeof(char**));
        for (int j = 0; j <= pipeCount; j++) 
		{
            tokenizedCommands[j] = tokenize(commands[j]);
        }

        // Execute the sequence of commands with pipes
        executeMultiplePipes(tokenizedCommands, pipeCount + 1);

        // Free memory
        for (int j = 0; j <= pipeCount; j++) 
		{
            free(tokenizedCommands[j]);
        }
        free(tokenizedCommands);
        free(commands);
    }
	else 
	{
        char** cmd = tokenize(corrected_input);
        executeCommand(cmd);
        free(cmd);
    }
    free(corrected_input);
}

// Function to replace all occurrences of $? with the last exit status
void replace_exit_status(char *cmd) 
{
    char buffer[MAX_LINE];
    char *pos;
    char last_exit_str[10];
    snprintf(last_exit_str, sizeof(last_exit_str), "%d", exit_status);

    while ((pos = strstr(cmd, "$?")) != NULL) 
	{
        *pos = '\0';
        snprintf(buffer, sizeof(buffer), "%s%s%s", cmd, last_exit_str, pos + 2);
        strcpy(cmd, buffer);
    }
}

// check for
// 1. empty strings  "" or ''
// 2. invalid strings 
// 3. ?? Why the need for env check? !!
static int check_input(char *input)
{
    int i = 0;

    if ((input[0] == '"' && input[1] == '"') || (input[0] == '\'' && input[1] == '\''))
	    return 1;
    if ((input[0] == '"' && input[1] == '\0') || (input[0] == '\'' && input[1] == '\0'))
	    return 1;
    while (input[i] != '\0')
    {
        while (input[i] == ' ')
            i++;
		// !!What is this check for? 
        if (input[i] == '|')
        {
            printf("bash error\n");
            return (1);
		}
		// !!Why is there a check for just env?
		else if (strstr(input, "env") != NULL)
		{
			if (strcmp(input, "env") != 0)
			{
				printf("env error\n");
				add_history(input);
				return (1);
			}
			return (0);
		}
		else
			return (0);
	}
    return (0);
}

int main(void)
{
    int flag = 0;
    char *input;

    signal(SIGINT, default_sigint);
    signal(SIGQUIT, SIG_IGN);
    while (1)
    {
        input = readline("Bash me up$: ");
		if (input == NULL)
		{
			printf("Ctrl + D pressed outside heredoc\n");
			break;
		}

		if (check_input(input) == 1)
			flag = 1;
		if (input[0] != '\0' && flag == 0)
		{
			add_history(input);
			replace_exit_status(input);
			executeSequence(input);
		}
		free(input);
		flag = 0;
	}
    return (0);
}
