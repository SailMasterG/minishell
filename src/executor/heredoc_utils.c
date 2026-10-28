/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chguerre <chguerre@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/25 19:57:47 by chguerre          #+#    #+#             */
/*   Updated: 2026/10/25 19:59:52 by chguerre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/include.h"

int	heredoc_event_hook(void)
{
	if (g_signal == SIGINT)
		rl_done = 1;
	return (0);
}

char	*heredoc_expand(char *value, t_shell *shell, bool is_quoted)
{
	char	*env;
	bool	dummy_is_var;
	int		i;

	i = -1;
	if (is_quoted)
		return (ft_strdup(value));
	env = ft_strdup("");
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
