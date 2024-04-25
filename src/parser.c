#include "minishell.h"

void all_quotes_remover_loop(char *string, char **token, int is_in_quote)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (string[i])
	{
		if (!is_in_quote && !is_quote(string[i]))
			(*token)[j++] = string[i];
		else if (is_in_quote)
		{
			if (string[i] != is_in_quote)
				(*token)[j++] = string[i];
		}
		else if (is_quote(string[i]))
		{
			if (!is_in_quote)
				is_in_quote = string[i];
			else
				is_in_quote = 0;
		}
		i++;
	}
	(*token)[j] = 0;
}

char	*all_quotes_remover(char *string)
{
	char	*token;
	int		is_in_quote;

	is_in_quote = 0;
	token = malloc(sizeof(char) * (ft_strlen(string) + 1));
	if (!token)
		return (0);
	all_quotes_remover_loop(string, &token, is_in_quote);
	return (token);
}

char	*around_quotes_remover(char *string)
{
	char	*res;
	int		i;

	if (!is_quote(string[0]))
		return (ft_strdup(string)); //need protection !
	res = malloc(sizeof(char) * (ft_strlen(string) + 1));
	if (!res)
		return (0);
	i = 0;
	while (string[i])
	{
		res[i] = string[i + 1];
		i++;
	}
	res[i - 2] = 0;
	return (res);
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
	cmd = palloc(cmd_len, sizeof(char *)); //to protect
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
	lst_append(lst, T_HEREDOC, NULL, NULL, tmp);
	free(tmp);
}

void	parse_cmd(t_tokens **tokens, t_node **lst, int *i, int *arg_count)
{
	char **consolidated_cmd;
	int	 index;

	index = *i;

	consolidated_cmd = consolidate_cmd(tokens, index, arg_count);
	lst_append(lst, T_CMD, NULL, consolidated_cmd, NULL);
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
			lst_append(&lst, T_PIPE, NULL, NULL, NULL);
		else if (!ft_strcmp(tok[i]->tok, ">") && !tok[i]->quote && i + 1 < tc)
			lst_append(&lst, T_OUTFILE, tok[i++ + 1]->tok, NULL, NULL);
		else if (!ft_strcmp(tok[i]->tok, "<") && i + 1 < tc && !tok[i]->quote)
			lst_append(&lst, T_INFILE, tok[i++ + 1]->tok, NULL, NULL);
		else if (!ft_strcmp(tok[i]->tok, ">>") && i + 1 < tc && !tok[i]->quote)
			lst_append(&lst, T_OUTFILE_APPEND, tok[i++ + 1]->tok, NULL, NULL);
		else if (!ft_strcmp(tok[i]->tok, "<<") && i + 1 < tc && !tok[i]->quote)
			parse_heredoc(tok[i++ + 1]->tok, &lst);
		else
			parse_cmd(tok, &lst, &i, &arg_count);
	}
	return (lst);
}
