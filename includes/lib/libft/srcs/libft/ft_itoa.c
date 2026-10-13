/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chguerre <chguerre@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 18:03:18 by chguerre          #+#    #+#             */
/*   Updated: 2025/12/08 18:03:40 by chguerre         ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
//#include <stdio.h>

int	is_negative(long *num, int *sing)
{
	if (*num < 0)
	{
		*num *= -1;
		*sing = 1;
		return (1);
	}
	return (0);
}

int	counter(long num)
{
	int	counter;

	counter = 0;
	if (num <= 0)
		counter = 1;
	while (num != 0)
	{
		num = num / 10;
		counter ++;
	}
	return (counter);
}

char	*ft_itoa(int n)
{
	long	aux;
	int		num_digits;
	char	*stringnum;
	int		simbol;

	aux = (long)n;
	num_digits = 0;
	simbol = 0;
	is_negative(&aux, &simbol);
	num_digits = counter((long)n);
	stringnum = (char *)malloc(num_digits + 1);
	if (stringnum == NULL)
		return (NULL);
	stringnum[num_digits] = '\0';
	while (num_digits-- > simbol)
	{
		stringnum[num_digits] = (aux % 10) + '0';
		aux = aux / 10;
	}
	if (simbol == 1)
		stringnum[0] = '-';
	return (stringnum);
}
/*
int	main(void)
{
	int		num;
	char	*resultado;

	num = -2082712576;
	resultado = ft_itoa(num);
	printf("Entero convertido en cadena:\n %s\n", resultado);
	return (0);
}
*/