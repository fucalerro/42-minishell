#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void builtin_pwd() {
    char *cwd;
    cwd = getcwd(NULL, 0);
    if (cwd != NULL) {
        printf("%s\n", cwd); //use libft printf
        free(cwd);
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
