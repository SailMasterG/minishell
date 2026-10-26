/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bultin_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chguerre <chguerre@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/24 11:06:18 by chguerre          #+#    #+#             */
/*   Updated: 2026/10/26 17:32:57 by rpinheir         ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/include.h"

int	env_pos(char **envp, char *key)
{
	int		i;
	int		len;

	len = strlen(key);
	i = 0;
	while (envp[i] != NULL)
	{
		if (ft_strncmp(envp[i], key, len) == 0 && (envp[i][len] == '='
			|| envp[i][len] == '\0' ))
			return (i);
		i++;
	}
	return (-1);
}
