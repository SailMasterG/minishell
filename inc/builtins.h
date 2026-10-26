/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chguerre <chguerre@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/22 14:49:04 by chguerre          #+#    #+#             */
/*   Updated: 2026/10/26 19:43:49 by rpinheir         ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "struct.h"

typedef int	(*t_builtin)(t_shell *shell, char **cmd_args);

t_builtin	get_builtin(char *name);
int			builtin_echo(t_shell *shell, char **cmd_args);
int			builtin_cd(t_shell *shell, char **cmd_args);
int			builtin_pwd(t_shell *shell, char **cmd_args);
int			builtin_export(t_shell *shell, char **cmd_args);
int			builtin_unset(t_shell *shell, char **cmd_args);
int			builtin_env(t_shell *shell, char **cmd_args);
int			builtin_exit(t_shell *shell, char **cmd_args);
int			run_builtin_parent(t_shell *shell, t_builtin fn, t_cmd *cmd);
int			env_pos(char **envp, char *key);

bool		is_name_valid(char *arg);
void		add_to_env(t_shell *shell, char *name, char *value);
char		*get_value(char *arg);
char		*get_name(char *arg);
void		modify_env(t_shell *shell, int index, char *value);
void		display_export(char **env);
void		sort_env(char **env);
#endif // H_BUILTINS
