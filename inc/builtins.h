/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chguerre <chguerre@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/22 14:49:04 by chguerre          #+#    #+#             */
/*   Updated: 2026/10/22 20:31:33 by chguerre         ###   ########.fr       */
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
int			is_parent_builtin(char *cmd);
int			run_builtin_parent(t_shell *shell, t_builtin fn, t_cmd *cmd);

#endif // H_BUILTINS
