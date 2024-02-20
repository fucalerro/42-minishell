/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isspace.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lferro <lferro@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 13:36:09 by lferro            #+#    #+#             */
/*   Updated: 2024/02/20 13:48:47 by lferro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isspace(const char c)
{
	if (c == ' ' || c == '\t' || c == '\f' || c == '\r' || c == '\v' || c == '\n')
		return (c);
	return (0);
}
