/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinheir <rpinheir@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 15:25:56 by rpinheir          #+#    #+#             */
/*   Updated: 2026/07/17 17:06:50 by pedro            ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */
#include "../../include/minishell.h"

void	append_redir(t_redir **head, t_redir_type type, char *file)
{
	t_redir	*node;
	t_redir	*tail;

	node = malloc(sizeof(t_redir));
	if (!node)
		return ;
	node->type = type;
	node->file = resolve_redir_file(type, file, &node->is_quoted);
	node->next = NULL;
	if (!*head)
	{
		*head = node;
		return ;
	}
	tail = *head;
	while (tail->next)
		tail = tail->next;
	tail->next = node;
}

t_redir_type	token_to_redir_type(t_token_type token_type)
{
	if (token_type == TOKEN_REDIR_APPEND)
		return (REDIR_APPEND);
	else if (token_type == TOKEN_REDIR_HEREDOC)
		return (REDIR_HEREDOC);
	else if (token_type == TOKEN_REDIR_IN)
		return (REDIR_IN);
	else if (token_type == TOKEN_REDIR_OUT)
		return (REDIR_OUT);
	return ((t_redir_type)0);
}

void	input_redirs(char *line, int *i, t_token **head, t_token **last)
{
	if (line[*i + 1] == '<')
	{
		add_token(head, last, new_token(TOKEN_REDIR_HEREDOC, "<<"));
		*i += 2;
	}
	else
	{
		add_token(head, last, new_token(TOKEN_REDIR_IN, "<"));
		(*i)++;
	}
}

void	output_redirs(char *line, int *i, t_token **head, t_token **last)
{
	if (line[*i + 1] == '>')
	{
		add_token(head, last, new_token(TOKEN_REDIR_APPEND, ">>"));
		*i += 2;
	}
	else
	{
		add_token(head, last, new_token(TOKEN_REDIR_OUT, ">"));
		(*i)++;
	}
}

void	handle_operator(char *line, int *i, t_token **head, t_token **last)
{
	if (line[*i] == '|')
	{
		add_token(head, last, new_token(TOKEN_PIPE, "|"));
		(*i)++;
	}
	else if (line[*i] == '<')
	{
		input_redirs(line, i, head, last);
	}
	else if (line[*i] == '>')
	{
		output_redirs(line, i, head, last);
	}
}
