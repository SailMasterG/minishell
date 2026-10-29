/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chguerre <chguerre@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/19 20:36:59 by chguerre          #+#    #+#             */
/*   Updated: 2026/10/29 15:28:51 by rpinheir         ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/include.h"

void	childs_exit(t_shell *shell, int i, int *fd, int code)
{
	if (shell->prevfd != -1)
		close(shell->prevfd);
	if (i < shell->cmd_count - 1)
		(void)fd;
	if (shell->pids != NULL)
		free(shell->pids);
	ft_strfree(shell->env);
	free_cmds(shell->cmds);
	exit(code);
}

void	wait_pid(t_shell *shell, pid_t *pid, int nb_cmd)
{
	int		status;
	int		i;
	pid_t	caugth_pid;
	pid_t	last_pid;

	last_pid = pid[nb_cmd - 1];
	i = -1;
	while (++i < nb_cmd)
	{
		caugth_pid = waitpid(pid[i], &status, 0);
		if (caugth_pid == last_pid)
		{
			if (WIFSIGNALED(status) && WTERMSIG(status) == SIGQUIT)
				write(2, "Quit (core dumped)\n", 19);
			if (WIFSIGNALED(status))
				shell->exit_status = EXIT_SIGNAL_BASE + WTERMSIG(status);
			else
				shell->exit_status = WEXITSTATUS(status);
		}
	}
}

static void	run_child(t_shell *shell, int i, int *fd, t_cmd *current)
{
	t_builtin	builtin;
	int			code;

	set_signal_mode(FORKED);
	setup_child_pipes(shell, i, fd);
	if (redirs_cmd(current->redirections) != 0)
		childs_exit(shell, i, fd, 1);
	builtin = get_builtin(current->cmd_args[0]);
	if (builtin != NULL)
	{
		code = builtin(shell, current->cmd_args);
		childs_exit(shell, i, fd, code);
	}
	if (current->cmd_args[0] == NULL)
		childs_exit(shell, i, fd, 0);
	if (current->path == NULL)
	{
		write(2, current->cmd_args[0], ft_strlen(current->cmd_args[0]));
		ft_putendl_fd(": command not found", 2);
		childs_exit(shell, i, fd, 127);
	}
	execve(current->path, current->cmd_args, shell->env);
	code = errno;
	perror(current->cmd_args[0]);
	childs_exit(shell, i, fd, 126 + (code == ENOENT));
}

int	fork_setup(t_shell *shell, int i, int *fd, t_cmd *current)
{
	shell->pids[i] = fork();
	if (shell->pids[i] == -1)
	{
		perror("fork");
		return (0);
	}
	if (shell->pids[i] == 0)
		run_child(shell, i, fd, current);
	return (1);
}
