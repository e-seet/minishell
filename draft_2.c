/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draft_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aadenan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 11:08:06 by aadenan           #+#    #+#             */
/*   Updated: 2024/05/15 16:01:24 by aadenan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// For reference
// Fix env expansion
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

// Expand environment variables in a string
char* expand_variables(const char* input) {
    printf("Inside expand_variables function\n");
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
    printf("result: %s\n", result);
    return result;
}

// Tokenize input considering quotes
char** tokenize(char* input) {
    char** tokens = malloc(MAX_TOKENS * sizeof(char*));
    char* token = malloc(strlen(input) + 1);
    int i = 0, j = 0, k = 0;
    int inSingleQuote = 0, inDoubleQuote = 0;

    while (input[i] != '\0') {
        if (input[i] == '\'' && !inDoubleQuote) {
            inSingleQuote = !inSingleQuote;
        } else if (input[i] == '"' && !inSingleQuote) {
            inDoubleQuote = !inDoubleQuote;
            if (!inDoubleQuote) {
                token[j] = '\0';
                char* expanded = expand_variables(token);
                strcpy(token, expanded);
                free(expanded);
                j = strlen(token);
            }
        } else if (input[i] == ' ' && !inSingleQuote && !inDoubleQuote) {
            if (j > 0) {
                token[j] = '\0';
                tokens[k++] = strdup(token);
                j = 0;
            }
        } else {
            token[j++] = input[i];
        }
        i++;
    }

    if (j > 0) {
        token[j] = '\0';
        if (inDoubleQuote) {
            char* expanded = expand_variables(token);
            strcpy(token, expanded);
            free(expanded);
        }
        tokens[k++] = strdup(token);
    }

    tokens[k] = NULL;
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
        if(strcmp(args[idx], ">") == 0)
	    flag = 1;
	if(strcmp(args[idx], ">>") == 0)
	    flag = 1;
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
            printf("%s", args[i]);
        }
        if (!nFlag) {
            printf("\n");
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
        //printf("%s\n", cwd);
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
void executeCommand(char** command) {
    if (handleBuiltins(command) == -1) {
        return;
    }
    pid_t pid = fork();
    if (pid == 0) {
        if (handleRedirections(command) == -1) {
            exit(EXIT_FAILURE);
        }
        if (execvp(command[0], command) == -1)
	{
	    //printf("%s\n", command[0]);
            //perror("execvp failed");
            exit(EXIT_FAILURE);
	}
    } else {
        wait(NULL);
    }
}

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

// Execute a sequence of commands
void executeSequence(char* input) {
    char* command = strtok(input, ";");
    while (command != NULL) {
        char* pipePos = strchr(command, '|');
        if (pipePos != NULL) {
            *pipePos = '\0';
            char** leftCmd = tokenize(command);
            char** rightCmd = tokenize(pipePos + 1);
            executePipe(leftCmd, rightCmd);
            free(leftCmd);
            free(rightCmd);
        } else {
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
        input[strcspn(input, "\n")] = 0;  // Remove the newline character
        executeSequence(input);
	if (input)
		add_history(input);
	free(input);
    }
    return 0;
}