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
