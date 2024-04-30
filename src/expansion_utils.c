#include "minishell.h"


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

	// printf("get var name: %s\n", var_name);

	return (var_name);
}

char	*get_var_value(char *var_name, int status, char **env)
{
	char	*var_value;

	if (!var_name)
		return (0);

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
		// if (token[i] == '$' && is_in_quotes(token, i) != SINGLE_QUOTE)
		if (token[i] == '$')
			nbr_of_vars++;
		i++;
	}
	return (nbr_of_vars);
}
