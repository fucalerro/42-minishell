#include "minishell.h"

void	exe_infile(t_node *node)
{
	int	fd;

	if (access(node->file, F_OK))
	{
		exit(EXIT_FAILURE);
	}
	fd = open(node->file, O_RDONLY);
	if (fd < 0)
	{
		perror(strerror(errno));
		exit(EXIT_FAILURE);
	}
	else
	{
		dup2(fd, STDIN_FILENO);
	}
}

void	exe_outfile(t_node *node)
{
	if (!access(node->file, F_OK))
	{
		if(access(node->file, W_OK))
		{
			perror(strerror(errno));
			exit(EXIT_FAILURE);
		}
	}
	int fd = open(node->file, O_CREAT | O_WRONLY | O_TRUNC, S_IRUSR | S_IWUSR);
	dup2(fd , STDOUT_FILENO);
	close(fd);
}

void exe_outfile_append(t_node *node)
{
	if (!access(node->file, F_OK))
	{
		if(access(node->file, W_OK))
		{
			perror(strerror(errno));
			exit(EXIT_FAILURE);
		}
	}
    int fd = open(node->file, O_CREAT | O_WRONLY | O_APPEND, S_IRUSR | S_IWUSR);
    dup2(fd, STDOUT_FILENO);
    close(fd);
}

void exe_heredoc(t_node *node) {
    int fd[2];

    if (pipe(fd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    while (1) {
        char *buff_str = readline("> ");
        if (!buff_str || !ft_strcmp(buff_str, node->delimiter)) {
            free(buff_str);
            break;
        }
        write(fd[1], buff_str, ft_strlen(buff_str));
        write(fd[1], "\n", 1);
        free(buff_str);
    }

    close(fd[1]);
    dup2(fd[0], STDIN_FILENO);
    close(fd[0]);
}
