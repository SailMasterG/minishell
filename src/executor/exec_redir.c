/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chguerre <chguerre@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/22 16:10:42 by rpinheir          #+#    #+#             */
/*   Updated: 2026/10/22 21:18:41 by chguerre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/include.h"

static int	redir_in(t_redir *node)
{
	int	fd_redir;

	fd_redir = open(node->file, O_RDONLY);
	if (fd_redir < 0)
	{
		perror(node->file);
		return (-1);
	}
	if (dup2(fd_redir, STDIN_FILENO) == -1)
	{
		close(fd_redir);
		return (-1);
	}
	close(fd_redir);
	return (0);
}

static int	redir_out(t_redir *node )
{
	int	fd_redir;

	fd_redir = open(node->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd_redir < 0)
	{
		perror(node->file);
		return (-1);
	}
	if (dup2(fd_redir, STDOUT_FILENO) == -1)
	{
		close(fd_redir);
		return (-1);
	}
	close(fd_redir);
	return (0);
}

static int	redir_append(t_redir *node)
{
	int	fd_redir;

	fd_redir = open(node->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd_redir < 0)
	{
		perror(node->file);
		return (-1);
	}
	if (dup2(fd_redir, STDOUT_FILENO) == -1)
	{
		close(fd_redir);
		return (-1);
	}
	close(fd_redir);
	return (0);
}

static int	redir_heredoc(t_redir *node)
{
	int	fd_redir;

	fd_redir = open(node->file, O_RDONLY);
	if (fd_redir < 0)
	{
		perror("Error de lectura de archivo 2");
		return (-1);
	}
	unlink(node->file);
	free(node->file);
	if (dup2(fd_redir, STDIN_FILENO) == -1)
	{
		close(fd_redir);
		return (-1);
	}
	close(fd_redir);
	return (0);
}

int	redirs_cmd(t_redir *node)
{
	while (node != NULL)
	{
		if (node->type == REDIR_IN && redir_in(node) == -1)
			return (1);
		else if (node->type == REDIR_OUT && redir_out(node) == -1)
			return (1);
		else if (node->type == REDIR_APPEND && redir_append(node) == -1)
			return (1);
		else if (node->type == REDIR_HEREDOC && redir_heredoc(node) == -1)
			return (1);
		node = node->next;
	}
	return (0);
}
