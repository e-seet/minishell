/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clearscreen.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aadenan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 16:06:26 by aadenan           #+#    #+#             */
/*   Updated: 2024/05/09 14:35:46 by aadenan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
//Draft function
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>

void ft_clear_screen()
{
    // Clear the readline line buffer
    rl_replace_line("", 0);
    // Move cursor to the beginning of the line
    //rl_point = 0;
    // Clear the terminal screen
    printf("\033[2J\033[H");
    //fflush(stdout); // Flush the output buffer to ensure screen is cleared immediately
}

int main()
{
    char* str = readline("Enter command: ");

    if (str != NULL)
    {
        if (strcmp(str, "clear") == 0)
            clear_screen();
        free(str); // Free the memory allocated by readline
    }
    return 0;
}
