#include "minishell.h"

int	exe_infile(t_node *node)
{
	int	fd;

	if (access(node->file, F_OK))
	{
		perror(strerror(errno));
		return (1);
	}
	fd = open(node->file, O_RDONLY);
	if (fd < 0)
	{
		perror(strerror(errno));
		close(fd);
		exit(EXIT_FAILURE);
	}
	else
	{
		dup2(fd, STDIN_FILENO);
	}
	close(fd);
	return (0);
}

int	exe_outfile(t_node *node)
{
	int	fd;

	if (!access(node->file, F_OK))
	{
		if (access(node->file, W_OK))
		{
			perror(strerror(errno));
			return (1);
		}
	}
	fd = open(node->file, O_CREAT | O_WRONLY | O_TRUNC, S_IRUSR | S_IWUSR);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (0);
}

int	exe_outfile_append(t_node *node)
{
	int	fd;

	if (!access(node->file, F_OK))
	{
		if (access(node->file, W_OK))
		{
			perror(strerror(errno));
			return (1);
		}
	}
	fd = open(node->file, O_CREAT | O_WRONLY | O_APPEND, S_IRUSR | S_IWUSR);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (0);
}
int exe_heredoc(t_node *node)
{
    pid_t pid;
	char *buff_str;
	int		fd[2];
	int status;

	if (pipe(fd) == -1)
		exit(EXIT_FAILURE);
    pid = fork();
    if (pid == -1)
	{
        perror("fork");
        exit(EXIT_FAILURE);
    }
	else if (pid == 0)
	{
		signal(SIGINT, sigint_handler_heredoc);
		close(fd[0]);
		while (1)
		{
			buff_str = readline("> ");
			if (!buff_str || !ft_strcmp(buff_str, node->delimiter))
			{
				free(buff_str);
				break;
			}
			write(fd[1], buff_str, ft_strlen(buff_str));
			write(fd[1], "\n", 1);
			free(buff_str);
		}

		close(fd[1]);
        exit(EXIT_SUCCESS);
    }
	else
	{
        waitpid(pid, &status, 0);
		close(fd[1]);
		if (WIFEXITED(status) && WEXITSTATUS(status))
			return (close(fd[0]) || 1);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
	}
    return 0;
}
