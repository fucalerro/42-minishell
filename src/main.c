#include "history.h"
#include "minishell.h"


#ifndef UNIT_TESTS

void	deal_with_multi_cmd(t_node *node)
{
	int		cmd_seen;
	t_node	*prev_cmd;
	char	**tmp;
	int		count;
	int		i;
	int		ii;

	cmd_seen = 0;
	prev_cmd = NULL;
	while (node)
	{
		if (node->type == T_CMD)
			cmd_seen++;
		if (cmd_seen > 1)
		{
			prev_cmd = node->previous;
			while (prev_cmd && prev_cmd->type != T_CMD)
				prev_cmd = prev_cmd->previous;
			count = 0;
			i = 0;
			while (node->cmd[i++])
				count++;
			i = 0;
			while (prev_cmd->cmd[i++])
				count++;
			tmp = (char **)malloc(sizeof(char *) * (count + 1));
			if (!tmp)
				return ;
			ii = 0;
			i = 0;
			while (prev_cmd->cmd[i])
				tmp[ii++] = prev_cmd->cmd[i++];
			i = 0;
			while (node->cmd[i])
				tmp[ii++] = node->cmd[i++];
			tmp[ii] = NULL;
			free(prev_cmd->cmd);
			prev_cmd->cmd = tmp;
			node->previous->next = node->next;
			if (node->next)
				node->next->previous = node->previous;
			prev_cmd = node->previous;
			free(node->cmd);
			free(node);
			node = prev_cmd;
			cmd_seen = 1;
		}
		if (node->type == T_PIPE)
			cmd_seen = 0;
		node = node->next;
	}
}

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
char *ft_readline(char *line, char **prompt)
{

	*prompt = readline(line);
	if (!*prompt)
	{
		return (NULL);
	}
	return (*prompt);
}
void	process_input_loop(char **line, char ***env_copy, int *status)
{
	t_fd fd;
	char		*prompt;
	char		*tmpline;
	t_tokens	**tokens;
	t_node		*lst;

	prompt = NULL;
	while (ft_readline(*line, &prompt)) //thiiiis is not lega -- do we need to free prompt ?
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
			deal_with_multi_cmd(lst); //push that in exe_prompt
			exe_prompt(lst, env_copy, status);
			free_lst(lst);
			setback_fd(&fd);
			tmpline = builtin_pwd();
			free(*line);
			*line = ft_strjoin(tmpline, "🌻 ");
			free(tmpline);
		}
		free_tokens(tokens);
	}
}

int	main(int ac, char **av, char **env)
{
	char	*tmpline;
	char	*line;
	int		status;
	char	**env_copy;

	if (ac > 2)
		exit(1);
	(void) av;
	tmpline = builtin_pwd();
	status = 0;
	signal(SIGINT, sigint_handler);   // Ctrl-C
	signal(SIGQUIT, sigquit_handler); // Ctrl-'\'
	line = ft_strjoin(tmpline, "🌻 ");
	free(tmpline);
	env_copy = copy_env(env, 0);
	ft_read_history();
	process_input_loop(&line, &env_copy, &status);
	free(line); //this is never reached
	printf("exit\n");
	return (0);
}
#endif
