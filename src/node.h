#ifndef NODE_H
#define NODE_H

#define T_PIPE 1
#define T_INFILE 2
#define T_HEREDOC 3
#define T_CMD 4
#define T_OUTFILE 5
#define T_OUTFILE_APPEND 6

#define PIPE_NEXT 1
#define PIPE_PREVIOUS 2

typedef struct s_node
{
	int				type;
	char			*file;
	char			**cmd;
	struct s_node	*next;
	struct s_node	*previous;
	char			*delimiter;
	int 			pipe[2][2];
} 					t_node;

t_node	*lst_new(int type, char *file, char **cmd, char *delimiter);
void	lst_append(t_node **lst, int type, char *file, char **cmd, char *delimiter);
void	free_lst(t_node *lst);

#endif




