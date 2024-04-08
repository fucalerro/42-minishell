#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <stdbool.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <dirent.h>
#include <sys/resource.h>
#include <signal.h>
#include "node.h"
#include "../libft/libft.h"
#include "parser.h"
#include "history.h"
#include "stack.h"
#include "colors.h"
#include "error.h"
#include <sys/stat.h>


#define MINI_DEBUG_MSG 0


#include <errno.h>
extern int errno;

/* FUNCTIONS */
void	print_list(t_node *lst);
char **consolidate_cmd(char **input, int i, int *token_count);
// var_expansion.c
char    *var_expander(char *string);
void    expand_env_vars(char **tokens, int status);
// array_utils.c
int get_elem_count(char **array);
char **flatten_3d_array(char ***array3d);
void    free_string_array(char **strings);
void    print_string_tab(char **tab);
// parser.c
size_t	wordcounter(char const *s, char c);
char    **tokenizer(char *string, int status);
char    **op_tokenizer(char *string);
char    **sp_tokenizer(char *string, char c);
int word_counter_quotes(char *input);
int is_in_quotes(char *input, int index);
t_node  *parser(char **input);
int is_quote(char c);
char    *input_normalizer(char *input);
//error_handling.c
int    parsing_error(char **tokens);
void    errror_msg(int type, int c);
// exec.c
int exe_prompt(t_node *node, char ***env, t_hist **hist, int *status);
// builtin.c
char *builtin_pwd(void);
void builtin_cd(const char *path);
void builtin_exit(char* exit_code);
void builtin_history(char **cmd, t_hist **hist);
// env
void builtin_env(char **env);
void builtin_export(char ***env, char **var);
char **copy_env(char **env, int size);
void builtin_unset(char ***env, char **var);

void debug_print(char *msg);

//stack.c
void	stack_add(t_stack **lst, int value);
void	stack_drop(t_stack **lst);
//erreur.c
void debug_print(char * msg);
//list_utils.c
int sort_infile(t_node **lst);
//infile.c
void	exe_infile(t_node *node);
void	exe_outfile_append(t_node *node);
void	exe_outfile(t_node *node);
void	exe_heredoc(t_node *node);
//signal.c
void sigint_handler(int sig);
void sigquit_handler(int sig);


// print_line define for quick debug
#define PL printf("line: %d file: %s\n", __LINE__,  __FILE__);

#endif
