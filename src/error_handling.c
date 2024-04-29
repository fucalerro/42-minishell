/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lferro <lferro@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 22:12:43 by Lu-ni             #+#    #+#             */
/*   Updated: 2024/04/29 16:56:40 by lferro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	token_error(t_tokens *token, int *op_flag, int *f_op_flag)
{
	if (is_unhandled_operator(token->tok) && token->quote == UNQUOTED)
		return (errror_msg(ERR_UNEXPECTED_TOKEN, token->tok[0]));
	else if (*f_op_flag && token->quote == UNQUOTED
		&& (is_file_operator(token->tok) || is_operator(token->tok)))
		return (errror_msg(ERR_UNEXPECTED_TOKEN, token->tok[0]));
	else if (is_file_operator(token->tok))
		*f_op_flag = true;
	else
		*f_op_flag = false;
	if (*op_flag && is_operator(token->tok) && token->quote == UNQUOTED)
		return (errror_msg(ERR_UNEXPECTED_TOKEN, token->tok[0]));
	else if (!is_operator(token->tok))
		*op_flag = false;
	else
		*op_flag = true;
	return (0);
}

int	parsing_error(t_tokens **tokens)
{
	int	i;
	int	op_flag;
	int	f_op_flag;
	int	result;

	i = -1;
	op_flag = true;
	f_op_flag = false;
	while (tokens[++i])
	{
		result = token_error(tokens[i], &op_flag, &f_op_flag);
		if (result != 0)
			return (result);
	}
if ((is_operator(tokens[i - 1]->tok) || is_file_operator(tokens[i - 1]->tok)) && tokens[i - 1]->quote == UNQUOTED)
		return (errror_msg(ERR_UNEXPECTED_TOKEN, tokens[i - 1]->tok[0]));
	return (0);
}
