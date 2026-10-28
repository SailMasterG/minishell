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

bool	is_flagged(char **cmd_args)
{
	int		i;
	int		j;
	bool	is_flagged;

	i = 0;
	j = 0;
	is_flagged = false;
	while (cmd_args[i])
	{
		while (cmd_args[i][j])
		{
			if (cmd_args[i][j] != '-' || cmd_args[i][j] != 'n')
				is_flagged = false;
			while (*cmd_args[i] == 'n')
				i++;
			if (cmd_args[i][j] == '\0')
				is_flagged = true;
			else
				is_flagged = false;
			j++;
		}
		i++;
	}
	return (is_flagged);
}

int	builtin_echo(t_shell *shell, char **cmd_cmd_argss)
{
	int	i;
	int	j;

	(void) shell;
	i = 1;
	j = 0;
	while (cmd_cmd_argss[i])
	{
		if (cmd_cmd_argss[i][j] != 'n' && ft_strncmp(cmd_cmd_argss[i], "-n", 2)
			&& cmd_cmd_argss[i][j] != ' ')
			ft_putstr_fd(cmd_cmd_argss[i], 1);
		if (cmd_cmd_argss[i][j] != 'n' && ft_strncmp(cmd_cmd_argss[i], "-n", 2)
			&& cmd_cmd_argss[i][j] != ' ')
			write(1, " ", 1);
		i++;
	}
	if (!&is_flagged)
		write(1, "\n", 1);
	return (0);
}
