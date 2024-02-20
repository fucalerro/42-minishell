/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lferro <lferro@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 11:18:30 by lferro            #+#    #+#             */
/*   Updated: 2023/11/13 16:52:43 by lferro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "../libft.h"
# include <stdarg.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>

typedef unsigned long long	t_ull;

// Helper functions
void	ft_putnbr_ll(long long n);
char	*dectohex_str(unsigned int decnbr);
char	*dectohex_sptr(t_ull decnbr);
char	*dectohex_scap(unsigned int decnbr);
t_ull	nbr_count_digit(long long n);
t_ull	print_int(int nbr);
t_ull	print_str(char *str);
t_ull	print_char(char c);
t_ull	print_uint(unsigned int nbr);
int		conv_matcher(char c);
t_ull	conv_printer(char const c, va_list args);
void	ft_putnbr_uint(t_ull n);
char	*revtab(char *tab);
int		ft_printf(const char *s, ...);

#endif
