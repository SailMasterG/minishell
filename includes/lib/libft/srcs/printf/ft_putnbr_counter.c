/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_counter.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chguerre <chguerre@student.lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 19:21:48 by chguerre          #+#    #+#             */
/*   Updated: 2026/02/19 23:59:20 by chguerre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putnbr_counter(int n, int fd)
{
	long	num;
	int		counter;

	counter = 0;
	num = n;
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		num *= -1;
		counter++;
	}
	if (num >= 10)
		counter += ft_putnbr_counter(num / 10, fd);
	ft_putchar_fd(num % 10 + '0', fd);
	counter += 1;
	return (counter);
}
