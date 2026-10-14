/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_split.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saouissi <saouissi@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 12:00:00 by rpinheir          #+#    #+#             */
/*   Updated: 2026/07/17 17:17:58 by pedro            ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*resolve_redir_file(t_redir_type type, char *file, bool *is_quoted)
{
	if (type == REDIR_HEREDOC)
	{
		*is_quoted = (ft_strchr(file, '"') || ft_strchr(file, '\''));
		return (strip_quotes(file));
	}
	*is_quoted = false;
	return (ft_strdup(file));
}

char	*strip_quotes(char *string)
{
	char	*res;
	bool	is_dq;
	bool	is_sq;
	int		i;

	res = ft_strdup("");
	is_sq = false;
	is_dq = false;
	i = -1;
	while (string[++i])
	{
		if (string[i] == '\'' && !is_dq)
			is_sq = !is_sq;
		else if (string[i] == '"' && !is_sq)
			is_dq = !is_dq;
		else
			res = ft_strjoin_char(res, string[i]);
	}
	return (res);
}

void	mark_range(char *s)
{
	int	i;

	i = -1;
	while (s[++i])
		if (s[i] == ' ' || s[i] == '\t')
			s[i] = WS_SEP;
}

int	count_fields(char *value)
{
	char	**fields;
	int		k;

	if (value[0] == '\0')
		return (1);
	fields = ft_split(value, WS_SEP);
	if (!fields)
		return (0);
	k = 0;
	while (fields[k])
		free(fields[k++]);
	return (free(fields), k);
}

void	fill_fields(char *value, char **cmd_args, int *i)
{
	char	**fields;
	int		k;

	k = -1;
	if (value[0] == '\0')
	{
		cmd_args[(*i)] = ft_strdup("");
		(*i)++;
		return ;
	}
	fields = ft_split(value, WS_SEP);
	if (!fields)
		return ;
	while (fields[++k])
		cmd_args[(*i)++] = fields[k];
	free(fields);
}
