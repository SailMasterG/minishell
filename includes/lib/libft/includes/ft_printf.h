/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chguerre <chguerre@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 21:19:33 by chguerre          #+#    #+#             */
/*   Updated: 2026/03/04 16:58:09 by chguerre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft.h"
# include <stdarg.h>

int	ft_printf(const char *str, ...);
int	printargs(char **str, va_list *args);
int	ft_putstr_counter(char *s);
int	ft_putnbr_counter(int n, int fd);
int	ft_putpointer(void *pointer);

int	ft_putchar_counter(char c);
int	ft_print_xx(unsigned int num, char x);
int	ft_putnbr_unsigned(int n, int fd);

#endif // FT_PRINTF_H
