#ifndef PARSER_H
#define PARSER_H

#define SINGLE_QUOTE 1
#define DOUBLE_QUOTE 2

int is_in_quotes(char *input, int index);
int	parser(char *input);

#endif
