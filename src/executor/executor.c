/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chguerre <chr@student.lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/16 20:01:34 by chguerre          #+#    #+#             */
/*   Updated: 2026/10/16 20:01:34 by chguerre         ###   ########.ch       */
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
			return (1);
		}
	}
	return (0);
}


int	executor(t_shell *shell)
{
	int		fd[2];
	pid_t	*pid;
	int		prev_fd;
	int		i;
	t_cmd	*current;
	t_redir	*node;
	int		code;

	code = 0;
	i = 0;
	shell->cmd_count = count_cmd(shell->cmds);
	prev_fd = -1;
	current = shell->cmds;
	pid = malloc(sizeof(pid_t) * shell->cmd_count);
	if (pid == NULL)
	{
		perror("malloc");
		return (1);
	}
	if (!heredoc_resolve(shell->cmds, shell->cmd_count, getpid()))
	{
		free(pid);
		return (1);
	}
	while (i < shell->cmd_count)
	{
		if (pipe_creator(shell, i, fd, pid))
			return (1);

		node = current->redirections;
		pid[i] = fork();
		if (pid[i] == -1)
		{
			perror("fork");
			free(pid);
			return (1);
		}
		if (pid[i] == 0)
		{
			if (prev_fd != -1)
			{
				dup2(prev_fd, STDIN_FILENO);
				close(prev_fd);
			}
			if (i < shell->cmd_count - 1)
			{
				dup2(fd[1], STDOUT_FILENO);
				close(fd[0]);
				close(fd[1]);
			}
			redirs_cmd(node, shell);
			if ((execve(current->path, current->cmd_args, shell->env)) == -1)
			{
				perror("Error: ");
				exit(127);
			}
		}
		while (node != NULL)
		{
			if (node->type == REDIR_HEREDOC)
				free(node->file);
			node = node->next;
		}
		if (current->next != NULL)
			current = current->next;
		if (prev_fd != -1)
			close(prev_fd);
		if (i < shell->cmd_count - 1)
		{
			close(fd[1]);
			prev_fd = fd[0];
		}
		i++;
	}
	code = wait_pid(pid, shell->cmd_count);
	free(pid);
	return (code);
}
