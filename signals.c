/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aadenan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 19:11:11 by aadenan           #+#    #+#             */
/*   Updated: 2024/04/29 15:14:52 by aadenan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
Just a summary of signals
Need to edit and remove illegal stuff
Probably need to add smth else
*/

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

void handle_sigint(int sig)
{
    printf("\n"); // Display a new prompt on a new line
    fflush(stdout); // Flush stdout to ensure the prompt is displayed immediately
}

int main()
{
    // Register signal handlers
    signal(SIGINT, handle_sigint); // Ctrl-C
    signal(SIGQUIT, SIG_IGN); // Ctrl-\, SIG_IGN to ignore the signal
    
    printf("Shell started. Press Ctrl-D to exit.\n");

    // Loop until Ctrl-D (EOF) is pressed
    while(1)
    {
        // Read user input
        char buffer[1024];
        if(fgets(buffer, sizeof(buffer), stdin) == NULL)
	{
            // Ctrl-D (EOF) detected, exit
            printf("\nExiting shell.\n");
            break;
        }
        
        // Echo back the input
        printf("You entered: %s", buffer);
    }

    return 0;
}
