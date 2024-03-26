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
#include <dirent.h>

#include "node.h"
#include "../libft/libft.h"
#include "parser.h"
#include "history.h"

/* FUNCTIONS */
void	print_list(t_node *lst);
char **consolidate_cmd(char **input, int i, int *token_count);
int get_elem_count(char **array);
char    *var_expander(char *string);
char    *var_expander(char *string);
char **flatten_3d_array(char ***array3d);
size_t	wordcounter(char const *s, char c);
char    *var_expander(char *string);
char    **tokenizer(char *string);
char    **op_tokenizer(char *string);
char    **sp_tokenizer(char *string, char c);
int word_counter_quotes(char *input);
int is_in_quotes(char *input, int index);
t_node  *parser(char **input);
int is_quote(char c);
char    *input_normalizer(char *input);
void    print_string_tab(char **tab);


// print_line define for quick debug
#define PL printf("line: %d file: %s\n", __LINE__,  __FILE__);

#endif
