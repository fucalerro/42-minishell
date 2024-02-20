#ifndef NODE_H
#define NODE_H

typedef struct s_node
{
	struct s_node *sublist;
	int            special;
	char spe[0]; // temporary solution until we find how we want to manage the special caracters
	char **cmd; // I think we should have commands an array ["cmd name", "cmd args"]
	struct s_node *next;
	struct s_node *previous; // let see if we need it
} t_node;

#endif
