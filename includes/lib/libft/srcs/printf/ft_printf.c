/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chguerre <chguerre@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 21:12:23 by chguerre          #+#    #+#             */
/*   Updated: 2026/03/04 18:21:12 by chguerre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf(const char *str, ...)
{
	va_list	args;
	int		count;

	va_start(args, str);
	count = 0;
	while (*str != '\0')
	{
		if (*str == '%')
		{
			if (*(str + 1) != '\0' && ft_strchr("cspdiuxX%", *(str + 1)))
			{
				count += printargs((char **)&str, &args);
				str++;
			}
			else
				return (-1);
			continue ;
		}
		ft_putchar_fd(*str, 1);
		count++;
		str++;
	}
	va_end(args);
	return (count);
}
