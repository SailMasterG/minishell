/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chguerre <chguerre@student.lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 16:56:01 by chguerre          #+#    #+#             */
/*   Updated: 2025/12/09 13:05:46 by chguerre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

int	ft_toupper(int c)
{
	if (c >= 'a' && c <= 'z')
		return (c -= 32);
	return (c);
}

/*
int	main(void)
{
	char	caracter;

	caracter = 's';
	printf("Letra ingresada es: %c", caracter);
	printf("Letra convertida %c", ft_toupper(caracter));
	return (0);
}
*/
