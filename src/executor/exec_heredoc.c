/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chguerre <chr@student.lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/16 20:33:16 by chguerre          #+#    #+#             */
/*   Updated: 2026/10/16 20:33:16 by chguerre         ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/include.h"

static void	heredoc_readline(int fd, char *line, t_redir *node)
{
	while (1)
	{
		line = readline("heredoc>");
		if (line == NULL)
			break ;
		if (ft_strncmp(line, node->file, ft_strlen(node->file) + 1) == 0)
			break ;
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	free(line);
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

static int	is_heredoc(t_redir *node, int i, int pid)
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
			free(route_path_tmp);
			return (0);
		}
		heredoc_readline(fd, line, node);
		close(fd);
		free(node->file);
		node->file = route_path_tmp;
		return (1);
	}
	return (0);
}

int	exec_heredoc(t_cmd *cmd, int nb_cmd, int pid)
{
	t_cmd	*current;
	t_redir	*node;
	int		i;

	current = cmd;
	i = 0;
	while (i < nb_cmd)
	{
		node = current->redirections;
		while (node != NULL)
		{
			if (!is_heredoc(node, i, pid))
				return (0);
			node = node->next;
		}
		current = current->next;
		i++;
	}
	return (1);
}
