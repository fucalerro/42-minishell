#include "minishell.h"


int	is_operator(char *token)
{
	if (ft_strcmp(token, "|") == 0)
		return (1);
	return (0);
}

int	is_file_operator(char *token)
{
	if (ft_strcmp(token, "<") == 0)
		return (1);
	if (ft_strcmp(token, ">") == 0)
		return (1);
	if (ft_strcmp(token, ">>") == 0)
		return (1);
	if (ft_strcmp(token, "<<") == 0)
		return (1);
	return (0);
}

int	is_unhandled_operator(char *tokens)
{
	if (tokens[0] == '(' || tokens[0] == ')' || tokens[0] == '&')
		return (1);
	return (0);
}
