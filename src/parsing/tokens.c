/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saouissi <saouissi@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 17:38:48 by rpinheir          #+#    #+#             */
/*   Updated: 2026/07/03 17:48:41 by saouissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	free_tokens(t_token *tokens)
{
	t_token	*tmp;

	while (tokens)
	{
		tmp = tokens->next;
		free(tokens->value);
		free(tokens);
		tokens = tmp;
	}
}

t_token	*new_token(t_token_type token_type, char *value)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = token_type;
	token->value = ft_strdup(value);
	token->is_var = false;
	token->is_quoted = false;
	token->next = NULL;
	return (token);
}

void	add_token(t_token **head, t_token **last, t_token *token)
{
	if (!*head)
	{
		*head = token;
		*last = token;
	}
	else
	{
		(*last)->next = token;
		*last = token;
	}
}

bool	is_redir(t_token *tokens)
{
	if (tokens->type == TOKEN_REDIR_APPEND
		|| tokens->type == TOKEN_REDIR_HEREDOC
		|| tokens->type == TOKEN_REDIR_IN
		|| tokens->type == TOKEN_REDIR_OUT)
		return (true);
	return (false);
}
