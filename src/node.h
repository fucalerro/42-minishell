#ifndef NODE_H
#define NODE_H

#define T_PIPE 1
#define T_INFILE 2
#define T_OUTFILE 3
#define T_HEREDOC 4
#define T_CMD 5

typedef struct s_node
{
	int            type;
	char *file;
	char **cmd; // I think we should have commands an array ["cmd name", "cmd args"]
	struct s_node *next;
	struct s_node *previous;
} t_node;

t_node	*lst_new(int type, char *file, char **cmd);
void	lst_append(t_node **lst, int type, char *file, char **cmd);
#endif
