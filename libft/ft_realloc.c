/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lferro <lferro@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 18:01:49 by lferro            #+#    #+#             */
/*   Updated: 2024/02/25 18:12:19 by lferro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void    *ft_realloc(void *ptr, size_t old_size, size_t size)
{
    void    *new_block;

    if (ptr == NULL)
        return (ptr);
    if (old_size == size)
        return (ptr);
    new_block = malloc(size);
    if (new_block == NULL)
        return (NULL);
    if (old_size < size)
        ft_memcpy(new_block, ptr, old_size);
    else
        ft_memcpy(new_block, ptr, old_size);
    free(ptr);
    return (new_block);
}
