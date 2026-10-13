/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chguerre <chguerre@student.lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 10:07:36 by chguerre          #+#    #+#             */
/*   Updated: 2025/12/09 21:12:29 by chguerre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	lentotal;
	size_t	len_s;

	if (s == NULL)
		return (NULL);
	len_s = ft_strlen(s);
	if (start >= (unsigned int)len_s)
	{
		str = malloc(1);
		if (str == NULL)
			return (NULL);
		str[0] = '\0';
		return (str);
	}
	lentotal = len;
	if (lentotal > (size_t)len_s - start)
		lentotal = len_s - start;
	str = (char *)malloc((lentotal + 1));
	if (!str)
		return (NULL);
	ft_memcpy(str, &s[start], lentotal);
	str[lentotal] = '\0';
	return (str);
}
/*
int	main(void)
{
	char	*str;
	char	*substring;

	str = "odontologo";
	substring = ft_substr(str, 0, 10);
	printf("%s \n", str);
	printf("La nueva subcadena es: %s \n ", substring);
	return (0);
}
*/
