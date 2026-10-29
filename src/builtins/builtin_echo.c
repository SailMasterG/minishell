/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chguerre <chguerre@student.lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/22 21:13:16 by chguerre          #+#    #+#             */
/*   Updated: 2026/10/26 20:38:04 by chguerre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/include.h"

static bool	is_n_flag(char *arg)
{
	int	j;

	if (arg[0] != '-' || arg[1] != 'n')
		return (false);
	j = 1;
	while (arg[j] == 'n')
		j++;
	return (arg[j] == '\0');
}

int	builtin_echo(t_shell *shell, char **cmd_args)
{
	int		i;
	bool	newline;

	(void)shell;
	i = 1;
	newline = true;
	while (cmd_args[i] && is_n_flag(cmd_args[i]))
	{
		newline = false;
		i++;
	}
	while (cmd_args[i])
	{
		ft_putstr_fd(cmd_args[i], 1);
		if (cmd_args[i + 1])
			write(1, " ", 1);
		i++;
	}
	if (newline)
		write(1, "\n", 1);
	return (0);
}
