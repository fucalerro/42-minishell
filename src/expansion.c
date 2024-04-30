/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lferro <lferro@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 22:12:43 by Lu-ni             #+#    #+#             */
/*   Updated: 2024/04/30 20:47:26 by lferro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_single_quotes(char *token, int *i, char **res, int *j)
{
	int	k;
	int	ii;

	k = *i;
	while (token[k] && token[k] != '\'')
		k++;
	ii = k + 1;
	while (token[ii] && token[ii] != '\'')
		ii++;
	res[*j] = ft_substr(token, k, ii + 1 - k);
	*j = *j + 1;
	*i = ii + 1;
}

void	handle_others(char *token, int *i, char **res, int *j)
{
	int	k;

	k = *i;
	while (token[k] && (token[k + 1] != '$'))
		k++;
	res[*j] = ft_substr(token, *i, k - *i + 1);
	*i = k + 1;
	*j = *j + 1;
}

void	handle_expansion(char *token, char **res, char **env, int *nbr)
{
	char	*var_value;
	char	*var_name;

	var_name = get_var_name(&token[nbr[0]]);
	var_value = get_var_value(var_name, nbr[2], env);
	if (var_value)
	{
		if (!ft_strcmp(var_value, "$"))
			(nbr[0])--;
		res[(nbr[1])++] = ft_strdup(var_value);
		free(var_value);
	}
	nbr[0] += ft_strlen(var_name) + 1;
	if (token[nbr[0]] == '\'' && is_in_quotes(token, nbr[0]) != DOUBLE_QUOTE)
		(nbr[0])++;
	free(var_name);
}

char	*expand_token(char *token, int status, char **env)
{
	int		nbr_of_vars;
	int		*i;
	char	**res;
	char	*new_token;

	i = palloc(3, sizeof(int));
	i[0] = 0;
	i[1] = 0;
	i[2] = status;
	nbr_of_vars = get_nbr_of_vars(token);
	res = palloc((nbr_of_vars * 5 + 1), sizeof(char *));
	while (token[i[0]])
	{
		if (is_in_quotes(token, i[0]) == SINGLE_QUOTE)
			handle_single_quotes(token, &i[0], res, &i[1]);
		else if ((token[i[0]] == '$') && is_in_quotes(token,
				i[0]) != SINGLE_QUOTE)
			handle_expansion(token, res, env, &i[0]);
		else
			handle_others(token, &i[0], res, &i[1]);
	}
	res[i[1]] = 0;
	new_token = flatten_2d_array(res);
	free_2starchar(res);
	return (new_token);
}
