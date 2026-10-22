/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bultin_pwd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chguerre <chguerre@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/22 18:49:45 by chguerre          #+#    #+#             */
/*   Updated: 2026/10/22 18:51:22 by chguerre         ###   ########.fr       */
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
	ft_putendl_fd(buf, STDOUT_FILENO);
	return (0);
}
