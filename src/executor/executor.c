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
void	clean_files_heredoc(t_cmd *cmd, int nb_cmd)
{
	t_redir *node;
	t_cmd *current;
	int i; 

	current = cmd;
	if	(!current)
		return;
	i = 0;
	while(i < nb_cmd)
	{
		node = current->redirections;
		while(node != NULL)
		{
			if (node->file != NULL)
			{
				unlink(node->file);
				free(node->file);
				node->file = NULL;
				node = node->next;
			}
			current = current->next;
	 	}
	i++;
	}
	free(current);
	return;
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
	if(!malloc_pids(shell))
		return(1);
	set_signal_mode(HEREDOC);
	if (!exec_heredoc(shell->cmds, shell->cmd_count, getpid()))
	{
		free(shell->pids);
		shell->pids = NULL;
		shell->exit_status = 1;
		if (g_signal == SIGINT)
		{
			shell->exit_status = 130;
			write(1,"S\n",2);
			clean_files_heredoc(shell->cmds, shell->cmd_count);
		}
		g_signal = 0;
		return (1);
	}
	set_signal_mode(EXECUTION);
	if (!exec_loop(shell, fd, current))
	{
		free(shell->pids);
		return (1);
	}
	code = wait_pid(shell->pids, shell->cmd_count);
	free(shell->pids);
	shell->exit_status = code;
	return (code);
}
