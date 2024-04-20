#include "minishell.h"

// prints error message
int	errror_msg(int type, int c)
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
	return (1);
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
	unsigned long		j;
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



int	error_token(t_tokens *token)
{
	int	op_flag;
	int	fileop_flag;

	op_flag = true;
	fileop_flag = false;
	if (is_unhandled_operator(token->tok) && token->quote == UNQUOTED)
		return (errror_msg(ERR_UNEXPECTED_TOKEN, token->tok[0]));
	else if (fileop_flag && token->quote == UNQUOTED 
		&& (is_file_operator(token->tok) || is_operator(token->tok)))
		return (errror_msg(ERR_UNEXPECTED_TOKEN, token->tok[0]));
	else if (is_file_operator(token->tok))
		fileop_flag = true;
	else
		fileop_flag = false;
	if (op_flag && is_operator(token->tok) && token->quote == UNQUOTED)
		return (errror_msg(ERR_UNEXPECTED_TOKEN, token->tok[0]));
	else if (!is_operator(token->tok))
		op_flag = false;
	else
		op_flag = true;
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

	op_flag = true;
	fileop_flag = false;
	i = -1;
	while (tokens[++i])
	{
		// error_token(tokens[i]);


		if (is_unhandled_operator(tokens[i]->tok) && tokens[i]->quote == UNQUOTED)
			return (errror_msg(ERR_UNEXPECTED_TOKEN, tokens[i]->tok[0]));
		else if (fileop_flag && tokens[i]->quote == UNQUOTED && (is_file_operator(tokens[i]->tok) || is_operator(tokens[i]->tok)))
			return (errror_msg(ERR_UNEXPECTED_TOKEN, tokens[i]->tok[0]));
		else if (is_file_operator(tokens[i]->tok))
			fileop_flag = true;
		else
			fileop_flag = false;
		if (op_flag && is_operator(tokens[i]->tok) && tokens[i]->quote == UNQUOTED)
			return (errror_msg(ERR_UNEXPECTED_TOKEN, tokens[i]->tok[0]));
		else if (!is_operator(tokens[i]->tok))
			op_flag = false;
		else
			op_flag = true;
	}
	if (tokens[i] && (is_operator(tokens[i - 1]->tok) || is_file_operator(tokens[i - 1]->tok)) && tokens[i - 1]->quote == UNQUOTED)
		return (errror_msg(ERR_UNEXPECTED_TOKEN, tokens[i - 1]->tok[0]));	
	return (0);
}
