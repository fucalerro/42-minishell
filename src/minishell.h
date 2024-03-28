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
#include <sys/resource.h>
#include "node.h"
#include "../libft/libft.h"
#include "parser.h"
#include "history.h"
#include "stack.h"

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
// exec.c
int exe_prompt(t_node *node, char ***env, t_hist **hist);
// builtin.c
char *builtin_pwd(void);
void builtin_cd(const char *path);
void builtin_exit(void);
void builtin_history(char **cmd, t_hist **hist);
// env
void builtin_env(char **env);
void builtin_export(char ***env, char *var);
char **copy_env(char **env, int size);
void builtin_unset(char **env, char *var);






//stack.c
void	stack_add(t_stack **lst, int value);
void	stack_drop(t_stack **lst);


// print_line define for quick debug
#define PL printf("line: %d file: %s\n", __LINE__,  __FILE__);

#endif
