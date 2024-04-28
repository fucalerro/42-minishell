/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bob <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 22:43:46 by bob               #+#    #+#             */
/*   Updated: 2024/04/28 22:44:24 by bob              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

char	*ft_getenv(char *varname, char **env);
int	does_var_exist(char **env, char *var);
void	export_var(char ***env, char *var);
int	is_varname_valid(char *var);
int	is_varvalue_valid(char *var);
#endif
