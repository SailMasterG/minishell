/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_unsigned.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chguerre <chguerre@student.lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 20:35:52 by chguerre          #+#    #+#             */
/*   Updated: 2026/02/19 23:59:26 by chguerre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_putnbr_count(unsigned int n, int fd)
{
	int	counter;

	counter = 0;
	if (n >= 10)
		counter += ft_putnbr_count(n / 10, fd);
	ft_putchar_fd(n % 10 + '0', fd);
	counter++;
	return (counter);
}

int	ft_putnbr_unsigned(int n, int fd)
{
	unsigned long	num;
	int				counter;

	counter = 0;
	num = n;
	counter += ft_putnbr_count(num, fd);
	return (counter);
}
