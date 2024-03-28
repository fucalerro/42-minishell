#include "minishell.h"

t_stack	*stack_new(int content)
{
	t_stack	*new;

	new = (t_stack *)malloc(sizeof(t_stack));
	if (new == NULL)
		return (NULL);
	new->value = content;
	new->next = NULL;
	return (new);
}

void	stack_add(t_stack **lst, int value)
{
	t_stack *new;
	new = stack_new(value);
	if (!lst || !(*lst))
		new->next = NULL;
	else
		new->next = *lst;
	*lst = new;
}

void	stack_drop(t_stack **lst)
{
	if(lst && *lst)
	{
		t_stack *next;
		next = (*lst)->next;
		free(*lst);
		*lst = next;
	}
}

