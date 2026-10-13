/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masterg <masterg@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 20:39:39 by masterg           #+#    #+#             */
/*   Updated: 2025/12/03 22:12:37 by masterg          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	len;
	size_t	i;
	size_t	srclen;

	len = 0;
	srclen = 0;
	i = 0;
	while (dst[len] && len < dstsize)
		len++;
	while (src[srclen])
		srclen++;
	if (len >= dstsize)
		return (len + srclen);
	while ((len + i < dstsize - 1) && src[i] != '\0')
	{
		dst[len + i] = src[i];
		i++;
	}
	dst[len + i] = '\0';
	return (len + srclen);
}
/*
int	main(void)
{
	char	*src;
	char	dest[30] = "Hola ";

	src = "Mundo";

	printf("Cadena a concatenar: %s \n", src);
	printf("Cadena a donde se agregara la src %s \n", dest);
	ft_strlcat(dest, src, 8);
	printf("Cadena dest= %s", dest);
	return (0);
}
*/