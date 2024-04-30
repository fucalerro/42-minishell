/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lferro <lferro@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 22:12:43 by Lu-ni             #+#    #+#             */
/*   Updated: 2024/04/30 15:42:42 by lferro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



char *handle_single_quote(char *token, int *i)
{
	int k;
	char *res;

	k = *i;
	while (token[k] && token[k] != '\'')
		k++;
	res = ft_substr(token, *i - 1, (k - *i) + 2);
	*i = k + 1;
	return (res);
}




char	*handle_out_of_quotes(char *token, int *i)
{
	int k;
	char *res;

	k = *i;
	while (token[k] && token[k] != '$')
		k++;
	res = ft_substr(token, *i, k - *i);
	*i = k;
	return (res);
}

void handle_dollar_in_db_quotes(char *token, char **env, char **res, t_nbr *nbr)
{
	char *var_name;
	char *var_value;


	var_name = get_var_name(&token[nbr->i]);
	var_value = get_var_value(var_name, nbr->status, env);
	if (var_value)
	{
		if (!ft_strcmp(var_value, "$"))
			(nbr->i)--;
		res[(nbr->j)++] = ft_strdup(var_value);
		free(var_value);
	}
	nbr->i += ft_strlen(var_name) + 1;
	if (token[nbr->i] == '\'' && is_in_quotes(token, nbr->i) != DOUBLE_QUOTE)
		(nbr->i)++;
	free(var_name);

	// return (res);
}

char	*expand_token(char *token, int status, char **env)
{
	int		nbr_of_vars;
	t_nbr	nbr;
	char	**res;
	char	*new_token;

	nbr_of_vars = get_nbr_of_vars(token);
	res = palloc((nbr_of_vars * 3 + 1), sizeof(char *));
	nbr.i = 0;
	nbr.j = 0;
	nbr.status = status;
	while (token[nbr.i])
	{
		if (is_in_quotes(token, nbr.i) == SINGLE_QUOTE)
			res[nbr.j++] = handle_single_quote(token, &nbr.i);
		else if (token[nbr.i] == '$' && is_in_quotes(token, nbr.i) != SINGLE_QUOTE)
			handle_dollar_in_db_quotes(token, env, res, &nbr);
		else
			res[nbr.j++] = handle_out_of_quotes(token, &nbr.i);
	}
	res[nbr.j] = 0;
	new_token = flatten_2d_array(res);
	free_2starchar(res);
	return (new_token);
}


// char	*expand_token(char *token, int status, char **env)
// {
// 	char	*var_value;
// 	char	*var_name;
// 	int		nbr_of_vars;
// 	int		i;
// 	int		j;
// 	int		k;
// 	char	**res;
// 	char	*new_token;

// 	nbr_of_vars = get_nbr_of_vars(token);
// 	res = palloc((nbr_of_vars * 3 + 1), sizeof(char *));
// 	j = 0;
// 	i = 0;
// 	while (token[i])
// 	{
// 		if (is_in_quotes(token, i) == SINGLE_QUOTE)
// 		{
// 			// res[j++] = handle_single_quote(token, &i);
// 			k = i;
// 			while (token[k] && token[k] != '\'')
// 				k++;
// 			printf("calcs: %d, %d\n", i - 1, (k - i) + 2);
// 			res[j++] = ft_substr(token, i - 1, (k - i) + 2);
// 			printf("res");
// 			i = k + 1;
// 		}
// 		else if (token[i] == '$' && is_in_quotes(token, i) != SINGLE_QUOTE)
// 		{
// 			var_name = get_var_name(&token[i]);
// 			var_value = get_var_value(var_name, status, env);
// 			if (var_value)
// 			{
// 				if (!ft_strcmp(var_value, "$"))
// 					(i)--;
// 			*res = ft_strdup(var_value);
// 			free(var_value);
// 			}
// 			if (token[i] == '\'' && is_in_quotes(token, i) != DOUBLE_QUOTE)
// 				(i)++;
// 			free(var_name);
// 		}
// 			// handle_dollar_in_db_quotes(token, &i, status, env, &res[j++]);
// 		else
// 		{
// 			k = i;
// 			while (token[k] && token[k] != '$')
// 				k++;
// 			res[j++] = ft_substr(token, i, k - i);
// 			i = k;
// 		}
// 	}
// 	res[j] = 0;
// 	new_token = flatten_2d_array(res);
// 	while (res[j])
// 		free(res[j++]);
// 	free(res);
// 	return (new_token);
// }
