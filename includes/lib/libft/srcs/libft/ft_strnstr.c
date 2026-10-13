/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chguerre <chguerre@student.lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/06 10:24:39 by sailmaster        #+#    #+#             */
/*   Updated: 2025/12/09 20:01:35 by chguerre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	k;

	i = 0;
	k = 0;
	if (*little == '\0')
		return ((char *)&big[i]);
	while (i < len && big[i])
	{
		while (little[k] == big[k + i] && (little[k] != '\0') && (k + i < len))
		{
			k++;
		}
		if (little[k] == '\0')
			return ((char *)&big[i]);
		k = 0;
		i++;
	}
	return (NULL);
}
