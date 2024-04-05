#include "minishell.h"

void	exe_infile(t_node *node)
{
	int	fd;

	if (access(node->file, R_OK))
	{
		//error("no such file or directory: ", node->file);
		//close_pipe(&pipefd[0], node);
		exit(EXIT_FAILURE);
	}
	fd = open(node->file, O_RDONLY);
	if (fd < 0)
	{
		//error("no such file or directory: ", node->file);
		//close_pipe(&pipefd[0], node);
		exit(EXIT_FAILURE);
	}
	else
	{
		dup2(fd, STDIN_FILENO);
	}
	//close_pipe(&pipefd[0], node);
}

void	exe_outfile(char *outfile)
{
	int fd = open(outfile, O_CREAT | O_WRONLY | O_TRUNC, S_IRUSR | S_IWUSR);
	dup2(fd , STDOUT_FILENO);
	close(fd);
}

void exe_outfile_append(char *outfile) {
    int fd = open(outfile, O_CREAT | O_WRONLY | O_APPEND, S_IRUSR | S_IWUSR);
    dup2(fd, STDOUT_FILENO);
    close(fd);
}

