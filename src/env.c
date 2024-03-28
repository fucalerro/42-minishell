#include "minishell.h"

char **copy_env(char **env)
{
	int env_size;
	int i;
	char **new_env;

	env_size = 0;
	while (env[env_size])
		env_size++;

	new_env = malloc((env_size + 1) * sizeof(char *));
	i = 0;
	while (env[i])
	{
		new_env[i] = ft_strdup(env[i]);
		i++;
	}
	new_env[i] = 0;
	return (new_env);
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
