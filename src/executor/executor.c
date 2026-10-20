/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chguerre <chr@student.lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/16 22:35:03 by chguerre          #+#    #+#             */
/*   Updated: 2026/10/16 22:37:15 by chguerre         ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/include.h"

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

static void setup_child_pipes(t_shell *shell, int i, int *fd)
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

int exec_loop(t_shell *shell, int *fd, t_cmd *current)
{
	int i;

	i = 0;
	while (i < shell->cmd_count)
	{
		if (!pipe_creator(shell, i, fd, shell->pids))
			return (0);
		if(!fork_setup(shell, i, fd, current))
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
	set_signal_mode(EXECUTION);
	return (1);
}

static int malloc_pids(t_shell *shell)
{
	shell->pids = malloc(sizeof(pid_t) * shell->cmd_count);
	if (shell->pids == NULL)
	{
		perror("malloc");
		return (0);
	}
	return (1);
}

int	executor(t_shell *shell)
{
	int		fd[2];
	t_cmd	*current;
	int		code;

	code = 0;
	resolve_all_paths(shell->cmds, shell->env);
	shell->cmd_count = count_cmd(shell->cmds);
	shell->prevfd = -1;
	current = shell->cmds;
	set_signal_mode(EXECUTION);
	if(!malloc_pids(shell))
		return(1);
	if (!exec_heredoc(shell->cmds, shell->cmd_count, getpid()))
	{
		free(shell->pids);
		return (1);
	}
	if (!exec_loop(shell, fd, current))
	{
		free(shell->pids);
		return (1);
	}
	code = wait_pid(shell->pids, shell->cmd_count);
	free(shell->pids);
	return (code);
}
