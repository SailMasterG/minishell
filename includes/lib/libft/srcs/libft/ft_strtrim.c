/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chguerre   </var/spool/mail/sailmaster>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 20:41:32 by sailmaster        #+#    #+#             */
/*   Updated: 2025/12/08 08:45:42 by sailmaster       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;
	size_t	size_trim;

	start = 0;
	if (!s1 || !set)
		return (NULL);
	while (*s1 && ft_strchr(set, s1[start]))
	{
		start++;
	}
	if (s1[start] == '\0')
		return (ft_strdup(""));
	end = ft_strlen(s1) - 1;
	while (end >= start && ft_strchr(set, s1[end]))
	{
		end--;
	}
	size_trim = (end - start) + 1;
	return (ft_substr(s1, start, size_trim));
}
