/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_xX.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chguerre <chguerre@student.lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 20:04:34 by chguerre          #+#    #+#             */
/*   Updated: 2026/02/19 23:58:38 by chguerre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	printhex(unsigned long num, char *base)
{
	int	counter;

	counter = 0;
	if (num >= 16)
		counter += printhex(num / 16, base);
	ft_putchar_fd(base[num % 16], 1);
	counter++;
	return (counter);
}

int	ft_print_xx(unsigned int num, char x)
{
	int		count;
	char	*base;

	count = 0;
	if (x == 'X')
		base = "0123456789ABCDEF";
	else
		base = "0123456789abcdef";
	if (num >= 16)
	{
		count += printhex(num / 16, base);
	}
	ft_putchar_fd(base[num % 16], 1);
	count++;
	return (count);
}
