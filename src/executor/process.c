/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chguerre <chguerre@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/19 20:36:59 by chguerre          #+#    #+#             */
/*   Updated: 2026/10/22 21:08:47 by chguerre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/include.h"

void	childs_exit(t_shell *shell, int i, int *fd, int code)
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
	ft_strfree(shell->env);
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
	i = -1;
	code = 0;
	while (++i < nb_cmd)
	{
		caugth_pid = waitpid(pid[i], &status, 0);
		if (caugth_pid == last_pid)
		{
			if (WIFSIGNALED(status))
			{
				if (WTERMSIG(status) == SIGINT)
					write(1, "\n", 1);
				code = WTERMSIG(status) + 128;
			}
			else if (WIFEXITED(status))
				code = WEXITSTATUS(status);
		}
	}
	return (code);
}

static void	run_child(t_shell *shell, int i, int *fd, t_cmd *current)
{
	set_signal_mode(FORKED);
	setup_child_pipes(shell, i, fd);
	if (redirs_cmd(current->redirections) != 0)
		childs_exit(shell, i, fd, 1);
	if (current->cmd_args[0] == NULL)
		childs_exit(shell, i, fd, 0);
	if (current->path == NULL)
	{
		write(2, current->cmd_args[0], ft_strlen(current->cmd_args[0]));
		ft_putendl_fd(": command not found", 2);
		childs_exit(shell, i, fd, 127);
	}
	if ((execve(current->path, current->cmd_args, shell->env)) == -1)
	{
		perror(current->cmd_args[0]);
		childs_exit(shell, i, fd, 127);
	}
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
