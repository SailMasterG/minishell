/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chguerre <chr@student.lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/16 22:01:37 by chguerre          #+#    #+#             */
/*   Updated: 2026/10/16 22:01:37 by chguerre         ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/include.h"

int	count_cmd(t_cmd *cmd)
{
	t_cmd	*current;
	int		count;

	count = 0;
	current = cmd;
	while (current != NULL)
	{
		current = current->next;
		count++;
	}
	return (count);
}

void erase_before_files(t_cmd *cmd, t_redir *limit)
{
	t_redir *node;
	t_cmd *current;

	current = cmd;
	if	(!current)
		return;
	while(current != NULL)
	{
		node = current->redirections;
		while(node != NULL)
		{
			if (limit == node)
				return;			
			if (node->type == REDIR_HEREDOC)
			{
				unlink(node->file);
				free(node->file);
				node->file = NULL;
				continue;
			}
			node = node->next;
		}
		current = current->next;
	}
	return;
}