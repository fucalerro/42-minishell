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
#include <readline/readline.h>
#include <readline/history.h>


#include "node.h"
#include "../libft/libft.h"
#include "parser.h"

/* FUNCTIONS */
int	parser(char *input);
int is_quote(char c);
char    *input_normalizer(char *input);
void	print_string_tab(char **tab);
int	is_char_special(char c);
int is_in_single_quotes(char *input, int index);



// print_line define for quick debug
#define PL printf("line: %d file: %s\n", __LINE__,  __FILE__);

#endif
