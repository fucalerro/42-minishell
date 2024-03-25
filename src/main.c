#include "minishell.h"

extern char **environ;

#ifndef UNIT_TESTS


int create_history(void)
{
    int fd;

    fd = open("/$HOME.minishell_history", 0);
}



void exec(char *line, char **env, t_node *lst)
{
	char *args[] = {"/usr/bin/touch", "okokokokok", NULL};  // Arguments array
	pid_t	pid;
	pid = fork();
	if (pid == 0)
		execve(lst->cmd[0], lst->cmd, env);
	else
		wait(NULL);
}

int main(int ac, char **av, char **env)
{
    char *line = "-> ";
    char *prompt;
    char **tokens;

	t_node *lst;
	char *cmd[] = {"/bin/ls",NULL};
	lst_append(&lst, T_CMD, NULL, cmd);

    while((prompt = readline(line)))
    {
        add_history(prompt);
        execve("/bin/history", NULL, env);

		if (prompt[0] == 'x')
		{
			exec(prompt, env, lst);
		}
    }
    return (0);
}
#endif


// (cd /tmp && touch "file" && "echo'hello'" > file && grep 'hello' file | tee result.txt) || echo 'Error' > error.log
