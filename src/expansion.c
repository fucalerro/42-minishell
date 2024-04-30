/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lferro <lferro@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 22:12:43 by Lu-ni             #+#    #+#             */
/*   Updated: 2024/04/30 19:06:33 by lferro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
void print_res(char **res)
{
	//printf("vvvv\n");
	int i = 0;
	while (res[i])
	{
		// printf("res[%d]: >%s<\n", i, res[i]);
		i++;
	}
	//printf("^^^^\n");
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
			int ii =0;


	nbr_of_vars = get_nbr_of_vars(token);
	// //printf("nb_var:%i\n",nbr_of_vars);
	res = palloc((nbr_of_vars * 5 + 1), sizeof(char *));
	//put null to all res
	for (int i = 0; i < (nbr_of_vars * 5 + 1); i++)
		res[i] = 0;
	if (!res)
		return (0);
	j = 0;
	i = 0;
	while (token[i])
	{
		if (is_in_quotes(token, i) == SINGLE_QUOTE)
		{
			//printf("----1---\n");
			k = i;
			//printf("i = %d\n", i);
			while (token[k] && token[k] != '\'')
				k++;
			ii = k + 1;
			while(token[ii] && token[ii] != '\'')
				ii++;
			res[j++] = ft_substr(token, k, ii + 1 - k);
				print_res(res);
			i = ii + 1;
				//printf("----1---out\n");
		}
		else if ((token[i] == '$' )&& is_in_quotes(token, i) != SINGLE_QUOTE)
		{
				//printf("----2---\n");
			var_name = get_var_name(&token[i]);
			var_value = get_var_value(var_name, status, env);
			if (var_value)
			{
				if (!ft_strcmp(var_value, "$"))
					i--;
				res[j++] = ft_strdup(var_value);
				print_res(res);
				free(var_value);
			}
			i += ft_strlen(var_name) + 1;
			if (token[i] == '\'' && is_in_quotes(token, i) != DOUBLE_QUOTE)
				i++;
			free(var_name);
				//printf("----2---out\n");
		}
		else
		{
				//printf("----3---\n");
			k = i;
			while (token[k] && (token[k + 1] != '$'))
				k++;
			res[j++] = ft_substr(token, i, k - i + 1);
			//printf("res[%i]\n",j - 1);
			//printf("res[] %p\n",&res[j]);
				// print_res(res);
			i = k + 1;
			// //printf("res[i][j]: %c\n", token[i  - 1]);
				//printf("----3---out\n");
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
// 	res[nbr_of_vars * 3] = 0;
// 	if (!res)
// 		return (0);
// 	j = 0;
// 	i = 0;
// 	while (token[i])
// 	{

// 		if (is_in_quotes(token, i) == SINGLE_QUOTE)
// 		{
// 			k = i;
// 			while (token[k] && token[k] != '\'')
// 				k++;
// 			res[j++] = ft_substr(token, i, (k - i) + 2);
// 				////printf("----1---\n");
// 				print_res(res);
// 			i = k + 1;
// 		}
// 		else if (token[i] == '$' && is_in_quotes(token, i) != SINGLE_QUOTE)
// 		{
// 			var_name = get_var_name(&token[i]);
// 			var_value = get_var_value(var_name, status, env);
// 			if (var_value)
// 			{
// 				if (!ft_strcmp(var_value, "$"))
// 					i--;
// 				res[j++] = ft_strdup(var_value);
// 				////printf("----2---\n");
// 				print_res(res);

// 				free(var_value);
// 			}
// 			i += ft_strlen(var_name) + 1;
// 			if (token[i] == '\'' && is_in_quotes(token, i) != DOUBLE_QUOTE)
// 				i++;
// 			free(var_name);
// 		}
// 		else
// 		{
// 			PL;
// 			k = i;
// 			while (token[k] && token[k] != '$')
// 				k++;
// 			////printf("token: i k: %d %d\n", i, k - i);
// 			res[j++] = ft_substr(token, i, k - i);
// 				////printf("----3---\n");
// 				print_res(res);
// 			i = k;
// 		}
// 		//////printf("resj: %s\n", res[j-1]);

// 	}
// 	res[j] = 0;
// 	new_token = flatten_2d_array(res);
// 	while (res[j])
// 	{
// 		free(res[j]);
// 		j++;
// 	}
// 	free(res);
// 	return (new_token);
// }


// void	expand_env_vars(char **tokens, int status, char **env)
// {
// 	int		i;
// 	char	*tmp;

// 	i = 0;
// 	while (tokens[i])
// 	{
// 		if (ft_strchr(tokens[i], '$'))
// 		{
// 			tmp = expand_token(tokens[i], status, env);
// 			if (tmp)
// 			{
// 				tokens[i] = ft_strdup(tmp);
// 				free(tmp);
// 			}
// 		}
// 		i++;
// 	}
// }




// char *handle_single_quote(char *token, int *i)
// {
// 	int k;
// 	char *res;

// 	k = *i;
// 	while (token[k] && token[k] != '\'')
// 		k++;
// 	res = ft_substr(token, *i - 1, (k - *i) + 2);
// 	*i = k + 1;
// 	return (res);
// }




// char	*handle_out_of_quotes(char *token, int *i)
// {
// 	int k;
// 	char *res;

// 	PL;
// 	k = *i;
// 	while (token[k] && token[k] != '$')
// 		k++;
// 	res = ft_substr(token, *i, k - *i);
// 	*i = k;
// 	return (res);
// }

// void handle_dollar_in_db_quotes(char *token, char **env, char **res, int *i, int *j, int status)
// {
// 	char *var_name;
// 	char *var_value;


// 	var_name = get_var_name(&token[*i]);
// 	var_value = get_var_value(var_name, status, env);
// 	if (var_value)
// 	{
// 		if (!ft_strcmp(var_value, "$"))
// 			(*i)--;
// 		res[(*j)++] = ft_strdup(var_value);
// 		free(var_value);
// 	}
// 	*i += ft_strlen(var_name) + 1;
// 	if (token[*i] == '\'' && is_in_quotes(token, *i) != DOUBLE_QUOTE)
// 		(*i)++;
// 	free(var_name);

// 	// return (res);
// }


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
// 	k = 0;


// 	while (token[i])
// 	{
// 		if (is_in_quotes(token, i) == SINGLE_QUOTE)
// 		{
// 			if (i == 0)
// 				i++;
// 			k = i;
// 			while (token[k] && token[k] != '\'')
// 				k++;
// 				////printf("i-1 = %d | k-i+2 = %d\n", i - 1, (k - i) + 2);
// 			res[j++] = ft_substr(token, i - 1, (k - i) + 2);
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
// 		////printf("res[%d]: %s\n", j - 1, res[j - 1]);
// 	}
// 	res[j] = 0;
// 	new_token = flatten_2d_array(res);

// 	////printf("new_token:%s:\n", new_token);


// 	free(res);

// 	return (new_token);
// }

