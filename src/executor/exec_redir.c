/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chguerre <chr@student.lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/16 20:43:24 by chguerre          #+#    #+#             */
/*   Updated: 2026/10/16 20:48:07 by chguerre         ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/include.h"

static void redir_in(t_redir *node)
{
	int fd_redir;
	
	fd_redir = open(node->file, O_RDONLY);
	if (fd_redir < 0)
	{
		perror("Error de lectura de archivo");
		exit(126);
	}
	dup2(fd_redir, STDIN_FILENO);
	close(fd_redir);
}

static void redir_out(t_redir *node )
{
    int	fd_redir;

    fd_redir = open(node->file,
	O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd_redir < 0)
	{
	    perror("Error de escritura de archivo");
		exit(126);
	}
	dup2(fd_redir, STDOUT_FILENO);
	close(fd_redir);
}

static void redir_append(t_redir *node)
{
	int fd_redir;
    fd_redir = open(node->file,
				O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd_redir < 0)
	{
		perror("Error de escritura de archivo");
		exit(126);
	}
	dup2(fd_redir, STDOUT_FILENO);
	close(fd_redir);
}

static void redir_heredoc(t_redir *node)
{
	int fd_redir;
	fd_redir = open(node->file, O_RDONLY);
	if (fd_redir < 0)
	{
		perror("Error de lectura de archivo 2");
		exit(126);
	}
	unlink(node->file);
	free(node->file);
	dup2(fd_redir, STDIN_FILENO);
	close(fd_redir);
}

void redirs_cmd(t_redir *node)
{
	while (node != NULL)
	{
		if (node->type == REDIR_IN)
        {
            redir_in(node);
        }
        else if (node->type == REDIR_OUT)
        {
            redir_out(node);
        }
        else if (node->type == REDIR_APPEND)
        {
            redir_append(node);
        }
        else if (node->type == REDIR_HEREDOC)
        {
            redir_heredoc(node);
        }
		node = node->next;
	}	
}
