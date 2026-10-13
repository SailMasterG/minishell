/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masterg <masterg@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 14:04:38 by masterg           #+#    #+#             */
/*   Updated: 2025/12/03 19:53:50 by masterg          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char		*ptr;
	const char	*src_ptr;

	src_ptr = (const char *)src;
	ptr = (char *)dest;
	if (ptr == NULL && src_ptr == NULL)
		return (0);
	while (n > 0)
	{
		*ptr++ = *src_ptr++;
		n--;
	}
	return (dest);
}
