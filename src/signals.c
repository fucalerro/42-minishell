#include "minishell.h"

void sigint_handler(int sig)
{
	(void) sig;
	printf("\n");
}

void sigquit_handler(int sig) {
	printf("Quit: %i\n", sig);
}
