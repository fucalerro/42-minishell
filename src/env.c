/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Lu-ni <lucas.nicollier@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 22:12:43 by Lu-ni             #+#    #+#             */
/*   Updated: 2024/04/28 22:12:43 by Lu-ni            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "env.h"

void	print_env(char **tab)
{
	int		i;
	int		j;
	char	*value;

	i = -1;
	while (tab[++i])
	{
		j = 0;
		printf("declare -x ");
		while (tab[i][j] && tab[i][j] != '=')
		{
			printf("%c", tab[i][j++]);
		}
		if (ft_strchr(tab[i], '='))
		{
			value = ft_strchr(tab[i], '=');
			printf("=\"%s\"\n", ++value);
		}
		else
			printf("\n");
	}
}

int	builtin_export(char ***env, char **var)
{
	int	i;

	i = 0;
	if (!var[1])
	{
		print_env(*env);
		return (0);
	}
	while (var[++i])
	{
		if (!is_varvalue_valid(var[i]))
			return (1);
		if (!is_varname_valid(var[i]))
			return (1);
	}
	i = 0;
	while (var[++i])
		export_var(env, var[i]);
	return (0);
}

void	unset_var(char **env, char *var)
{
	int	var_index;

	if (ft_strchr(var, '='))
	{
		printf("unset: not a valid identifier\n");
		return ;
	}
	var_index = does_var_exist(env, var);
	if (var_index >= 0)
	{
		free(env[var_index]);
		while (env[var_index])
		{
			env[var_index] = env[var_index + 1];
			var_index++;
		}
		env[var_index] = 0;
	}
}

void	builtin_unset(char ***env, char **var)
{
	int	i;

	i = 0;
	while (var[++i])
		unset_var(*env, var[i]);
}

void	builtin_env(char **env)
{
	int	i;

	i = 0;
	while (env[i])
		printf("%s\n", env[i++]);
}
