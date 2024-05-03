/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rm_empty_str.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aadenan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 15:03:43 by aadenan           #+#    #+#             */
/*   Updated: 2024/05/03 15:13:16 by aadenan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// To check & cleanup once confirmed...
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int count_non_empty_argv(int argc, char **argv)
{
    int non_empty_count = 0;

    for (int i = 1; i < argc; i++)
    {
        if (strcmp(argv[i], "") != 0)
            non_empty_count++;
    }
    return non_empty_count;
}

void copy_over(char **argv, char **non_empty_argv, int argc, int non_empty_count)
{
    // Copy non-empty strings
    int j = 0;
    for (int i = 1; i < argc; i++)
    {
        if (strcmp(argv[i], "") != 0)
            non_empty_argv[j++] = strdup(argv[i]);
    }
    non_empty_argv[non_empty_count] = NULL; // Null-terminate the array
}

// Replace main with the actual function...
// Example...remove_empty(char **str)?
// What is the return value?
// What are the arguments?
int main(int argc, char **argv)
{
    int non_empty_count;
    char **non_empty_argv;

    non_empty_count = count_non_empty_argv(argc, argv);
    // Allocate memory for non-empty strings
    non_empty_argv = (char **)malloc((non_empty_count + 1) * sizeof(char *));
    if (non_empty_argv == NULL)
    {
        fprintf(stderr, "Memory allocation failed.\n");
        return 1;
    }
    // Duplicate the string while removing, all empty strings
    copy_over(argv, non_empty_argv, argc, non_empty_count);

    // Print non-empty strings
    printf("Non-empty arguments:\n");
    for (int i = 0; i < non_empty_count; i++)
    {
        printf("%s\n", non_empty_argv[i]);
    }

    // Free memory
    for (int i = 0; i < non_empty_count; i++)
    {
        free(non_empty_argv[i]);
    }
    free(non_empty_argv);

    return 0;
}

