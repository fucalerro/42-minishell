#include "minishell.h"

int     count_files_in_dir(char *dirname)
{
    DIR             *d;
    struct dirent   *dir;
    int             file_count;

    d = opendir(dirname);
    file_count = 0;
    if (d)
    {
        while ((dir = readdir(d)) != NULL)
            file_count++;
        closedir(d);
    }
    return (file_count);
}

char    **get_files_list(char *dirname)
{
    DIR             *d;
    struct dirent   *dir;
    char            **files_list;
    int             i;

    files_list = malloc((count_files_in_dir(dirname) + 1) * sizeof(char *));
    i = 0;
    d = opendir(dirname);
    if (d)
    {
        while ((dir = readdir(d)) != NULL)
        {
            if (dir->d_name[0] != '.')
            {
                files_list[i] = ft_strdup(dir->d_name);
                printf("%s\n", files_list[i]);
                i++;
            }
        }
    }
    files_list[i] = NULL;
    return (files_list);
}


// char    *find_segment(char *string, int start)
// {
//     char    *found;

//     while


//     ft_strstr(string, )
// }



char    **wildcard_expansion(char *pattern)
{
    int i;

    char    **files_matched;

    i = 0;
    if (ft_strchr(pattern, '*'))
    {
        while (pattern[i] != '*' && pattern[i])
        {

        }








    }
}
