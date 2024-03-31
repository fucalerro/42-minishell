#include "minishell.h"

void sigint_handler(int sig)
{
	(void) sig;

	char *cwd = builtin_pwd();
	char *line;

	line = ft_strjoin(cwd, "🌻 ");

	printf("\n");
	printf("%s", line);

}

void sigquit_handler(int sig) {
	printf("Quit: %i\n", sig);
}
