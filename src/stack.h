#ifndef STACK_H
# define STACK_H
typedef struct s_stack
{
	int				value;
	struct s_stack	*next;
}					t_stack;
#endif
