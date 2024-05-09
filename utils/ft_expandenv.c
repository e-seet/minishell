/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expandenv.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aadenan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 14:58:51 by aadenan           #+#    #+#             */
/*   Updated: 2024/05/09 15:37:07 by aadenan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/*
#include <stdio.h>
#include <stdlib.h> // for getenv, malloc, free
#include <string.h>

char* expand_env_variable(const char* variable_name)
{	
    char* value = getenv(variable_name); // Get the value of the environment variable

    if (value == NULL) {
        // Variable not found
        return NULL;
    }

    // Allocate memory for the expanded variable
    char* expanded_variable = (char*)malloc(strlen(value) + 1);
    if (expanded_variable == NULL) {
        // Memory allocation failed
        return NULL;
    }

    // Copy the value into the newly allocated memory
    strcpy(expanded_variable, value);

    return expanded_variable;
}

int main(int argc, char **argv) {
    //const char* variable_name = "HOME";
    if(argc == 2)
    {
        char* expanded_value = expand_env_variable(argv[1]);

        if (expanded_value != NULL) {
            printf("%s=%s\n", argv[1], expanded_value);
            free(expanded_value); // Remember to free the allocated memory
        } else {
            printf("Environment variable not found.\n");
        }
    }
    return 0;
}
*/
// Draft function
#include <stdio.h>
#include <stdlib.h> // for getenv

int main(int argc, char **argv)
{
    const char* variable_name;
    char* value;

    if(argc == 2)
    {
	variable_name = argv[1];
	value = getenv(variable_name);
        if (value != NULL) {
            printf("%s\n", value);
        } else {
            printf("Environment variable not found.\n");
        }
    }
    return 0;
}
