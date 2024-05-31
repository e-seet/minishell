/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draft_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aadenan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 11:08:06 by aadenan           #+#    #+#             */
/*   Updated: 2024/05/31 15:38:39 by aadenan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Fix 2 pipes with 1 redirection
// Might need to rethink about export & unset
// Soon to be draft_bash v0.3

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

#define MAX_TOKENS 100
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* expand_env_variable(const char* input) {
    // Maximum length of expanded string
    size_t max_len = 2048; // Adjust as needed
    char* expanded = (char*)malloc(max_len);
    if (expanded == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }

    size_t input_len = strlen(input);
    size_t out_pos = 0;

    for (size_t i = 0; i < input_len; ++i) {
        if (input[i] == '$' && input[i + 1] == '{') {
            // Found a possible environment variable
            size_t j = i + 2;
            while (input[j] != '\0' && input[j] != '}') {
                ++j;
            }
            if (input[j] == '}') {
                // Valid environment variable found
                size_t name_len = j - i - 2;
                char* name = (char*)malloc(name_len + 1);
                if (name == NULL) {
                    fprintf(stderr, "Memory allocation failed.\n");
                    exit(EXIT_FAILURE);
                }
                memcpy(name, &input[i + 2], name_len);
                name[name_len] = '\0';
                const char* value = getenv(name);
                if (value != NULL) {
                    size_t value_len = strlen(value);
                    if (out_pos + value_len > max_len - 1) {
                        max_len *= 2;
                        expanded = (char*)realloc(expanded, max_len);
                        if (expanded == NULL) {
                            fprintf(stderr, "Memory allocation failed.\n");
                            exit(EXIT_FAILURE);
                        }
                    }
                    memcpy(&expanded[out_pos], value, value_len);
                    out_pos += value_len;
                    i = j; // Skip the rest of the environment variable
                }
                free(name);
            }
        } else {
            expanded[out_pos++] = input[i];
        }

        if (out_pos >= max_len - 1) {
            // Increase buffer size if needed
            max_len *= 2;
            expanded = (char*)realloc(expanded, max_len);
            if (expanded == NULL) {
                fprintf(stderr, "Memory allocation failed.\n");
                exit(EXIT_FAILURE);
            }
        }
    }

    expanded[out_pos] = '\0';
    return expanded;
}

// Expand environment variables in a string
char* expand_variables(const char* input) {
    char* result = malloc(strlen(input) + 1);
    int i = 0, j = 0;
    while (input[i] != '\0') {
        if (input[i] == '$' && input[i + 1] != '\0') {
            i++;
            char varName[100];
            int k = 0;
            while (input[i] != '\0' && (isalnum(input[i]) || input[i] == '_')) {
                varName[k++] = input[i++];
            }
            varName[k] = '\0';
            char* varValue = getenv(varName);
            if (varValue) {
                strcpy(&result[j], varValue);
                j += strlen(varValue);
            }
        } else {
            result[j++] = input[i++];
        }
    }
    result[j] = '\0';
    return result;
}

// Tokenize input considering quotes
char** tokenize(char* input)
{
    char** tokens = malloc(MAX_TOKENS * sizeof(char*));
    char* token = malloc(strlen(input) + 1);
    char *tmp;
    int i = 0, j = 0, k = 0, m = 0;
    int inSingleQuote = 0, inDoubleQuote = 0, onlyDollar = 0;

    while (input[i] != '\0')
    {
	if (input[i] == '$' && !inSingleQuote && !inDoubleQuote)
	{
    		onlyDollar = 1;
	}
        if (input[i] == '\'' && !inDoubleQuote)
	{
            inSingleQuote = !inSingleQuote;
        }
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
	else if (input[i] == ' ' && !inSingleQuote && !inDoubleQuote)
	{
            if (j > 0)
	    {
                token[j] = '\0';
                tokens[k++] = strdup(token);
                j = 0;
            }
        }
	else if ((!inSingleQuote && !inDoubleQuote && onlyDollar == 1) && (input[i] == ' '
				|| input[i + 1] == '\0'))
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
int handleRedirections(char** command) {
    int fd;
    for (int i = 0; command[i] != NULL; i++) {
        if (strcmp(command[i], ">") == 0) {
            fd = open(command[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
            if (fd == -1) {
                perror("open");
                return -1;
            }
            dup2(fd, STDOUT_FILENO);
            close(fd);
            command[i] = NULL;
        } else if (strcmp(command[i], ">>") == 0) {
            fd = open(command[i + 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
            if (fd == -1) {
                perror("open");
                return -1;
            }
            dup2(fd, STDOUT_FILENO);
            close(fd);
            command[i] = NULL;
        } else if (strcmp(command[i], "<") == 0) {
            fd = open(command[i + 1], O_RDONLY);
            if (fd == -1) {
                perror("open");
                return -1;
            }
            dup2(fd, STDIN_FILENO);
            close(fd);
            command[i] = NULL;
        } else if (strcmp(command[i], "<<") == 0) {
            char* endMarker = command[i + 1];
            char line[1024];
            int pipefd[2];
            pipe(pipefd);

            if (fork() == 0) {
                close(pipefd[0]);
                while (1) {
                    printf("> ");
                    fgets(line, sizeof(line), stdin);
                    if (strncmp(line, endMarker, strlen(endMarker)) == 0 && line[strlen(endMarker)] == '\n') {
                        break;
                    }
                    write(pipefd[1], line, strlen(line));
                }
                close(pipefd[1]);
                exit(0);
            } else {
                close(pipefd[1]);
                dup2(pipefd[0], STDIN_FILENO);
                close(pipefd[0]);
                wait(NULL);
            }
            command[i] = NULL;
        }
    }
    return 0;
}

// Built-in command implementations
void builtin_echo(char** args) {
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
    if (flag == 0) {
        if (args[1] && strcmp(args[1], "-n") == 0) {
            nFlag = 1;
            i++;
        }
        for (; args[i] != NULL; i++) {
            if (i > 1 + nFlag) {
                printf(" ");
            }
        }
        if (!nFlag) {
            //printf("\n");
        }
    }
}

void builtin_cd(char** args) {
    if (args[1] == NULL) {
        fprintf(stderr, "cd: missing argument\n");
    } else {
        if (chdir(args[1]) != 0) {
            perror("cd");
        }
    }
}

void builtin_pwd() {
    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
	return;
    } else {
        perror("pwd");
    }
}

void builtin_export(char** args) {
    for (int i = 1; args[i] != NULL; i++) {
        char* equalSign = strchr(args[i], '=');
        if (equalSign) {
            *equalSign = '\0';
            if (setenv(args[i], equalSign + 1, 1) != 0) {
                perror("export");
            }
            *equalSign = '=';
        } else {
            fprintf(stderr, "export: invalid format\n");
        }
    }
}

void builtin_unset(char** args) {
    for (int i = 1; args[i] != NULL; i++) {
        if (unsetenv(args[i]) != 0) {
            perror("unset");
        }
    }
}

void builtin_env() {
    extern char **environ;
    for (char **env = environ; *env != 0; env++) {
        printf("%s\n", *env);
    }
}

void builtin_exit(char** args) {
    int exit_status = 0;
    if (args[1] != NULL) {
        exit_status = atoi(args[1]);
    }
    exit(exit_status);
}

// Handle built-in commands
int handleBuiltins(char** args) {
    if (strcmp(args[0], "echo") == 0) {
        builtin_echo(args);
        return 1;
    } else if (strcmp(args[0], "cd") == 0) {
        builtin_cd(args);
        return 1;
    } else if (strcmp(args[0], "pwd") == 0) {
        builtin_pwd();
        return 1;
    } else if (strcmp(args[0], "export") == 0) {
        builtin_export(args);
        return 1;
    } else if (strcmp(args[0], "unset") == 0) {
        builtin_unset(args);
        return 1;
    } else if (strcmp(args[0], "env") == 0) {
        builtin_env();
        return 1;
    } else if (strcmp(args[0], "exit") == 0) {
        builtin_exit(args);
        return 1;
    }
    return 0;
}

// Execute a single command
void executeCommand(char** command)
{
    if (handleBuiltins(command) == -1) {
        return;
    }
    pid_t pid = fork();
    if (pid == 0)
    {
        if (handleRedirections(command) == -1)
	{
            exit(EXIT_FAILURE);
        }
        if (execvp(command[0], command) == -1 && strcmp(command[0], "unset") != 0
			&& strcmp(command[0], "export") != 0)
	{
            perror("execvp failed");
            exit(EXIT_FAILURE);
	}
	if (strcmp(command[0], "unset") == 0 || strcmp(command[0], "export") == 0)
		exit(0);
    }
    else
    {
        wait(NULL);
    }
}
/*
// Execute a piped command
void executePipe(char** leftCmd, char** rightCmd) {
    int pipefd[2];
    pipe(pipefd);
    pid_t pid = fork();
    if (pid == 0) {
        dup2(pipefd[1], STDOUT_FILENO);
        close(pipefd[0]);
        close(pipefd[1]);
        if (handleRedirections(leftCmd) == -1) {
            exit(EXIT_FAILURE);
        }
        execvp(leftCmd[0], leftCmd);
        perror("execvp failed");
        exit(EXIT_FAILURE);
    } else {
        pid_t pid2 = fork();
        if (pid2 == 0) {
            dup2(pipefd[0], STDIN_FILENO);
            close(pipefd[0]);
            close(pipefd[1]);
            if (handleRedirections(rightCmd) == -1) {
                exit(EXIT_FAILURE);
            }
            execvp(rightCmd[0], rightCmd);
            perror("execvp failed");
            exit(EXIT_FAILURE);
        } else {
            close(pipefd[0]);
            close(pipefd[1]);
            wait(NULL);
            //wait(NULL);
        }
    }
}
*/
void executePipe(char** leftCmd, char** rightCmd)
{
    // Execute two commands connected by a single pipe
    int pipefd[2];
    if (pipe(pipefd) < 0)
    {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    if (fork() == 0)
    {
        dup2(pipefd[1], 1);
        close(pipefd[0]);
        close(pipefd[1]);
        execvp(leftCmd[0], leftCmd);
        perror("execvp");
        exit(EXIT_FAILURE);
    }

    if (fork() == 0)
    {
        dup2(pipefd[0], 0);
        close(pipefd[1]);
        close(pipefd[0]);
        execvp(rightCmd[0], rightCmd);
        perror("execvp");
        exit(EXIT_FAILURE);
    }

    close(pipefd[0]);
    close(pipefd[1]);
    wait(NULL);
    wait(NULL);
}
// This function will need to handle the execution of multiple commands connected by pipes
void executeMultiplePipes(char*** commands, int n)
{
    int pipefds[2 * (n - 1)];
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
                if (dup2(pipefds[(i - 1) * 2], 0) < 0)
                {
                    perror("dup2");
                    exit(EXIT_FAILURE);
                }
            }

            // If not the last command, output to next pipe
            if (i != n - 1)
            {
                if (dup2(pipefds[i * 2 + 1], 1) < 0)
                {
                    perror("dup2");
                    exit(EXIT_FAILURE);
                }
            }

            // Close all pipe file descriptors
            for (int j = 0; j < 2 * (n - 1); j++)
            {
                close(pipefds[j]);
            }

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
/*
// Execute a sequence of commands
void executeSequence(char* input)
{
    char* command = strtok(input, ";");
    while (command != NULL)
    {
        char* pipePos = strrchr(input, '|');
        if (pipePos != NULL)
        {
            *pipePos = '\0';
            executeSequence(input);
            char** leftCmd = tokenize(input);
            char** rightCmd = tokenize(pipePos + 1);
            executePipe(leftCmd, rightCmd);
            free(leftCmd);
            free(rightCmd);
        }
        else
        {
	    char** cmd = tokenize(command);
	    executeCommand(cmd);// executeCommand separately for string with pipes
	    free(cmd);
        }
	command = strtok(NULL, ";");
    }

}
*/
/*
// Main function to execute a sequence of commands
void executeSequence(char* input)
{
    char* pipePos = strrchr(input, '|');  // Search for the last occurrence of '|'
    if (pipePos != NULL)
    {
        *pipePos = '\0';
        char** leftCmd = tokenize(input);
        char** rightCmd = tokenize(pipePos + 1);
        executePipe(leftCmd, rightCmd);
        free(leftCmd);
        free(rightCmd);
    }
    else
    {
        char** cmd = tokenize(input);
        executeCommand(cmd);
        free(cmd);
    }
}
*/
/*
// Execute a sequence of commands
void executeSequence(char* input)
{
    char* command = strtok(input, ";");
    while (command != NULL)
    {
        char* pipePos = strchr(command, '|');
        if (pipePos != NULL)
	{
            *pipePos = '\0';
            char** leftCmd = tokenize(command);
            char** rightCmd = tokenize(pipePos + 1);
            executePipe(leftCmd, rightCmd);
            free(leftCmd);
            free(rightCmd);
        }
	else
	{
            char** cmd = tokenize(command);
            executeCommand(cmd);
            free(cmd);
        }
        command = strtok(NULL, ";");
    }
}
*/
void executeSequence(char* input)
{
    char* command = strtok(input, ";");
    while (command != NULL)
    {
        // Count number of pipes in the command
        int pipeCount = 0;
        for (char* temp = command; *temp != '\0'; temp++)
        {
            if (*temp == '|') pipeCount++;
        }

        if (pipeCount > 0)
        {
            // Tokenize command by pipes
            char** commands = malloc((pipeCount + 2) * sizeof(char*));
            int i = 0;
            char* pipeToken = strtok(command, "|");
            while (pipeToken != NULL)
            {
                commands[i++] = pipeToken;
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
            char** cmd = tokenize(command);
            executeCommand(cmd);
            free(cmd);
        }
        command = strtok(NULL, ";");
    }
}

void handle_sigint(int sig)
{
	printf("\n");
	rl_on_new_line();
	rl_redisplay();
}

// Main loop
int main() {
    char *input;
    signal(SIGINT, handle_sigint);
    signal(SIGQUIT, SIG_IGN);
    while (1) {
        input = readline("Bash me up$: ");
	if (input == NULL)
	{
		printf("exit\n");
		break;
	}
	add_history(input);
        executeSequence(input);
	free(input);
    }
    return 0;
}
