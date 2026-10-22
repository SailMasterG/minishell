/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chguerre <chguerre@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/22 21:13:40 by chguerre          #+#    #+#             */
/*   Updated: 2026/10/22 21:13:51 by chguerre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/include.h"

int	builtin_exit(t_shell *shell, char **cmd_args)
{
	(void)shell;
	(void)cmd_args;
	return (1);
}
