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
int exe_heredoc(t_node *node) {
/////////////////////////////CECHK
    pid_t pid;
    int fd;  // File descriptor for the output file
    char *filename = ft_strdup("heredoc_output.txt");  // Specify your file name here

    pid = fork(); // Fork a new process

    if (pid == -1) {
        // Fork failed
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        // Child process
        char *buff_str;

        // Open the file for writing, create if not exists, truncate to zero length
        fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (fd == -1) {
            perror("Failed to open file");
            exit(EXIT_FAILURE);
        }

        while (1) {
            buff_str = readline("> ");
            if (!buff_str || !ft_strcmp(buff_str, node->delimiter)) {
                free(buff_str);
                break;
            }
            write(fd, buff_str, strlen(buff_str));
            write(fd, "\n", 1);  // Write newline character
            free(buff_str);
        }

        close(fd);  // Close the file descriptor
        exit(EXIT_SUCCESS);  // Ensure the child exits after doing its work
    } else {
        // Parent process
        waitpid(pid, NULL, 0);  // Wait for the child process to finish
		node->file = filename;
		exe_infile(node);
		
    }

    return 0;
}
int	exe_heredor(t_node *node)
{
	int		fd[2];
	char	*buff_str;

	if (pipe(fd) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	while (1)
	{
		buff_str = readline("> ");
		printf("buff_str: ..%s..\n", buff_str);
		if (!buff_str || !ft_strcmp(buff_str, node->delimiter))
		{
			free(buff_str);
			break ;
		}
		write(fd[1], buff_str, ft_strlen(buff_str));
		write(fd[1], "\n", 1);
		free(buff_str);
	}
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	return (0);
}
