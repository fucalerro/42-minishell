/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicolli <lnicolli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 22:12:43 by Lu-ni             #+#    #+#             */
/*   Updated: 2024/04/30 21:28:04 by lnicolli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	setback_fd(t_fd *fd)
{
	if (dup2(fd->in, STDIN_FILENO) == -1)
		exit(EXIT_FAILURE);
	if (dup2(fd->out, STDOUT_FILENO) == -1)
		exit(EXIT_FAILURE);
	close(fd->in);
	close(fd->out);
}

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
	return (new_env);
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
			if (!check_error(lst))
				exe_prompt(lst, env_copy, status);
		}
		setback_fd(&fd);
		free(prompt);
		free_tokens(tokens);
		set_signal(0);
	}
}

int	main(int ac, char **av, char **env)
{
	int		status;
	char	**env_copy;
	char	**new_shlvl;

	if (ac > 1)
		exit(1);
	(void)av;
	status = 0;
	set_signal(0);
	env_copy = copy_env(env, 0);
	new_shlvl = get_new_shlvl(env_copy);
	builtin_export(&env_copy, new_shlvl);
	free_2starchar(new_shlvl);
	ft_read_history(env_copy);
	process_input_loop(&env_copy, &status);
	return (0);
}
