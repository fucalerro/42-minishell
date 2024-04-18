#include "minishell.h"

char	*ft_getenv(char *varname, char **env)
{
	int		i;
	int		varname_len;

	i = -1;
	varname_len = ft_strlen(varname);
	while (env[++i])
		if (!ft_strncmp(varname, env[i], varname_len)
			&& env[i][varname_len] == '=')
			return (env[i] + varname_len + 1);
	return (0);
}

char	**copy_env(char **env, int size)
{
	int		env_size;
	int		i;
	char	**new_env;

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

int	does_var_exist(char **env, char *var)
{
	int	i;
	int	var_len;
	int	evar_len;

	if (var == NULL)
		return (-1);
	i = 0;
	var_len = 0;
	while (var[var_len] != '=' && var[var_len])
		var_len++;
	while (env[i])
	{
		evar_len = 0;
		while (env[i][evar_len] != '=' && env[i][evar_len])
			evar_len++;
		if (evar_len == var_len && ft_strncmp(env[i], var, var_len) == 0)
			return (i);
		i++;
	}
	return (-1);
}

void	export_var(char ***env, char *var)
{
	char	**new_env;
	int		env_size;
	int		var_index;

	var_index = 0;
	env_size = 0;
	while ((*env)[env_size])
		env_size++;
	var_index = does_var_exist(*env, var);
	if (var_index >= 0)
	{
		free((*env)[var_index]);
		(*env)[var_index] = ft_strdup(var);
		return ;
	}
	new_env = copy_env(*env, 1);
	new_env[env_size] = ft_strdup(var);
	new_env[env_size + 1] = 0;
	*env = new_env;
}

int	is_varname_valid(char *var)
{
	int	i;

	i = 0;
	if (!ft_isalpha(var[i]) && var[i] != '_')
	{
		errno = EINVAL;
		write_err("export: not a valid identifier\n");
		return (false);
	}
	i++;
	while (var[i] && var[i] != '=')
	{
		if (!ft_isalnum(var[i]) && var[i] != '_')
		{
			errno = EINVAL;
			write_err("export: not a valid identifier\n");
			return (false);
		}
		i++;
	}
	return (true);
}

int	is_varvalue_valid(char *var)
{
	int	i;

	i = 0;
	while (var[i] && var[i] != '=')
		i++;
	if (var[i] != '=')
		return (true);
	i++;
	while (var[i])
	{
		if (!ft_isprint(var[i]))
		{
			errno = EINVAL;
			write_err("export: not a valid identifier\n");
			return (false);
		}
		i++;
	}
	return (true);
}

void	print_env(char **tab)
{
	int		i;
	int		j;
	char	*value;

	i = 0;
	while (tab[i])
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
		{
			printf("\n");
		}
		i++;
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
