#include "minishell.h"

int	is_metachar(char c)
{
	if (c == '|' || c == '<' || c == '>')
		return (1);
	return (0);
}

/**
 * @brief check if a character in a string is within single or double quotes.
 *
 * @param input string
 * @param index character index to check
 * @return 1 if within quotes,
	0 if not. Returns 1 even if the quote is not closed.
 */
int	is_in_quotes(char *input, int index)
{
	int	in_double_quote;
	int	in_single_quote;
	int	i;

	i = -1;
	in_double_quote = false;
	in_single_quote = false;
	while (input[++i] && i <= index)
	{
		if (input[i] == '\'' && !in_double_quote)
			in_single_quote = !in_single_quote;
		else if (input[i] == '\"' && !in_single_quote)
			in_double_quote = !in_double_quote;
		if (i == index)
			break ;		
	}
	if (in_single_quote)
		return (SINGLE_QUOTE);
	if (in_double_quote)
		return (DOUBLE_QUOTE);
	else
		return (0);
}



void normalize_loop(char *input, int i, char **output)
{
	int	j;
	int	flag;

	j = 0;
	while (input[i])
	{
		while (is_in_quotes(input, i) > 0 && input[i])
			(*output)[j++] = input[i++];
		if (ft_isspace(input[i]) && ft_isspace(input[i]) != ' ')
			(*output)[j++] = ' ';
		else if (ft_isspace(input[i]))
		{
			if (flag && input[i + 1] != 0 && !ft_isspace(input[i + 1]))
				(*output)[j++] = ' ';
		}
		else
		{
			(*output)[j++] = input[i];
			flag = 1;
		}
		i++;
	}
	(*output)[j] = 0;
}

/**
 * @brief Removes extra spaces and replaces all sort of tabs for spaces.
 * Do not change the portion that are in single or double quotes.
 *
 * @param input
 * @return char*
 */
char	*input_normalizer(char *input)
{
	int		i;
	char	*output;

	output = malloc(sizeof(char) * (ft_strlen(input) + 1));
	if (!output)
		return (0);
	i = 0;
	while (ft_isspace(input[i]) && input[i])
	{
		if (ft_isspace(input[i]) != 32)
			output[i] = ' ';
		i++;
	}
	normalize_loop(input, i, &output);
	return (output);
}

/**
 * @brief Count the number of words in a string. Words are separated by spaces.
 * Words within single or double quotes are considered as one word.
 *
 * @param input
 * @return int
 */
int	word_counter_quotes(char *input)
{
	int	i;
	int	quote_count;
	int	in_quote;
	int	prev_in_quote;

	in_quote = false;
	prev_in_quote = false;
	quote_count = 0;
	i = 0;
	if (input[i] == '\'' || input[i] == '\"')
		quote_count--;
	while (input[i])
	{
		in_quote = is_in_quotes(input, i);
		if (in_quote != prev_in_quote)
			quote_count++;
		prev_in_quote = in_quote;
		i++;
	}
	if (input[--i] == '\'' || input[i] == '\"')
		quote_count--;
	return (quote_count + 1);
}

int	is_quote(char c)
{
	if (c == '\'')
		return (SINGLE_QUOTE);
	if (c == '\"')
		return (DOUBLE_QUOTE);
	else
		return (0);
}

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
		return (ft_strdup(string));
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

void *palloc(int size, int elem_size)
{
	void	*res;

	res = malloc(elem_size * (size + 1));
	if (!res)
		return (NULL);
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
	cmd = palloc(cmd_len, sizeof(char *));
	j = 0;
	while (tokens[i] && (!is_metachar(tokens[i]->tok[0])
			|| (is_metachar(tokens[i]->tok[0]) && tokens[i]->quote)))
	{
		cmd[j++] = ft_strdup(tokens[i]->tok);
		free(tokens[i++]->tok);
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
