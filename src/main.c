/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Lu-ni <lucas.nicollier@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 22:12:43 by Lu-ni             #+#    #+#             */
/*   Updated: 2024/04/28 22:12:43 by Lu-ni            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**copy_env(char **env, int size)
{
	int		env_size;
	int		i;
	char	**new_env;

	env_size = 0;
	while (env && env[env_size])
		env_size++;
	new_env = palloc(env_size + size + 1, sizeof(char *));
	if (!new_env)
		return (0);
	i = 0;
	while (env && env[i])
	{
		new_env[i] = ft_strdup(env[i]);
		i++;
	}
	new_env[i] = 0;

	int shlvl;
	char **shlvlstring;
	shlvlstring = palloc(3, sizeof(char *));
	shlvl = ft_atoi(ft_getenv("SHLVL", new_env)) + 1;
	shlvlstring[0] = ft_strdup("");
	char *new_shlvl = ft_itoa(shlvl);
	shlvlstring[1] = ft_strjoin("SHLVL=", new_shlvl);
	shlvlstring[2] = NULL;
	builtin_export(&new_env, shlvlstring);

	free(new_shlvl);
	free_2starchar(shlvlstring);

	return (new_env);
}

void	setback_fd(t_fd *fd)
{
	if (dup2(fd->in, STDIN_FILENO) == -1)
		exit(EXIT_FAILURE);
	if (dup2(fd->out, STDOUT_FILENO) == -1)
		exit(EXIT_FAILURE);
	close(fd->in);
	close(fd->out);
}

char	*ft_readline(char **prompt)
{
	char	*line;
	char	*tmpline;

	tmpline = builtin_pwd();
	line = ft_strjoin(tmpline, "🌻 ");
	free(tmpline);
	*prompt = readline(line);
	free(line);
	if (!*prompt)
	{
		return (NULL);
	}
	return (*prompt);
}

void	process_input_loop(char ***env_copy, int *status)
{
	t_fd		fd;
	char		*prompt;
	t_tokens	**tokens;
	t_node		*lst;

	prompt = NULL;
	while (ft_readline(&prompt))
	{
		fd.in = dup(STDIN_FILENO);
		fd.out = dup(STDOUT_FILENO);
		if (ft_strlen(prompt) == 0 || is_quotes_opened(prompt))
			continue ;
		tokens = tokenizer(prompt, *status, *env_copy);
		if (!parsing_error(tokens))
		{
			lst = parser(tokens);
			if (lst)
				ft_history(prompt, *env_copy);
			exe_prompt(lst, env_copy, status);
			setback_fd(&fd);
		}
		free(prompt);
		free_tokens(tokens);
		set_signal(0);
	}
}

int	main(int ac, char **av, char **env)
{
	int		status;
	char	**env_copy;
	if (ac > 1)
		exit(1);
	(void)av;
	status = 0;
	set_signal(0);
	env_copy = copy_env(env, 0);
	ft_read_history(env_copy);
	process_input_loop(&env_copy, &status);
	return (0);
}
