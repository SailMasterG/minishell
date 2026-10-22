/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chguerre <chguerre@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/22 14:32:50 by chguerre          #+#    #+#             */
/*   Updated: 2026/10/22 18:54:50 by chguerre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/include.h"

static int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return ((unsigned char)*s1 - (unsigned char)*s2);
}

t_builtin	get_builtin(char *name)
{
	if (name == NULL)
		return (NULL);
	if (ft_strcmp(name, "echo") == 0)
		return (1);
	//	return (builtin_echo);
	if (ft_strcmp(name, "cd") == 0)
		return (1);
	if (ft_strcmp(name, "pwd") == 0)
		return (builtin_pwd);
	if (ft_strcmp(name, "export") == 0)
		return (1);
	//	return (builtin_export);
	if (ft_strcmp(name, "unset") == 0)
		return (1);
	//	return (builtin_unset);
	if (ft_strcmp(name, "env") == 0)
		return (1);
	//	return (builtin_env);
	if (ft_strcmp(name, "exit") == 0)
		return (1);
	//	return (builtin_exit);
	return (NULL);
}
