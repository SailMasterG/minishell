/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chguerre <chguerre@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/19 20:56:52 by chguerre          #+#    #+#             */
/*   Updated: 2026/10/19 20:58:07 by chguerre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/include.h"

void setup_child_pipes(t_shell *shell, int i, int *fd)
{
	if (shell->prevfd != -1)
	{
		if(dup2(shell->prevfd, STDIN_FILENO) == -1)
		{
			perror("dup2");
			childs_exit(shell, i, fd, 1);
		}
		close(shell->prevfd);
	}
	if (i < shell->cmd_count - 1)
	{
		if(dup2(fd[1], STDOUT_FILENO) == -1)
		{
			perror("dup2");
			childs_exit(shell, i, fd, 1);
		}
		close(fd[0]);
		close(fd[1]);
	}
}

int pipe_creator(t_shell *shell, int i, int *fd, pid_t *pid)
{
	if (i < shell->cmd_count - 1)
	{
		if (pipe(fd) == -1)
		{
			perror("pipe");
			free(pid);
			return (0);
		}
	}
	return (1);
}
