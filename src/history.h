/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Lu-ni <lucas.nicollier@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 22:12:43 by Lu-ni             #+#    #+#             */
/*   Updated: 2024/04/28 22:12:43 by Lu-ni            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HISTORY_H
# define HISTORY_H

typedef struct s_hist
{
	char			*line;
	struct s_hist	*previous;
	struct s_hist	*next;
}					t_hist;

void				add_to_history(char *line);
void				print_hist(char **env);
int					ft_write_history_file(char *line, char **env);
char				*get_history_path(char **env);
void				ft_read_history(char **env);

#endif
