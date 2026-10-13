/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chguerre <chguerre@student.lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/06 07:38:45 by sailmaster        #+#    #+#             */
/*   Updated: 2025/12/09 19:18:28 by chguerre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *pointer1, const void *pointer2, size_t size)
{
	unsigned char	*cadena1;
	unsigned char	*cadena2;

	cadena1 = (unsigned char *)pointer1;
	cadena2 = (unsigned char *)pointer2;
	while (size > 0)
	{
		if (*cadena1 != *cadena2)
			return (*cadena1 - *cadena2);
		size--;
		cadena1++;
		cadena2++;
	}
	return (0);
}
