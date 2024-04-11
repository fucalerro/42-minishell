#ifndef PARSER_H
#define PARSER_H

#define SINGLE_QUOTE    1
#define DOUBLE_QUOTE    2

#define SINGLE          1
#define DOUBLE          2
#define NONE            0

#define QUOTED          1
#define UNQUOTED        0


typedef struct s_tokens
{
    char    *token;
    int     type;
    char    *is_in_quotes;
}           t_tokens;


int is_in_quotes(char *input, int index);
char    *all_quotes_remover(char *string);

#endif
