/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masterg <masterg@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 14:11:30 by masterg           #+#    #+#             */
/*   Updated: 2025/12/03 14:40:39 by masterg          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char		*dest_ptr;
	const char	*src_ptr;
	size_t		i;

	dest_ptr = (char *)dest;
	src_ptr = (const char *)src;
	i = 0;
	if (!dest_ptr && !src_ptr)
		return (0);
	if (dest_ptr < src_ptr)
	{
		while (i < n)
		{
			dest_ptr[i] = src_ptr[i];
			i++;
		}
	}
	else
	{
		while (n--)
		{
			dest_ptr[n] = src_ptr[n];
		}
	}
	return (dest);
}
