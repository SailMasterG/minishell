/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chguerre <chguerre@student.lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 22:17:54 by chguerre          #+#    #+#             */
/*   Updated: 2026/02/20 00:03:47 by chguerre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*remainig_buff(char *buff_base)
{
	char	*pos;
	char	*buff_remaining;
	size_t	len;
	int		i;

	pos = ft_strchr(buff_base, '\n');
	if (!pos)
	{
		free(buff_base);
		return (NULL);
	}
	len = ft_strlen(pos + 1);
	buff_remaining = (char *)malloc(len + 1);
	if (!buff_remaining)
		return (free(buff_base), NULL);
	i = 0;
	pos++;
	while (*pos)
	{
		buff_remaining[i] = *pos;
		pos++;
		i++;
	}
	buff_remaining[i] = '\0';
	return (free(buff_base), buff_remaining);
}
