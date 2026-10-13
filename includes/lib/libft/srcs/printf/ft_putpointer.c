/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putpointer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chguerre <chguerre@student.lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 23:32:59 by chguerre          #+#    #+#             */
/*   Updated: 2026/02/19 23:59:31 by chguerre         ###   ########.fr       */
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

int	ft_putpointer(void *pointer)
{
	int				counter;
	unsigned long	temp;
	char			*base;

	counter = 0;
	temp = (unsigned long)pointer;
	base = "0123456789abcdef";
	if (temp == 0)
	{
		ft_putstr_fd("(nil)", 1);
		return (5);
	}
	ft_putstr_fd("0x", 1);
	counter += printhex(temp, base);
	return (counter + 2);
}
