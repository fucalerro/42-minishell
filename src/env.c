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

	len = 0;
	while (var[len] != '=')
		len++;
	printf("len: %d\n", len);

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], var, len) == 0)
			return (i);
		i++;
	}
	return (-1);
}

void	builtin_export(char ***env, char *var)
{
	char **new_env;
	int env_size;

	env_size = 0;
	while ((*env)[env_size])
		env_size++;
	
	int var_index;
	
	var_index = does_var_exist(*env, var);
	printf("var_index: %d\n", var_index);
	if (var_index >= 0)
	{
		free((*env)[var_index]);
		(*env)[var_index] = ft_strdup(var);
		return ;
	}
	new_env = copy_env(*env, 1);
	new_env[env_size++] = ft_strdup(var);
	new_env[env_size] = 0;
	*env = new_env;
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
