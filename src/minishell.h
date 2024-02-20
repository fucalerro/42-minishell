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

#include "node.h"
#include "../libft/libft.h"

/* FUNCTIONS */
void	print_string_tab(char **tab);
int		is_char_special(char c);

#endif
