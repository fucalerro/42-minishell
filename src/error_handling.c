#include "minishell.h"

// prints error message
void	errror_msg(int type, int c)
{
	printf("minishell: ");
	if (type == ERR_UNEXPECTED_TOKEN || type == ERR_UNCLOSED_QUOTE)
	{
		printf("syntax error: ");
		if (type == ERR_UNEXPECTED_TOKEN)
		{
			printf("unexpected token near '%c'\n", c);
		}
		else if (type == ERR_UNCLOSED_QUOTE)
		{
			printf("unclosed quote\n");
		}
	}
}

// check if file exists and if it is readable.
int	access_infile(char *filepath)
{
	if (access(filepath, F_OK) == -1)
	{
		printf("minishell: %s: No such file or directory\n", filepath);
		return (1);
	}
	if (access(filepath, R_OK) == -1)
	{
		printf("minishell: %s: Permission denied\n", filepath);
		return (1);
	}
	return (0);
}

// check if file is a directory, if it exists and if it is writable.
// if file doesnt exist, check if current directory is writable.
int	access_outfile(const char *filename)
{
	if (open(filename, O_DIRECTORY) >= 0)
	{
		printf("minishell: %s: Is a directory\n", filename);
		return (1);
	}
	if (access(filename, F_OK) == -1)
	{
		if (access(".", W_OK) == -1)
		{
			printf("minishell: %s: Permission denied\n", filename);
			return (1);
		}
	}
	else if (access(filename, W_OK) == -1)
	{
		printf("minishell: %s: Permission denied\n", filename);
		return (1);
	}
	return (0);
}

// check if token is an operator
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
	int		i;
	int		j;
	char *unhandled[] = { "(", ")", "&" };

	j = 0;
	while (j < sizeof(unhandled) / sizeof(unhandled[0]))
	{
		if (ft_strcmp(tokens, unhandled[j]) == 0)
			return (1);
		j++;
	}
	return (0);
}

/**
 * @brief return 1 in case of error. if starting or ending with
 * operator, return error.
 * If 2 or more operators are next to each other, return error.
 *
 * @param tokens
 * @return int
 */
int	parsing_error(t_tokens **tokens)
{
	int	i;
	int	op_flag;
	int	fileop_flag;

	i = -1;
	op_flag = true;
	fileop_flag = false;
	while (tokens[++i])
	{
		if (is_unhandled_operator(tokens[i]->token)
			&& tokens[i]->quoted == UNQUOTED)
		{
			errror_msg(ERR_UNEXPECTED_TOKEN, tokens[i]->token[0]);
			return (1);
		}
		else if (fileop_flag && tokens[i]->quoted == UNQUOTED
			&& (is_file_operator(tokens[i]->token)
				|| is_operator(tokens[i]->token)))
		{
			errror_msg(ERR_UNEXPECTED_TOKEN, tokens[i]->token[0]);
			return (1);
		}
		else if (is_file_operator(tokens[i]->token))
			fileop_flag = true;
		else
			fileop_flag = false;
		if (op_flag && is_operator(tokens[i]->token)
			&& tokens[i]->quoted == UNQUOTED)
		{
			errror_msg(ERR_UNEXPECTED_TOKEN, tokens[i]->token[0]);
			return (1);
		}
		else if (!is_operator(tokens[i]->token))
			op_flag = false;
		else
			op_flag = true;
	}
	if (tokens[i] && (is_operator(tokens[i - 1]->token)
			|| is_file_operator(tokens[i - 1]->token)) && tokens[i
		- 1]->quoted == UNQUOTED)
	{
		errror_msg(ERR_UNEXPECTED_TOKEN, tokens[i - 1]->token[0]);
		return (1);
	}
	return (0);
}
