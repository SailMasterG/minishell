/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chguerre <chguerre@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/19 20:36:59 by chguerre          #+#    #+#             */
/*   Updated: 2026/10/19 20:39:00 by chguerre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/include.h"


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

int	wait_pid(pid_t *pid, int nb_cmd)
{
	int		status;
	int		i;
	int		code;
	pid_t	caugth_pid;
	pid_t	last_pid;

	last_pid = pid[nb_cmd - 1];
	i = 0;
	code = 0;
	while (i < nb_cmd)
	{
		caugth_pid = waitpid(pid[i], &status, 0);
		if (caugth_pid == last_pid)
		{
			if (WIFSIGNALED(status))
				code = WTERMSIG(status) + 128;
			else if (WIFEXITED(status))
				code = WEXITSTATUS(status);
		}
		i++;
	}
	return (code);
}

int fork_setup(t_shell *shell, int i, int *fd, t_cmd *current)
{
	t_redir	*node;

	node = current->redirections;
	shell->pids[i] = fork();
	if (shell->pids[i] == -1)
	{
		perror("fork");
		free(shell->pids);
		return (0);
	}
	if (shell->pids[i] == 0)
	{
		set_signal_mode(FORKED);
		setup_child_pipes(shell, i, fd);
		redirs_cmd(node);
		if (current->path == NULL)
		{
			ft_printf("Error: command not found: %s\n", current->cmd_args[0]);
			childs_exit(shell, i, fd, 127);
		}
		if ((execve(current->path, current->cmd_args, shell->env)) == -1)
		{
			perror("Error: ");
			childs_exit(shell, i, fd, 127);
		}
	}
	return (1);
}
