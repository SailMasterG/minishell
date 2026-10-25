/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chguerre <chguerre@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/22 16:13:08 by rpinheir          #+#    #+#             */
/*   Updated: 2026/10/25 19:25:33 by chguerre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/include.h"

int	exec_loop(t_shell *shell, int *fd, t_cmd *current)
{
	int	i;

	i = 0;
	while (i < shell->cmd_count)
	{
		if (!pipe_creator(shell, i, fd, shell->pids))
			return (0);
		if (!fork_setup(shell, i, fd, current))
			return (0);
		if (current->next != NULL)
			current = current->next;
		if (shell->prevfd != -1)
			close(shell->prevfd);
		if (i < shell->cmd_count - 1)
		{
			close(fd[1]);
			shell->prevfd = fd[0];
		}
		i++;
	}
	return (1);
}

static int	malloc_pids(t_shell *shell)
{
	shell->pids = malloc(sizeof(pid_t) * shell->cmd_count);
	if (shell->pids == NULL)
	{
		perror("malloc");
		return (0);
	}
	return (1);
}

static int	run_heredoc(t_shell *shell )
{
	set_signal_mode(HEREDOC);
	if (exec_heredoc(shell, getpid()))
		return (1);
	free(shell->pids);
	shell->pids = NULL;
	shell->exit_status = 1;
	if (g_signal == SIGINT)
		shell->exit_status = 130;
	g_signal = 0;
	return (0);
}

int	executor(t_shell *shell)
{
	int			fd[2];
	t_cmd		*current;
	int			code;
	t_builtin	builtin;

	code = 0;
	resolve_all_paths(shell->cmds, shell->env);
	shell->cmd_count = count_cmd(shell->cmds);
	shell->prevfd = -1;
	current = shell->cmds;
	if (!malloc_pids(shell))
		return (1);
	if (!run_heredoc(shell))
		return (1);
	set_signal_mode(EXECUTION);
	builtin = get_builtin(current->cmd_args[0]);
	if (builtin != NULL && shell->cmd_count == 1)
	{
		code = run_builtin_parent(shell, builtin, shell->cmds);
		return (free(shell->pids), shell->exit_status = code, code);
	}
	if (!exec_loop(shell, fd, current))
		return (free(shell->pids), 1);
	code = wait_pid(shell->pids, shell->cmd_count);
	return (free(shell->pids), shell->exit_status = code, code);
}
