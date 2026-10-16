/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chguerre <chr@student.lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/16 19:52:30 by chguerre          #+#    #+#             */
/*   Updated: 2026/10/16 19:52:55 by chguerre         ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/include.h"

void redir_in(t_redir *node, int fd_redir)
{
	fd_redir = open(node->file, O_RDONLY);
	if (fd_redir < 0)
	{
		perror("Error de lectura de archivo");
		exit(126);
	}
	dup2(fd_redir, STDIN_FILENO);
	close(fd_redir);
}