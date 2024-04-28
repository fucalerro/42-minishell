#include "minishell.h"

void	sigint_handler(int sig)
{
	(void)sig;
	printf("\n");
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	sigint_handler_process(int sig)
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

void	sigquit_handler(int sig)
{
	printf("Quit: %i\n", sig);
}
