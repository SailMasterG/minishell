/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saouissi <saouissi@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 13:01:33 by rpinheir          #+#    #+#             */
/*   Updated: 2026/07/20 19:40:01 by saouissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/include.h"


int	main(int ac, char **av, char **environ)
{
	t_shell	shell;

	if (ac > 1 && av[0])
		return (1);
	shell.pids = NULL;
	shell.print_newline = true;
	shell.env = NULL; // copy env
	(void)environ;
	shell.cmds = NULL;
	if (shell.cmds)
		printf("Free cmds");
	return (0);
}
