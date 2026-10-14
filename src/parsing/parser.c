/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinheir <rpinheir@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 11:15:45 by rpinheir          #+#    #+#             */
/*   Updated: 2026/05/17 13:45:00 by pedro            ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/include.h"

t_cmd	*filter_null_cmds(t_cmd *cmds)
{
	t_cmd	*tmp;
	t_cmd	*prev;

	while (cmds && cmds->cmd_args[0] == NULL && !cmds->redirections)
	{
		tmp = cmds->next;
		cmds->next = NULL;
		free_cmds(cmds);
		cmds = tmp;
	}
	prev = cmds;
	while (prev && prev->next)
	{
		if (prev->next->cmd_args[0] == NULL && !prev->next->redirections)
		{
			tmp = prev->next;
			prev->next = tmp->next;
			tmp->next = NULL;
			free_cmds(tmp);
		}
		else
			prev = prev->next;
	}
	return (cmds);
}

t_cmd	*parse(char *line, t_shell *shell)
{
	t_token	*tokens;
	t_cmd	*cmds;

	tokens = lexer(line);
	if (!tokens)
		return (NULL);
	if (!validation(tokens))
		return (shell->exit_status = 2, free_tokens(tokens), NULL);
	if (!expansion(tokens, shell))
		return (free_tokens(tokens), NULL);
	cmds = build_cmds(tokens);
	debug_tokens(tokens, line);
	free_tokens(tokens);
	cmds = filter_null_cmds(cmds);
	debug_cmds(cmds);
	if (!cmds)
		shell->exit_status = 0;
	return (cmds);
}
