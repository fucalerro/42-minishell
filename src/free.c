#include "minishell.h"
void free_2starchar(char **strstr)
{
	int i;
	i = 0;
	if(!strstr || !*strstr)
		return;
	while(strstr[i])
		free(strstr[i++]);
	free(strstr);
}
