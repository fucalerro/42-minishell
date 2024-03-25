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
#include "history.h"
#include "../libft/libft.h"
#include "parser.h"

/* FUNCTIONS */
char    *var_expander(char *string);
char    *var_expander(char *string);
char **flatten_3d_array(char ***array3d);
size_t	wordcounter(char const *s, char c);
char    *var_expander(char *string);
char    **get_files_list();
char    **tokenizer(char *string);
char    **op_tokenizer(char *string);
char    **sp_tokenizer(char *string, char c);
char    **tokeniser(char *s, char c);
char    **quotes_splitter(char *input);
int word_counter_quotes(char *input);
int is_in_quotes(char *input, int index);
t_node  *parser(char **input);
int is_quote(char c);
char    *input_normalizer(char *input);
void    print_string_tab(char **tab);
int	is_char_special(char c);



// print_line define for quick debug
#define PL printf("line: %d file: %s\n", __LINE__,  __FILE__);

#endif
