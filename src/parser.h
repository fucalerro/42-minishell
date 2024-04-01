#ifndef PARSER_H
#define PARSER_H

#define SINGLE_QUOTE    1
#define DOUBLE_QUOTE    2

#define SINGLE          1
#define DOUBLE          2
#define NONE            0

#define ERR_UNCLOSED_QUOTE  1
#define ERR_UNEXPECTED_TOKEN 2
#define ERR_
#define ERR_



int is_in_quotes(char *input, int index);

#endif
