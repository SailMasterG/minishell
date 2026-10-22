/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chguerre <chguerre@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/22 14:49:04 by chguerre          #+#    #+#             */
/*   Updated: 2026/10/22 15:12:56 by chguerre         ###   ########.fr       */
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

#endif // H_BUILTINS
