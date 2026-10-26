/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chguerre <chguerre@student.lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/22 21:15:05 by chguerre          #+#    #+#             */
/*   Updated: 2026/10/26 20:38:56 by chguerre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/include.h"

int	builtin_env(t_shell *shell, char **cmd_args)
{
	char	*simbol_equal;
	int		i;

	i = 0;
	if (cmd_args[1] != NULL)
		return (0);
	while (shell->env[i])
	{
		simbol_equal = ft_strchr(shell->env[i], '=');
		if (simbol_equal != NULL)
		{
			ft_putendl_fd(shell->env[i], 1);
		}
		i++;
	}
	return (1);
}
