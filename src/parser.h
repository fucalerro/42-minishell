/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicolli <lnicolli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 22:12:43 by Lu-ni             #+#    #+#             */
/*   Updated: 2024/04/30 12:31:35 by lnicolli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# define SINGLE_QUOTE 1
# define DOUBLE_QUOTE 2

# define SINGLE 1
# define DOUBLE 2
# define NONE 0

# define QUOTED 1
# define UNQUOTED 0

# define NO_QUOTES 'N'
# define S_QUOTES 'S'
# define D_QUOTES 'D'

# define CLOSED_QUOTES 0
# define OPEN_QUOTES 1

typedef struct s_tokens
{
	char	*tok;
	int		quote;
	char	*is_in_quotes;
	int		unclosed_quote;
}			t_tokens;

typedef struct s_tokenzied
{
	char	*normalized;
	char	**space_tok;
	char	***op_tok;
	char	**tok;
}			t_tokenized;

int			is_in_quotes(char *input, int index);
char		*all_quotes_remover(char *string);
int			is_quotes_opened(char *string);

#endif
