/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinheir <rpinheir@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/16 14:09:15 by rpinheir          #+#    #+#             */
/*   Updated: 2026/10/16 14:42:36 by rpinheir         ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H
# define EXIT_SIGNAL_BASE 128
# define WS_SEP '\001'

# include "libft/libft.h"
# include "enum.h"

typedef struct s_token
{
	t_token_type	type;
	bool			is_var;
	bool			is_quoted;
	char			*value;
	struct s_token	*next;
}				t_token;

typedef struct s_redir
{
	t_redir_type	type;
	char			*file;
	struct s_redir	*next;
	bool			is_quoted;
}				t_redir;

typedef struct s_cmd
{
	char			**cmd_args;
	char			*path;
	t_redir			*redirections;
	struct s_cmd	*next;
}				t_cmd;

typedef struct s_shell
{
	pid_t			hereid;
	int				prevfd;
	int				wread[2];
	int				cmd_count;
	pid_t			*pids;
	t_cmd			*cmds;
	bool			print_newline;
	char			**env;
	long long		exit_status;
}			t_shell;

#endif
