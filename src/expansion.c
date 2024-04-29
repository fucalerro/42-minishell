/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Lu-ni <lucas.nicollier@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 22:12:43 by Lu-ni             #+#    #+#             */
/*   Updated: 2024/04/28 22:12:43 by Lu-ni            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_var_name(char *token)
{
	char	*var_name;
	int		i;
	int		j;

	i = 1;
	j = 0;
	if (token[i] == '?')
	{
		return (ft_strdup("?"));
	}
	if (!token[i] || (!ft_isalnum(token[i]) && token[i] != '_'))
	{
		return (ft_strdup("$"));
	}
	var_name = palloc(ft_strlen(token) + 1, sizeof(char));
	if (!var_name)
		return (0);
	while (token[i] && (ft_isalnum(token[i]) || token[i] == '_'))
	{
		var_name[j++] = token[i++];
	}
	var_name[j] = 0;
	return (var_name);
}

char	*get_var_value(char *var_name, int status, char **env)
{
	char	*var_value;

	if (!ft_strcmp(var_name, "$"))
	{
		return (ft_strdup("$"));
	}
	if (!ft_strcmp("?", var_name))
		return (ft_itoa(status));
	var_value = ft_getenv(var_name, env);
	if (var_value)
		return (ft_strdup(var_value));
	return (0);
}

int	get_nbr_of_vars(char *token)
{
	int	i;
	int	nbr_of_vars;

	i = 0;
	nbr_of_vars = 0;
	while (token[i])
	{
		if (token[i] == '$' && is_in_quotes(token, i) != SINGLE_QUOTE)
			nbr_of_vars++;
		i++;
	}
	return (nbr_of_vars);
}

char	*expand_token(char *token, int status, char **env)
{
	char	*var_value;
	char	*var_name;
	int		nbr_of_vars;
	int		i;
	int		j;
	int		k;
	char	**res;
	char	*new_token;

	nbr_of_vars = get_nbr_of_vars(token);
	res = palloc((nbr_of_vars * 3 + 1), sizeof(char *));
	if (!res)
		return (0);
	j = 0;
	i = 0;
	while (token[i])
	{
		if (is_in_quotes(token, i) == SINGLE_QUOTE)
		{
			k = i;
			while (token[k] && token[k] != '\'')
				k++;
			res[j++] = ft_substr(token, i - 1, (k - i) + 2);
			i = k + 1;
		}
		else if (token[i] == '$' && is_in_quotes(token, i) != SINGLE_QUOTE)
		{
			var_name = get_var_name(&token[i]);
			var_value = get_var_value(var_name, status, env);
			if (var_value)
			{
				if (!ft_strcmp(var_value, "$"))
					i--;
				res[j++] = ft_strdup(var_value);
				free(var_value);
			}
			else
				res[j++] = ft_strdup("");
			i += ft_strlen(var_name) + 1;
			free(var_name);
		}
		else
		{
			k = i;
			while (token[k] && token[k] != '$')
				k++;
			res[j++] = ft_substr(token, i, k - i);
			i = k;
		}
	}
	res[j] = 0;
	new_token = flatten_2d_array(res);
	while (res[j])
	{
		free(res[j]);
		j++;
	}
	free(res);
	return (new_token);
}

void	expand_env_vars(char **tokens, int status, char **env)
{
	int		i;
	char	*tmp;

	i = 0;
	while (tokens[i])
	{
		if (ft_strchr(tokens[i], '$'))
		{
			tmp = expand_token(tokens[i], status, env);
			if (tmp)
			{
				tokens[i] = ft_strdup(tmp);
				free(tmp);
			}
		}
		i++;
	}
}
