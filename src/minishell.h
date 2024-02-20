#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <fcntl.h>
#include <errno.h>
#include <stdbool.h>

#include "node.h"
#include "../libft/libft.h"

/* FUNCTIONS */
char    *input_normalizer(char *input);
void	print_string_tab(char **tab);
int		is_char_special(char c);

#define PL printf("line: %d file: %s\n", __LINE__,  __FILE__);

#endif
