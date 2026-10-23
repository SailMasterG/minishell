/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chguerre <chguerre@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/22 21:13:16 by chguerre          #+#    #+#             */
/*   Updated: 2026/10/23 15:57:50 by chguerre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/include.h"

int	builtin_echo(t_shell *shell, char **cmd_args)
{
	int	i;
	int	is_flaged;

	(void) shell;
	is_flaged = 0;
	i = 1;
	while (cmd_args[i] && ft_strncmp(cmd_args[i], "-n", 3) == 0)
	{
		is_flaged = 1;
		i++;
	}
	while (cmd_args[i])
	{
		ft_putstr_fd(cmd_args[i], 1);
		if (cmd_args[i + 1] != NULL)
			write(1, " ", 1);
		i ++;
	}
	if (!is_flaged)
		write(1, "\n", 1);
	return (0);
}
