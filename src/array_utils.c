#include "minishell.h"

/**
 * @brief get the number of element in a 3d array
 *
 * @param array3d 3d array
 * @return size of the array
 */
int get_3darray_size(char ***array3d)
{
    int i;
    int j;
    int size;

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
char **flatten_3d_array(char ***array3d)
{
    char **arr_flatten;

    int i;
    int j;
    int k;
    int array3d_size;

    i = 0;
    j = 0;
    k = 0;
    array3d_size = get_3darray_size(array3d);
    arr_flatten = malloc((array3d_size + 1) * sizeof(char *));
    while (array3d[i])
    {
        while (array3d[i][j])
            arr_flatten[k++] = ft_strdup(array3d[i][j++]);
        j = 0;
        i++;
    }
    arr_flatten[k] = 0;
    return arr_flatten;
}

