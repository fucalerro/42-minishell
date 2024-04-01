#include "minishell.h"

void sigint_handler(int sig)
{
	(void) sig;

	// char *cwd = builtin_pwd();
	// char *line;

	// line = ft_strjoin(cwd, "🌻 ");

	printf("\n");
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void sigquit_handler(int sig) {
	printf("Quit: %i\n", sig);
}
