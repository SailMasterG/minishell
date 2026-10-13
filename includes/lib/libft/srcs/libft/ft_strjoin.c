/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chguerre <chguerre@42lausanne.ch>           +#+  +:+       +#+       */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 11:44:42 by chguerre          #+#    #+#             */
/*   Updated: 2025/12/07 20:43:15 by sailmaster       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	size_t	length;
	size_t	i;
	size_t	k;

	length = ft_strlen(s1) + ft_strlen(s2);
	str = (char *)malloc(length + 1);
	if (!str)
		return (NULL);
	i = 0;
	k = 0;
	while (s1[k] != '\0')
	{
		str[i] = s1[k++];
		i++;
	}
	k = 0;
	while (s2[k] != '\0')
	{
		str[i] = s2[k++];
		i++;
	}
	str[i] = '\0';
	return (str);
}

/*
int	main(void)
{
	char	*str1;
	char	*str2;
	char	*res;

	str1= "Soy un gran tipo ";
	str2= "y soy Venezolano.";
	res = ft_strjoin(str1, str2);
	printf("La nueva cadena unida es:\n");
	printf("%s \n ", res);
	return (0);
}
*/
