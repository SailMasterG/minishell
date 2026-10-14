/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinheir <rpinheir@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/11 11:58:04 by rpinheir          #+#    #+#             */
/*   Updated: 2026/07/17 17:07:09 by pedro            ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*variable_expansion(char *name, t_shell *shell)
{
	char	**env;
	int		i;

	i = -1;
	env = shell->env;
	while (env[++i])
	{
		if (ft_strncmp(env[i], name, ft_strlen(name)) == 0)
		{
			if (env[i][ft_strlen(name)] == '=')
			{
				name = &env[i][ft_strlen(name) + 1];
				return (name);
			}
		}
	}
	return ("");
}

char	*value_expand(char *value, int *i, t_shell *shell)
{
	char	*name;
	char	*val;
	int		len;

	if (value[*i + 1] == '?')
		return (*i += 1, ft_itoa(shell->exit_status));
	if (value[*i + 1] == '\'' || value[*i + 1] == '"')
		(*i)++;
	len = 0;
	while (ft_isalnum(value[*i + 1 + len]) || value[*i + 1 + len] == '_')
		len++;
	if (len == 0)
		return (ft_strdup("$"));
	name = ft_substr(value, *i + 1, len);
	val = ft_strdup(variable_expansion(name, shell));
	free(name);
	*i += len;
	return (val);
}

char	*join_expand(char *env, char *value, bool is_dq, bool *is_var)
{
	char	*res;

	*is_var = true;
	if (!is_dq)
		mark_range(value);
	res = ft_strjoin(env, value);
	free(env);
	free(value);
	return (res);
}

char	*token_expand(char *value, t_shell *shell, bool	*is_var)
{
	char	*env;
	bool	is_dq;
	bool	is_sq;
	int		i;

	env = ft_strdup("");
	is_sq = false;
	is_dq = false;
	i = -1;
	while (value[++i])
	{
		if (value[i] == '\'' && !is_dq)
			is_sq = !is_sq;
		else if (value[i] == '"' && !is_sq)
			is_dq = !is_dq;
		else if (value[i] == '$' && !is_sq)
			env = join_expand(env, value_expand(value, &i, shell),
					is_dq, is_var);
		else
			env = ft_strjoin_char(env, value[i]);
	}
	return (env);
}

bool	expansion(t_token *head, t_shell *shell)
{
	t_token	*node;
	char	*value;

	if (!head)
		return (false);
	node = head;
	while (node)
	{
		if (node->type == TOKEN_REDIR_HEREDOC)
			node = node->next;
		else if (node->type == TOKEN_WORD)
		{
			node->is_var = false;
			value = token_expand(node->value, shell, &node->is_var);
			free(node->value);
			node->value = value;
		}
		node = node->next;
	}
	return (true);
}
