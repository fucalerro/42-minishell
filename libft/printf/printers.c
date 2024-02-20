/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lferro <lferro@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 15:21:06 by lferro            #+#    #+#             */
/*   Updated: 2023/10/25 12:04:55 by lferro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

// Print an integer
// Param:	Integer to print
// Return:	Number of char printed
t_ull	print_int(int nbr)
{
	t_ull	count;

	count = nbr_count_digit(nbr);
	ft_putnbr_fd(nbr, 1);
	return (count);
}

// Print an unsigned integer
// Param:	Unsigned integer to print
// Return:	Number of char printed
t_ull	print_uint(unsigned int nbr)
{
	t_ull	count;

	count = nbr_count_digit(nbr);
	ft_putnbr_uint(nbr);
	return (count);
}

// Print a string
// Param:	String to print
// Return:	Number of char printed
t_ull	print_str(char *str)
{
	t_ull	count;

	if (str == NULL)
	{
		ft_putstr_fd("(null)", 1);
		return (6);
	}
	count = ft_strlen(str);
	ft_putstr_fd(str, 1);
	return (count);
}

// Print a character
// Param:	Char to print
// Return:	Number of char printed (1)
t_ull	print_char(char c)
{
	ft_putchar_fd(c, 1);
	return (1);
}
