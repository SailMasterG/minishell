/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chguerre <chguerre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 21:30:45 by masterg           #+#    #+#             */
/*   Updated: 2025/12/10 18:57:02 by chguerre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	char	*dernier_mach;

	dernier_mach = NULL;
	while (*str != '\0')
	{
		if (*str == (char)c)
		{
			dernier_mach = (char *) str;
		}
		str++;
	}
	if ((char)c == '\0')
		dernier_mach = (char *) str;
	return (dernier_mach);
}
