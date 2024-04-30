/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicolli <lnicolli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 22:12:43 by Lu-ni             #+#    #+#             */
/*   Updated: 2024/04/30 20:31:29 by lnicolli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <termios.h>

void	set_signal(int primary)
{
	struct termios		term;
	struct sigaction	sa_quit;

	if (primary == 0)
	{
		signal(SIGINT, sigint_handler);
		sa_quit.sa_handler = sigquit_handler;
	}
	else
	{
		signal(SIGINT, sigint_handler_p);
		sa_quit.sa_handler = sigquit_handler_p;
	}
	sigemptyset(&sa_quit.sa_mask);
	sa_quit.sa_flags = 0;
	sigaction(SIGQUIT, &sa_quit, NULL);
	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

char	*all_quotes_remover(char *string)
{
	char	*token;
	char	prev_quote;

	prev_quote = 0;
	token = palloc(ft_strlen(string) + 1, sizeof(char));
	if (!token)
		return (0);
	all_quotes_remover_loop(string, &token, prev_quote);
	return (token);
}

char	*around_quotes_remover(char *string)
{
	char	*res;
	int		i;

	if (!is_quote(string[0]))
		return (ft_strdup(string));
	res = palloc(ft_strlen(string) + 1, sizeof(char));
	if (!res)
		return (0);
	i = 0;
	while (string[i])
	{
		res[i] = string[i + 1];
		i++;
	}
	res[i - 2] = 0;
	return (res);
}

char	**get_new_shlvl(char **env)
{
	int		shlvl;
	char	*shlvl_str;
	char	*new_shlvl_string;
	char	**new_shlvl;

	new_shlvl = palloc(3, sizeof(char *));
	new_shlvl[0] = ft_strdup("export");
	shlvl_str = ft_getenv("SHLVL", env);
	if (!shlvl_str)
		new_shlvl[1] = ft_strdup("SHLVL=1");
	else
	{
		shlvl = ft_atoi(shlvl_str);
		new_shlvl_string = ft_itoa(shlvl + 1);
		new_shlvl[1] = ft_strjoin("SHLVL=", new_shlvl_string);
		free(new_shlvl_string);
	}
	new_shlvl[2] = NULL;
	return (new_shlvl);
}
