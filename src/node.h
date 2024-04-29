/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicolli <lnicolli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 22:12:43 by Lu-ni             #+#    #+#             */
/*   Updated: 2024/04/29 14:52:55 by lnicolli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NODE_H
# define NODE_H

# define T_PIPE 1
# define T_INFILE 2
# define T_HEREDOC 3
# define T_CMD 4
# define T_OUTFILE 5
# define T_OUTFILE_APPEND 6

# define PIPE_NEXT 1
# define PIPE_PREVIOUS 2

typedef struct s_node
{
	int				type;
	int				active;
	char			*file;
	char			**cmd;
	struct s_node	*next;
	struct s_node	*previous;
	char			*delimiter;
	int				pipe[2];
}					t_node;

void	lst_append(t_node **lst, int type, char **cmd, char *arg[2]);
void				free_lst(t_node *lst);

#endif
