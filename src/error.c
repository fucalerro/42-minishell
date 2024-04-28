#include "minishell.h"

void	write_err(char *str)
{
	int	size;

	size = ft_strlen(str);
	write(2, str, size);
}
