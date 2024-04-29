/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lferro <lferro@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 22:12:43 by Lu-ni             #+#    #+#             */
/*   Updated: 2024/04/29 20:32:47 by lferro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <termios.h>

void set_signal(int primary) {
    struct termios term;
    struct sigaction sa_quit;

    if (primary == 0)
	{
		signal(SIGINT, sigint_handler);  // Setup for SIGINT remains the same
        sa_quit.sa_handler = sigquit_handler;  // Use primary handler
    }
	else
	{
		signal(SIGINT, sigint_handler_p);  // Setup for SIGINT remains the same
        sa_quit.sa_handler = sigquit_handler_p;  // Use secondary handler
    }
    sigemptyset(&sa_quit.sa_mask);
    sa_quit.sa_flags = 0; // No SA_RESTART, handlers are invoked each time
    sigaction(SIGQUIT, &sa_quit, NULL);

    // Terminal settings to suppress echo of control characters
    tcgetattr(STDIN_FILENO, &term);
    term.c_lflag &= ~ECHOCTL;
    tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

