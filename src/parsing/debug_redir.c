/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinheir <rpinheir@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 14:10:49 by rpinheir          #+#    #+#             */
/*   Updated: 2026/04/22 14:29:00 by rpinheir         ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */
#include "../../include/minishell.h"

static char	*redir_name(t_redir_type type)
{
	if (type == REDIR_IN)
		return ("<");
	if (type == REDIR_OUT)
		return (">");
	if (type == REDIR_APPEND)
		return (">>");
	if (type == REDIR_HEREDOC)
		return ("<<");
	return ("?");
}

void	debug_redirs(t_cmd *cmd, int fd)
{
	t_redir	*redir;

	ft_putstr_fd("\n  redirs:", fd);
	redir = cmd->redirections;
	while (redir)
	{
		ft_putstr_fd(" ", fd);
		ft_putstr_fd(redir_name(redir->type), fd);
		ft_putstr_fd(" ", fd);
		ft_putstr_fd("[", fd);
		if (redir->file)
			ft_putstr_fd(redir->file, fd);
		else
			ft_putstr_fd("null", fd);
		ft_putendl_fd("]", fd);
		redir = redir->next;
	}
	if (!cmd->redirections)
		ft_putstr_fd(" none", fd);
	ft_putstr_fd("\n  next: ", fd);
	if (cmd->next)
		ft_putstr_fd("YES\n", fd);
	else
		ft_putstr_fd("NULL\n", fd);
}
