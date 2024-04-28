#include "history.h"
#include "minishell.h"


#ifndef UNIT_TESTS


void setback_fd(t_fd *fd)
{
	// Restore original stdin
	if (dup2(fd->in, STDIN_FILENO) == -1)
	{
		perror("dup2");
		exit(EXIT_FAILURE);
	}
	// Restore original stdout
	if (dup2(fd->out, STDOUT_FILENO) == -1)
	{
		perror("dup2");
		exit(EXIT_FAILURE);
	}
	// Close the saved descriptors no longer needed
	close(fd->in);
	close(fd->out);

}
char *ft_readline(char **prompt)
{
	char	*line;
	char		*tmpline;
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
	t_fd fd;
	char		*prompt;
	t_tokens	**tokens;
	t_node		*lst;

	prompt = NULL;
	signal(SIGINT, sigint_handler);   // Ctrl-C
	while (ft_readline(&prompt))
	{
		fd.in = dup(STDIN_FILENO);
		fd.out = dup(STDOUT_FILENO);

		if (ft_strlen(prompt) == 0 || is_quotes_opened(prompt))
			continue;
		tokens = tokenizer(prompt, *status, *env_copy);
		if (!parsing_error(tokens))	
		{
			lst = parser(tokens);
			if (lst)
				ft_history(prompt);
			exe_prompt(lst, env_copy, status);
			setback_fd(&fd);
		}
		free(prompt);
		free_tokens(tokens);
		signal(SIGINT, sigint_handler);   // Ctrl-C
	}
}

int	main(int ac, char **av, char **env)
{
	int		status;
	char	**env_copy;

	if (ac > 2)
		exit(1);
	(void) av;
	status = 0;
	signal(SIGQUIT, sigquit_handler); // Ctrl-'\'
	env_copy = copy_env(env, 0);
	ft_read_history();
	process_input_loop(&env_copy, &status);
	return (0);
}
#endif
