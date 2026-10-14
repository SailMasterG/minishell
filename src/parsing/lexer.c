/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinheir <rpinheir@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 12:29:13 by rpinheir          #+#    #+#             */
/*   Updated: 2026/05/11 13:10:05 by rpinheir         ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	handle_word(char *line, int *i, t_token **head, t_token **last)
{
	int		start;
	char	*value;
	char	quote_char;
	bool	quoted;

	start = *i;
	quote_char = 0;
	quoted = false;
	while (line[*i] && (quote_char || (line[*i] != ' ' && line[*i] != '\t'
				&& line[*i] != '|' && line[*i] != '<' && line[*i] != '>')))
	{
		if (quote_char == 0 && (line[*i] == '\'' || line[*i] == '"'))
		{
			quote_char = line[*i];
			quoted = true;
		}
		else if (quote_char != 0 && line[*i] == quote_char)
			quote_char = 0;
		(*i)++;
	}
	value = ft_substr(line, start, *i - start);
	add_token(head, last, new_token(TOKEN_WORD, value));
	if (*last)
		(*last)->is_quoted = quoted;
	free(value);
}

bool	handle_quote(char *line)
{
	char	quote;
	int		i;

	quote = '\0';
	i = 0;
	while (line[i])
	{
		if ((line[i] == '\'' || line[i] == '\"' ) && quote == '\0')
			quote = line[i];
		else if (line[i] && line[i] == quote)
			quote = '\0';
		i++;
	}
	if (quote == '\0')
		return (true);
	return (false);
}

t_token	*lexer(char *line)
{
	int		i;
	t_token	*head;
	t_token	*last;

	head = NULL;
	last = NULL;
	i = 0;
	if (!handle_quote(line))
	{
		ft_putstr_fd("minishell: syntax error", 2);
		ft_putendl_fd(" unclosed quotes are not permitted", 2);
		return (NULL);
	}
	while (line[i])
	{
		while (line[i] == ' ' || line[i] == '\t')
			i++;
		if (!line[i])
			break ;
		if (line[i] == '|' || line[i] == '<' || line[i] == '>')
			handle_operator(line, &i, &head, &last);
		else
			handle_word(line, &i, &head, &last);
	}
	return (head);
}
