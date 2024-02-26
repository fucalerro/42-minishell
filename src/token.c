#include "minishell.h"

int is_single_op(char *string, int i)
{
    char    *single_op = "&|<>()";

    if (string[i] && ft_strchr(single_op, string[i]))
        return (true);
    return (false);
}

int is_double_op(char *string, int i)
{
    char    *double_op[] = { "&&", "||", "<<", ">>" };
    int     op_index;

    if (string[i] == 0 || string[i + 1] == 0)
        return false;

    op_index = 0;
    while (op_index < 4)
    {
        if (ft_strncmp(&string[i], double_op[op_index], 2) == 0)
            return (true);
        op_index++;
    }
    return (false);
}


char    **op_tokeniser(char *string)
{
    char    **res;
    char    *token;
    int     flag;
    int     i;
    int     len;
    int     j;

    flag = 0;
    i = 0;
    len = 0;
    j = 0;

    res = malloc(sizeof(char *) * 10);

    while (string[i])
    {
        if (is_double_op(string, i) && flag != 1)
        {
            flag = 1;
            res[j] = ft_substr(string, i, 2);
            printf("token: %s\n", res[j]);
            j++;
            // i++;
        }
        else if (is_single_op(string, i) && flag != 1)
        {
            flag = 1;
            res[j] = ft_substr(string, i, 1);
            printf("token: %s\n", res[j]);
            j++;
        }
        else
        {
            int start = i;
            while (string[i] != 0 && !is_double_op(string, i) && !is_single_op(string, i))
            {
                i++;
            }
            res[j] = ft_substr(string, start, i - start);
            printf("token: %s\n", res[j]);
            j++;
            flag = 0;
        }
        i++;
    }
    return (res);
}

            // printf("token: %s  for index: %d\n", token, i);
            // printf("token: %s   for index: %d\n", token, i);
            // printf("token: %s for index: %d\n", token, i);


char	**sp_tokeniser(char *string, char c)
{
	size_t	i;
	size_t	j;
	int		index;
	char	**res;

	i = 0;
	j = 0;
	index = -1;
	res = malloc((wordcounter(string, c) + 1) * sizeof(char *));
	if (res == 0)
		return (0);
	while (i <= ft_strlen(string))
	{
		if (string[i] != c && index < 0)
			index = i;
		else if ((string[i] == c || i == ft_strlen(string)) && index >= 0 && is_in_quotes(string, i) == 0)
		{
			res[j++] = wordmaker(string, index, i);
			index = -1;
		}
		i++;
	}
	res[j] = 0;
	return (res);

}
