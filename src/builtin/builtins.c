/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chguerre <chguerre@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/22 14:32:50 by chguerre          #+#    #+#             */
/*   Updated: 2026/10/22 15:11:43 by chguerre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/include.h"

t_builtin	get_builtin(char *name)
{
	if (name == NULL)
		return (NULL);
	if (ft_strcmp(name, "echo") == 0)
		return (builtin_echo);
	if (ft_strcmp(name, "cd") == 0)
		return (builtin_cd);
	if (ft_strcmp(name, "pwd") == 0)
		return (builtin_pwd);
	if (ft_strcmp(name, "export") == 0)
		return (builtin_export);
	if (ft_strcmp(name, "unset") == 0)
		return (builtin_unset);
	if (ft_strcmp(name, "env") == 0)
		return (builtin_env);
	if (ft_strcmp(name, "exit") == 0)
		return (builtin_exit);
	return (NULL);
}
