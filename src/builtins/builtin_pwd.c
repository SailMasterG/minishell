/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chguerre <chguerre@student.lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/22 18:49:45 by chguerre          #+#    #+#             */
/*   Updated: 2026/10/23 09:36:18 by chguerre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/include.h"

int	builtin_pwd(t_shell *shell, char **cmd_args)
{
	char	buf[PATH_MAX];

	(void)shell;
	(void)cmd_args;
	if (getcwd(buf, sizeof(buf)) == NULL)
	{
		perror("pwd");
		return (1);
	}
	ft_putendl_fd("¡ESTE ES MI PROPIO BUILTIN DE PWD!", STDOUT_FILENO);	ft_putendl_fd(buf, STDOUT_FILENO);
	return (0);
}
