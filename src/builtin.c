#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *builtin_pwd(void) {
    char *cwd;
    cwd = getcwd(NULL, 0); //its a malloc, wee need to free that at some point
    if (cwd != NULL) {
		return cwd;
    } else {
        perror("getcwd() error");
    }
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

void builtin_exit(void)
{
	exit(EXIT_SUCCESS);
}
