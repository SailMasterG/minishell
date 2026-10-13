/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chguerre <youremail@student.42lausanne.ch> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/06 20:55:49 by yourlogin         #+#    #+#             */
/*   Updated: 2025/12/07 20:47:37 by sailmaster       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t n)
{
	size_t	str_len;
	size_t	i;

	str_len = 0;
	i = 0;
	while (src[str_len] != '\0')
	{
		str_len++;
	}
	if (n == 0)
		return (str_len);
	while (i < (n - 1) && src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (str_len);
}
/*
int	main(void)
{
	char		dest[10];
	const char	*src = "123456";
	size_t		len;

	len = ft_strlcpy(dest, src, 4);
	printf("Dest: '%s', Len: %zu\n", dest, len); // Dest: '123', Len: 6
	len = ft_strlcpy(dest, src, 0);
	printf("Dest: '%s', Len: %zu\n", dest, len); // Dest no cambia, Len: 6
	len = ft_strlcpy(dest, src, 10);
	printf("Dest: '%s', Len: %zu\n", dest, len); // Dest: '123456', Len: 6
	return (0);
}
*/
