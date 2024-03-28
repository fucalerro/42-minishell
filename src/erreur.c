#include "minishell.h"
void debug_print(char * msg)
{
	char *color = COLOR_CYAN;
	if (MINI_DEBUG_MSG)
	{
		printf("%s%s\n",color,msg);
		printf("\033[0m");
		fflush(stdout);
	}
}
