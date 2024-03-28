#include "minishell.h"

char **copy_env(char **env, int size)
{
	int env_size;
	int i;
	char **new_env;

	env_size = 0;
	while (env[env_size])
		env_size++;

	new_env = malloc((env_size + size + 1) * sizeof(char *));
	i = 0;
	while (env[i])
	{
		new_env[i] = ft_strdup(env[i]);
		i++;
	}
	new_env[i] = 0;
	return (new_env);
}

int does_var_exist(char **env, char *var)
{
	int i;
	int len;

	i = 0;
	len = 0;
	while (var[len] != '=' && var[len])
		len++;
	while (env[i])
	{
		if (ft_strncmp(env[i], var, len) == 0)
			return (i);
		i++;
	}
	return (-1);
}


int does_vars_exist(char **env, char *var)
{
	int i;
	int len;

	len = 0;
	while (var[len] != '=' && var[len])
		len++;
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], var, len) == 0)
			return (i);
		i++;
	}

}




void	builtin_export(char ***env, char **var)
{
	char **new_env;
	int env_size;

	env_size = 0;
	while ((*env)[env_size])
		env_size++;
	
	int *var_index;
	int var_nbr;

	var_nbr = 0;
	while (var[var_nbr])
		var_nbr++;
	var_nbr--;
	var_index = malloc(var_nbr * sizeof(int));
	PL;

	int j;
	j = 0;
	while (var[++j])
		var_index[j - 1] = does_var_exist(*env, var[j]);

	printf("var_nbr: %d\n", var_nbr);
	for (int i = 0; i < var_nbr; i++)
		printf("varindex: %d\n", var_index[j]);
	PL;


	j = 0;
	new_env = copy_env(*env, var_nbr);
	while (var_index[j])
	{
		if (var_index[j] >= 0)
		{
			PL;
			free((*env)[var_index[j]]);
			(*env)[var_index[j]] = ft_strdup(var[j + 1]);
			return ;
		}
		j++;

	}
	j = 0;
	while (var[j])
	{
		new_env[env_size++] = ft_strdup(var[j]);
		j++;
	
	}
	new_env[env_size] = 0;
	*env = new_env;
}

void builtin_unset(char **env, char *var)
{
	if (ft_strchr(var, '='))
	{
		printf("unset: not a valid identifier\n");
		return ;
	}
	int var_index = does_var_exist(env, var);
	int i;

	if (var_index >= 0)
	{
		free(env[var_index]);
		i = var_index;
		while (env[var_index])
		{
			env[var_index] = env[var_index + 1];
		}
	}
}


void	print_env(char **env)
{
	int i;

	i = 0;
	while (env[i])
		printf("%s\n", env[i++]);

}

void	builtin_env(char **env)
{
	int i;

	i = 0;
	while (env[i])
		printf("%s\n", env[i++]);
}
