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
			exit(EXIT_FAILURE);
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
			exit(EXIT_FAILURE);
	}
    int fd = open(node->file, O_CREAT | O_WRONLY | O_APPEND, S_IRUSR | S_IWUSR);
    dup2(fd, STDOUT_FILENO);
    close(fd);
}

