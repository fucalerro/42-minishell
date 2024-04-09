#include "minishell.h"

char *builtin_pwd(void) {
    char *cwd;
    cwd = getcwd(NULL, 0); //its a malloc, wee need to free that at some point
    if (cwd != NULL) {
		return cwd;
    } else {
        perror("getcwd() error");
    }
	return NULL;
}

int builtin_cd(const char *path) {
    if (path == NULL) {
        path = getenv("HOME");
        if (path == NULL) {
            write_err("cd: HOME not set\n");
            return 1;
        }
    }
    if (chdir(path) != 0)
	{
        perror(" cd");
		return 1;
    }
	return 0;
}

void    builtin_history(char **cmd, t_hist **hist)
{
    char *home;
    char *path;

    if (!hist)
    {
        return ;
    }
    if (!cmd[1])
    {
        print_hist();
    }
    else if (!ft_strcmp(cmd[1], "-c"))
    {
        path = get_history_path();
        unlink(path);
        // free(path);
        rl_clear_history();
        // clear_hist(hist);
    }
}

int builtin_exit(t_node *node)
{
	char *cmd;
	if (!node->cmd[1])
		exit(0);
	if (node->cmd[1] && node->cmd[2])
	{
		write_err( "too many arguments\n");
		return 1;
	}
	cmd = node->cmd[1];
	if(*cmd == '-' || *cmd == '+')
		cmd++;
	while(*cmd)
	{
		if (!ft_isdigit(*cmd))
		{
			write_err(" numeric argument required\n");
			exit (255);
		}
		cmd++;
	}
	if (node->cmd[1])
	{
		exit(atoi(node->cmd[1]));
	}
	return 0;
}
