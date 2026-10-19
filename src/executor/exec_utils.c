/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chguerre <chr@student.lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/16 22:01:37 by chguerre          #+#    #+#             */
/*   Updated: 2026/10/16 22:01:37 by chguerre         ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/include.h"

int	count_cmd(t_cmd *cmd)
{
	t_cmd	*current;
	int		count;

	count = 0;
	current = cmd;
	while (current != NULL)
	{
		current = current->next;
		count++;
	}
	return (count);
}

void childs_exit(t_shell *shell, int i, int *fd, int code)
{
	if (shell->prevfd != -1)
		close(shell->prevfd);
	if (i < shell->cmd_count - 1)
	{
		close(fd[0]);
		close(fd[1]);
	}
	if (shell->pids != NULL)
		free(shell->pids);
	free (shell->env);
	free_cmds(shell->cmds);
	exit(code);
}