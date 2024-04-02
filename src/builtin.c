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

void builtin_cd(const char *path) {
    if (path == NULL) {
        path = getenv("HOME");
        if (path == NULL) {
            fprintf(stderr, "cd: HOME not set\n");
            return;
        }
    }
    if (chdir(path) != 0) {
        perror("cd");
    }
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
        print_hist(*hist);
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

void builtin_exit(void)
{
	exit(EXIT_SUCCESS);
}
