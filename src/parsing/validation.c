/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinheir <rpinheir@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 15:50:35 by rpinheir          #+#    #+#             */
/*   Updated: 2026/05/11 13:11:08 by rpinheir         ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

bool	redir_validation(t_token *token)
{
	if (token->type == TOKEN_REDIR_IN || token->type == TOKEN_REDIR_OUT
		|| token->type == TOKEN_REDIR_HEREDOC
		|| token->type == TOKEN_REDIR_APPEND)
	{
		if (!token->next || token->next->type != TOKEN_WORD)
		{
			ft_putstr_fd("minishell: syntax error near unexpected token ", 2);
			if ((token->next && token->next->value[0]))
			{
				ft_putstr_fd("`", 2);
				ft_putstr_fd(token->next->value, 2);
				ft_putendl_fd("'", 2);
			}
			else
				ft_putendl_fd("`newline'", 2);
			return (false);
		}
	}
	return (true);
}

/* IMPORTANT
 Bash behaviour: reads stdin to execute command after.No error message
 Minishell: Show a simple error message.
 Why? Because it is not  explictly asked for in subject, \e
 in case it is required:
 it needs to be done on execution side with exec_cmd + env;

*/
bool	pipe_validation(t_token *token)
{
	if (!token->next)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token ", 2);
		ft_putendl_fd("`newline'", 2);
		return (false);
	}
	if (token->next->type == TOKEN_PIPE)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token ", 2);
		ft_putstr_fd("`", 2);
		ft_putstr_fd(token->next->value, 2);
		ft_putendl_fd("'", 2);
		return (false);
	}
	return (true);
}

bool	validation(t_token *head)
{
	t_token	*node;

	if (!head)
		return (false);
	if (head->type == TOKEN_PIPE)
	{
		ft_putendl_fd("minishell: syntax error near unexpected token `|'", 2);
		return (false);
	}
	node = head;
	while (node)
	{
		if (!redir_validation(node))
			return (false);
		if (node->type == TOKEN_PIPE && !pipe_validation(node))
			return (false);
		node = node->next;
	}
	return (true);
}

// Check if exit is alone | maybe not needed
// if we make : cat Makefile | cat | exit \e
// it shouldnt work, no cat, no output BUT it should'nt exit the bash, it just
// stops/exits the command/pipe or maybe nothing as exit should be alone ?!
