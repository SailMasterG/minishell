/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printarg.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chguerre <chguerre@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 11:17:48 by chguerre          #+#    #+#             */
/*   Updated: 2026/03/04 18:20:14 by chguerre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/**We recieve the pointer actual, and
 * verify the type of arg, if
 * there not a valid format, we return
 *  0 value if not we return the quantity of caracaters printed.
 */
int	printargs(char **str, va_list *args)
{
	(*str)++;
	if (**str == 'd')
		return (ft_putnbr_counter(va_arg(*args, int), 1));
	else if (**str == 's')
		return (ft_putstr_counter(va_arg(*args, char *)));
	else if (**str == '%')
		return (ft_putchar_counter('%'));
	else if (**str == 'c')
		return (ft_putchar_counter(va_arg(*args, int)));
	else if (**str == 'i')
		return (ft_putnbr_counter(va_arg(*args, int), 1));
	else if (**str == 'u')
		return (ft_putnbr_unsigned(va_arg(*args, unsigned int), 1));
	else if (**str == 'x')
		return (ft_print_xx(va_arg(*args, unsigned int), 'x'));
	else if (**str == 'X')
		return (ft_print_xx(va_arg(*args, unsigned int), 'X'));
	else if (**str == 'p')
	{
		return (ft_putpointer(va_arg(*args, void *)));
	}
	else
		return (0);
	return (1);
}
