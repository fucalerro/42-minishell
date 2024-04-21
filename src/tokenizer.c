#include "minishell.h"

char *op_tokenzier_loop(char *string, int *i, int *op_flag, int *start)
{
	char *token;

	if (is_double_op(string, *i) && !*op_flag && !is_in_quotes(string, *i))
	{
		*op_flag = true;
		token = ft_substr(string, *i, 2);
		*i += 2;
	}
	else if (is_single_op(string, *i)
		&& !*op_flag && !is_in_quotes(string, *i))
	{
		*op_flag = true;
		token = ft_substr(string, (*i)++, 1);
	}
	else
	{
		*start = *i;
		while (string[*i] && ((!is_double_op(string, *i)
			&& !is_single_op(string, *i)) || is_in_quotes(string, *i)))
			(*i)++;
		if (*i > *start)
			token = ft_substr(string, *start, *i - *start);
		*op_flag = false;
	}
	return (token);
}

/**
 * @brief convert a string into a table of Operator and Word tokens
 * @param string input string
 * @return char** table of tokens
 */
char	**op_tokenizer(char *string)
{
	char	**res;
	int		op_flag;
	int		i;
	int		j;
	int		start;

	res = palloc((count_op(string) + 1) * 2, sizeof(char *));

	i = 0;
	j = 0;
	op_flag = 0;
	while (string[i])
		res[j++] = op_tokenzier_loop(string, &i, &op_flag, &start);
	res[j] = 0;
	return (res);
}

/**
 * @brief convert a string into a table of tokens based on Space delimiter
 *
 * @param string
 * @param c
 * @return char**
 */
char	**sp_tokenizer(char *string, char c)
{
	size_t	i;
	size_t	j;
	int		index;
	char	**res;

	i = -1;
	j = 0;
	index = -1;
	res = malloc((wordcounter(string, c) + 1) * sizeof(char *));
	if (res == 0)
		return (0);
	while (++i <= ft_strlen(string))
	{
		if (string[i] != c && index < 0)
			index = i;
		else if ((string[i] == c || i == ft_strlen(string)) && index >= 0
			&& !is_in_quotes(string, i))
		{
			res[j++] = wordmaker(string, index, i);
			index = -1;
		}
	}
	res[j] = 0;
	return (res);
}

char	*set_is_in_quotes(char *token)
{
	char	*res;
	int		i;

	res = malloc(sizeof(char) * (ft_strlen(token) + 1));
	if (!res)
		return (0);
	i = 0;
	while (token[i])
	{
		if (is_in_quotes(token, i) == SINGLE_QUOTE)
			res[i] = 'S';
		else if (is_in_quotes(token, i) == DOUBLE_QUOTE)
			res[i] = 'D';
		else
			res[i] = 'N';
		i++;
	}
	return (res);
}

t_tokens	**quotes_tokenizer(char **tokens)
{
	int			i;
	t_tokens	**res;
	char		*temp;

	res = malloc(sizeof(t_tokens *) * (count_arr_elems(tokens) + 1));
	if (!res)
		return (0);
	i = 0;
	while (tokens[i])
	{
		res[i] = malloc(sizeof(t_tokens));
		if (!res[i])
			return (0);
		res[i]->quote = is_quote(tokens[i][0]);
		temp = all_quotes_remover(tokens[i]);
		res[i]->tok = ft_strdup(temp);
		free(temp);
		i++;
	}
	res[i] = 0;
	return (res);
}



t_tokens	**tokenizer(char *string, int status, char **env)
{
	char		*normalized_input;
	char		**sp_tokenized;
	char		***op_tokenized;
	int			i;
	t_tokens	**tokens;
	char		**tokenized;

	if (is_quotes_opened(string))
		return (0);
	normalized_input = input_normalizer(string);
	sp_tokenized = sp_tokenizer(normalized_input, ' ');
	expand_env_vars(sp_tokenized, status, env);
	op_tokenized = palloc(count_arr_elems(sp_tokenized), sizeof(char **));
	i = -1;
	while (sp_tokenized[++i])
		op_tokenized[i] = op_tokenizer(sp_tokenized[i]);
	op_tokenized[i] = 0;
	tokenized = flatten_3d_array(op_tokenized);
	tokens = quotes_tokenizer(tokenized);
	free(normalized_input);
	free_string_array(sp_tokenized);
	free_string_array(tokenized);
	return (tokens);
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
