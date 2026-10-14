/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_cmds.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saouissi <saouissi@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/17 12:34:47 by pedro             #+#    #+#             */
/*   Updated: 2026/07/03 17:47:22 by saouissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	free_cmds(t_cmd *cmds)
{
	t_cmd	*next_cmd;
	t_redir	*redir;
	t_redir	*next_redir;
	int		i;

	while (cmds)
	{
		next_cmd = cmds->next;
		i = 0;
		while (cmds->cmd_args[i])
			free(cmds->cmd_args[i++]);
		free(cmds->cmd_args);
		redir = cmds->redirections;
		while (redir)
		{
			next_redir = redir->next;
			free(redir->file);
			free(redir);
			redir = next_redir;
		}
		free(cmds);
		cmds = next_cmd;
	}
}

int	count_args(t_token *tokens)
{
	int		n_args;

	n_args = 0;
	while (tokens && tokens->type != TOKEN_PIPE)
	{
		if (tokens->is_var && tokens->value[0] == '\0' && !tokens->is_quoted)
		{
			tokens = tokens->next;
			continue ;
		}
		if (is_redir(tokens))
		{
			tokens = tokens->next;
			if (tokens)
				tokens = tokens->next;
		}
		else if (tokens->type == TOKEN_WORD)
		{
			n_args += count_fields(tokens->value);
			tokens = tokens->next;
		}
	}
	return (n_args);
}

bool	builder_helper(t_token **tokens, t_cmd *cmd, int *i)
{
	if ((*tokens)->is_var && (*tokens)->value[0] == '\0'
		&& !(*tokens)->is_quoted)
	{
		(*tokens) = (*tokens)->next;
		return (false);
	}
	if ((*tokens)->type == TOKEN_WORD)
		fill_fields((*tokens)->value, cmd->cmd_args, i);
	else if (is_redir(*tokens) && (*tokens)->next)
	{
		append_redir(&cmd->redirections,
			token_to_redir_type((*tokens)->type), (*tokens)->next->value);
		*tokens = (*tokens)->next;
	}
	*tokens = (*tokens)->next;
	return (true);
}

t_cmd	*build_one_cmd(t_token **tokens)
{
	t_cmd	*cmds;
	int		i;

	i = 0;
	cmds = malloc(sizeof(t_cmd));
	if (!cmds)
		return (NULL);
	cmds->next = NULL;
	cmds->redirections = NULL;
	cmds->cmd_args = malloc(sizeof(char *) * (count_args(*tokens) + 1));
	if (!cmds->cmd_args)
		return (free(cmds), NULL);
	while (*tokens && (*tokens)->type != TOKEN_PIPE)
	{
		if (!builder_helper(tokens, cmds, &i))
			continue ;
	}
	return (cmds->cmd_args[i] = NULL, cmds);
}

t_cmd	*build_cmds(t_token *tokens)
{
	t_cmd	*head;
	t_cmd	*tail;
	t_cmd	*new_cmd;

	head = NULL;
	tail = NULL;
	while (tokens)
	{
		new_cmd = build_one_cmd(&tokens);
		if (!new_cmd)
			return (head);
		if (!head)
		{
			head = new_cmd;
			tail = new_cmd;
		}
		else
		{
			tail->next = new_cmd;
			tail = new_cmd;
		}
		if (tokens && tokens->type == TOKEN_PIPE)
			tokens = tokens->next;
	}
	return (head);
}
