/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lferro <lferro@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 22:12:43 by Lu-ni             #+#    #+#             */
/*   Updated: 2024/04/30 21:21:29 by lferro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	all_quotes_remover_loop(char *string, char **token, char prev_quote)
{
	int		i;
	int		j;
	int		is_in_quote;

	i = -1;
	j = 0;
	is_in_quote = false;
	while (string[++i])
	{
		if (is_quote(string[i]))
		{
			if (!is_in_quote)
				prev_quote = string[i];
			if (!is_in_quote)
				is_in_quote = true;
			else if (prev_quote != string[i])
				(*token)[j++] = string[i];
			else if (prev_quote == string[i])
				is_in_quote = false;
		}
		else
			(*token)[j++] = string[i];
	}
	(*token)[j] = 0;
}

char	**consolidate_cmd(t_tokens **tokens, int i, int *arg_count)
{
	char	**cmd;
	int		j;
	int		cmd_len;

	j = i;
	cmd_len = 0;
	while (tokens[j] && (!is_metachar(tokens[j]->tok[0])
			|| (is_metachar(tokens[j]->tok[0]) && tokens[j]->quote)))
	{
		cmd_len++;
		j++;
	}
	cmd = palloc(cmd_len, sizeof(char *));
	j = 0;
	while (tokens[i] && (!is_metachar(tokens[i]->tok[0])
			|| (is_metachar(tokens[i]->tok[0]) && tokens[i]->quote)))
	{
		cmd[j++] = tokens[i++]->tok;
	}
	*arg_count = cmd_len - 1;
	cmd[j] = 0;
	return (cmd);
}

void	parse_heredoc(char *token, t_node **lst)
{
	char	*tmp;

	tmp = around_quotes_remover(token);
	lst_append(lst, T_HEREDOC, NULL, merge_str(NULL, tmp));
	free(tmp);
}

void	parse_cmd(t_tokens **tokens, t_node **lst, int *i, int *arg_count)
{
	char	**consolidated_cmd;
	int		index;

	index = *i;
	consolidated_cmd = consolidate_cmd(tokens, index, arg_count);
	lst_append(lst, T_CMD, consolidated_cmd, merge_str(NULL, NULL));
	free(consolidated_cmd);
	*i += *arg_count;
}

t_node	*parser(t_tokens **tok)
{
	t_node	*lst;
	int		i;
	int		tc;
	int		arg_count;

	lst = NULL;
	tc = get_elem_count_tok(tok);
	i = -1;
	while (tok[++i])
	{
		if (!ft_strncmp(tok[i]->tok, "|", 1) && !tok[i]->quote)
			lst_append(&lst, T_PIPE, NULL, merge_str(NULL, NULL));
		else if (!ft_strcmp(tok[i]->tok, ">") && !tok[i]->quote && i + 1 < tc)
			lst_append(&lst, T_OUTFILE, 0, merge_str(tok[i++ + 1]->tok, 0));
		else if (!ft_strcmp(tok[i]->tok, "<") && i + 1 < tc && !tok[i]->quote)
			lst_append(&lst, T_INFILE, 0, merge_str(tok[i++ + 1]->tok, 0));
		else if (!ft_strcmp(tok[i]->tok, ">>") && i + 1 < tc && !tok[i]->quote)
			lst_append(&lst, T_OUTFILE_APPEND, NULL, merge_str(tok[i++
					+ 1]->tok, NULL));
		else if (!ft_strcmp(tok[i]->tok, "<<") && i + 1 < tc && !tok[i]->quote)
			parse_heredoc(tok[i++ + 1]->tok, &lst);
		else
			parse_cmd(tok, &lst, &i, &arg_count);
	}
	return (lst);
}
