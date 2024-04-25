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
#include <errno.h>


#define MINI_DEBUG_MSG 0

typedef struct s_fd
{
	int				out;
	int             in;
} 					t_fd;

extern int errno;

/* FUNCTIONS */
void	print_list(t_node *lst);
// var_expansion.c
char    *var_expander(char *string);
void    expand_env_vars(char **tokens, int status, char **env);
// array_utils.c
void    print_tokens(t_tokens **tokens);
int get_elem_count_tok(t_tokens **array);
int count_arr_elems(char **array);
char **flatten_3d_array(char ***array3d);
void    free_string_array(char **strings);
void    print_string_tab(char **tab);
char *flatten_2d_array(char **array);
// parser.c
int	is_metachar(char c);
void *palloc(int size, int elem_size);
size_t	wordcounter(char const *s, char c);
t_node *parser(t_tokens **tokens);
int is_quote(char c);
char    *input_normalizer(char *input);
int word_counter_quotes(char *input);
int is_in_quotes(char *input, int index);
char **consolidate_cmd(t_tokens **input, int i, int *arg_count);
// tokenizer.c
int	is_single_op(char *string, int i);
int	is_double_op(char *string, int i);
int	count_op(char *string);
void 	free_tokens(t_tokens **tokens);


t_tokens **tokenizer(char *string, int status, char **env);
char    **op_tokenizer(char *string);
char    **sp_tokenizer(char *string, char c);
//error_handling.c
int    parsing_error(t_tokens **tokens);
int    errror_msg(int type, int c);
// exec.c
int exe_prompt(t_node *node, char ***env, int *status);
// builtin.c
char *builtin_pwd(void);
int builtin_cd(const char *path, char **env);
int builtin_exit(t_node *node);
void builtin_history(char **cmd);
// env.c
char *ft_getenv(char *varname, char **env);
void builtin_env(char **env);
int builtin_export(char ***env, char **var);
char **copy_env(char **env, int size);
void builtin_unset(char ***env, char **var);
int builtin_echo(t_node *node);

void debug_print(char *msg);

//stack.c
void	stack_add(t_stack **lst, int value);
void	stack_drop(t_stack **lst);
//erreur.c
void debug_print(char * msg);
void write_err(char *str);
//list_utils.c
int sort_infile(t_node **lst);
//infile.c
int exe_infile(t_node *node);
int exe_outfile_append(t_node *node);
int exe_outfile(t_node *node);
int exe_heredoc(t_node *node);
//signal.c
void sigint_handler(int sig);
void sigquit_handler(int sig);
//pipe.c
void check_pipe_status(t_node *node);
int init_pipe(t_node *node);
int close_pipe(t_node *node);
int	set_pipe(t_node *node);
int	check_pipe(t_node *node);
//free.c
void free_2starchar(char **strstr);


// print_line define for quick debug
#define PL printf("line: %d file: %s\n", __LINE__,  __FILE__);

#endif
