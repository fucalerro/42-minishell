/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Lu-ni <lucas.nicollier@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 22:12:43 by Lu-ni             #+#    #+#             */
/*   Updated: 2024/04/28 22:12:43 by Lu-ni            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sigint_handler(int sig)
{
	(void)sig;
	printf("\n");
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	sigint_handler_p(int sig)
{
	(void)sig;
	printf("\n");
	rl_on_new_line();
}

void	sigint_handler_heredoc(int sig)
{
	(void)sig;
	printf("\n");
	rl_on_new_line();
	exit(1);
}

void sigquit_handler(int signo)
{
	(void) signo;
    rl_on_new_line();      // Move to a new line
//    rl_replace_line("", 0);  // Clear the current line
    rl_redisplay();        // Redisplay the line
}

void sigquit_handler_p(int signo)
{
	printf("Quit: %i\n", signo);
    rl_on_new_line();      // Move to a new line
//    rl_replace_line("", 0);  // Clear the current line
}
