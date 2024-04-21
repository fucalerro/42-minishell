#include "minishell.h"

void *palloc(int size, int elem_size)
{
	void	*res;

	res = malloc(elem_size * (size + 1));
	if (!res)
		return (NULL);
	return (res);
}
