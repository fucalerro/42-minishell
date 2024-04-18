#include "minishell.h"

/**
 * @brief get the number of element in a 3d array
 *
 * @param array3d 3d array
 * @return size of the array
 */
int	get_3darray_size(char ***array3d)
{
	int	i;
	int	j;
	int	size;

	i = 0;
	j = 0;
	size = 0;
	while (array3d[i])
	{
		while (array3d[i][j++])
			size++;
		j = 0;
		i++;
	}
	return (size);
}

/**
 * @brief flatten a 3d array into a 2d array
 *
 * @param array3d 3d array to flatten
 * @return char** 2d array
 */
char	**flatten_3d_array(char ***array3d)
{
	char	**arr_flatten;
	int		i;
	int		j;
	int		k;
	int		array3d_size;

	i = 0;
	j = 0;
	k = 0;
	array3d_size = get_3darray_size(array3d);
	arr_flatten = malloc((array3d_size + 1) * sizeof(char *));
	while (array3d[i])
	{
		while (array3d[i][j])
		{
			arr_flatten[k++] = ft_strdup(array3d[i][j]);
			free(array3d[i][j]);
			j++;
		}
		free(array3d[i]);
		j = 0;
		i++;
	}
	arr_flatten[k] = 0;
	free(array3d);
	return (arr_flatten);
}

/**
 * @brief get the number of elems in an array
 *
 */
int	get_elem_count_tok(t_tokens **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		i++;
	}
	return (i);
}

int	get_elem_count_arr(char **array)
{
	int	i;

	i = 0;
	while (array[i])
		i++;
	return (i);
}

void	print_string_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		printf("%s\n", tab[i]);
		i++;
	}
}

void	print_tokens(t_tokens **tokens)
{
	int	i;

	i = 0;
	while (tokens[i])
	{
		printf("token: %s\n", tokens[i]->token);
		printf("type:  %d\n\n", tokens[i]->quoted);
		i++;
	}
}

void	free_string_array(char **strings)
{
	int	i;

	i = 0;
	while (strings[i])
	{
		free(strings[i]);
		i++;
	}
	free(strings);
}

char	*flatten_2d_array(char **array)
{
	char	*res;
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	k = 0;
	while (array[i])
	{
		while (array[i][j])
		{
			k++;
			j++;
		}
		j = 0;
		i++;
	}
	res = malloc(sizeof(char) * (k + 1));
	i = 0;
	j = 0;
	k = 0;
	while (array[i])
	{
		while (array[i][j])
		{
			res[k++] = array[i][j];
			j++;
		}
		j = 0;
		i++;
	}
	res[k] = 0;
	return (res);
}
