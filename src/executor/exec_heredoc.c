/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chguerre <chguerre@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/22 16:06:43 by rpinheir          #+#    #+#             */
/*   Updated: 2026/10/25 20:05:32 by chguerre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/include.h"

static int	hdoc_pro_line(int fd, char *line, t_redir *node, t_shell *shell)
{
	char	*expanded_line;

	if (g_signal == SIGINT)
	{
		free(line);
		return (0);
	}
	if (ft_strncmp(line, node->file, ft_strlen(node->file) + 1) == 0)
	{
		free(line);
		return (0);
	}
	if (fd != -1)
	{
		expanded_line = heredoc_expand(line, shell, node->is_quoted);
		if (expanded_line)
		{
			ft_putendl_fd(expanded_line, fd);
			free(expanded_line);
		}
	}
	free(line);
	return (1);
}

static int	heredoc_readline(int fd, char *line, t_redir *node, t_shell *shell)
{
	while (1)
	{
		rl_event_hook = heredoc_event_hook;
		line = readline("heredoc>");
		if (line == NULL || g_signal == SIGINT)
		{
			free(line);
			break ;
		}
		if (!hdoc_pro_line(fd, line, node, shell))
			break ;
	}
	rl_event_hook = NULL;
	rl_done = 0;
	if (g_signal == SIGINT || fd == -1)
		return (0);
	return (1);
}

static char	*heredoc_path_temp(int i, int pid)
{
	char	*route_path;
	char	*path_temp;
	char	*prefix;
	char	*pid_txt;
	char	*id;

	pid_txt = ft_itoa(pid);
	id = ft_itoa(i);
	prefix = ft_strjoin(".sailmaster_", pid_txt);
	path_temp = ft_strjoin(prefix, "_");
	route_path = ft_strjoin(path_temp, id);
	free(prefix);
	free(pid_txt);
	free(id);
	free(path_temp);
	return (route_path);
}

static int	is_heredoc(t_redir *node, int i, int pid, t_shell *shell)
{
	int		fd;
	char	*line;
	char	*route_path_tmp;

	if (node->type == REDIR_HEREDOC)
	{
		line = NULL;
		route_path_tmp = heredoc_path_temp(i, pid);
		fd = open(route_path_tmp, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (fd < 0)
		{
			perror("Error de Lectura de archivo 1");
		}
		if (!heredoc_readline(fd, line, node, shell))
		{
			close(fd);
			unlink(route_path_tmp);
			return (free(route_path_tmp), 0);
		}
		close(fd);
		free(node->file);
		node->file = route_path_tmp;
		return (1);
	}
	return (1);
}

int	exec_heredoc(t_shell *shell, int pid )
{
	t_cmd	*current;
	t_redir	*node;
	int		i;
	int		j;

	current = shell->cmds;
	i = 0;
	j = 0;
	while (i < shell->cmd_count)
	{
		node = current->redirections;
		while (node != NULL)
		{
			if (!is_heredoc(node, j, pid, shell))
			{
				erase_before_files(shell->cmds, node);
				return (0);
			}
			node = node->next;
			j++;
		}
		current = current->next;
		i++;
	}
	return (1);
}
