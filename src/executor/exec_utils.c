/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chguerre <chguerre@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/16 22:01:37 by chguerre          #+#    #+#             */
/*   Updated: 2026/10/25 19:35:47 by chguerre         ###   ########.fr       */
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

void	erase_before_files(t_cmd *cmd, t_redir *limit)
{
	t_redir	*node;
	t_cmd	*current;

	current = cmd;
	if (!current)
		return ;
	while (current != NULL)
	{
		node = current->redirections;
		while (node != NULL)
		{
			if (limit == node)
				return ;
			if (node->type == REDIR_HEREDOC)
			{
				unlink(node->file);
				free(node->file);
				node->file = NULL;
			}
			node = node->next;
		}
		current = current->next;
	}
	return ;
}

char	*heredoc_expand(char *value, t_shell *shell)
{
	char	*env;
	bool	dummy_is_var;
	int		i;

	env = ft_strdup("");
	i = -1;
	while (value[++i])
	{
		if (value[i] == '$')
			env = join_expand(env, value_expand(value, &i, shell),
					true, &dummy_is_var);
		else
			env = ft_strjoin_char(env, value[i]);
	}
	return (env);
}
