#include "minishell.h"
char  **free_2starchar(char **strstr)
{
	int i;
	i = 0;
	if(!strstr || !*strstr)
		return (NULL);
	while(strstr[i])
		free(strstr[i++]);
	free(strstr);
	strstr = NULL;
	return(NULL);
}
