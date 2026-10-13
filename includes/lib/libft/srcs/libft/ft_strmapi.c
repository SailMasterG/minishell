/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chguerre <chguerre@student.lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 09:17:56 by chguerre          #+#    #+#             */
/*   Updated: 2025/12/09 14:59:08 by chguerre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

/**
 * ft_strmapi applies a function to each character of a given string.
 *
 * The function takes two parameters, an unsigned int and a char, and
 * returns a char.
 *
 * The returned string is a new string that is the result of applying
 * the function to each character of the given string.
 *
 * @param s the given string
 * @param f the function to apply to each character
 * @return a new string with the result of applying the function to each
 * character of the given string
 */

char	*ft_strmapi(const char *s, char (*f)(unsigned int, char))
{
	char	*str;
	int		index;
	int		len;

	len = ft_strlen(s);
	str = (char *)malloc(len + 1);
	if (str == NULL)
		return (NULL);
	index = 0;
	while (index < len)
	{
		str[index] = (*f)(index, s[index]);
		index++;
	}
	str[len] = '\0';
	return (str);
}
