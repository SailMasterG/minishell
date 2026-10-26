/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bultin_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chguerre <chguerre@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/24 11:06:18 by chguerre          #+#    #+#             */
/*   Updated: 2026/10/26 19:49:16 by rpinheir         ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/include.h"

int	env_pos(char **envp, char *key)
{
	int		i;
	int		len;

	len = ft_strlen(key);
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

int	cmp_names(char *a, char *b)
{
	int	i;

	i = 0;
	while (a[i] == b[i] && a[i] != '\0' && a[i] != '=')
	{
		i++;
	}
	if (a[i] == '=')
		return (-1);
	else if (b[i] == '=')
		return (1);
	return ((unsigned char)a[i] - (unsigned char)b[i]);
}

void	sort_env(char **env)
{
	int		i;
	char	*tmp;
	bool	swapped;

	swapped = true;
	while (swapped)
	{
		swapped = false;
		i = -1;
		while (env[++i + 1])
		{
			if (cmp_names(env[i], env[i + 1]) > 0)
			{
				tmp = env[i];
				env[i] = env[i + 1];
				env[i + 1] = tmp;
				swapped = true;
			}
		}
	}
	display_export(env);
}
