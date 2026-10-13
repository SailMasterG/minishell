/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_counter.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chguerre <chguerre@student.lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 21:16:30 by chguerre          #+#    #+#             */
/*   Updated: 2026/02/19 23:59:45 by chguerre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putstr_counter(char *s)
{
	int		fcounter;
	char	*null;

	null = "(null)";
	fcounter = 0;
	if (s == NULL)
	{
		while (null[fcounter] != '\0')
		{
			ft_putchar_fd(null[fcounter], 1);
			fcounter++;
		}
		return (fcounter);
	}
	while (*s != '\0')
	{
		ft_putchar_fd(*s, 1);
		fcounter++;
		s++;
	}
	return (fcounter);
}
