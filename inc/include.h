/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   include.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinheir <your_login@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/13 16:39:58 by rpinheir          #+#    #+#             */
/*   Updated: 2026/10/13 16:40:56 by rpinheir         ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */
#ifndef INCLUDE_H
# define INCLUDE_H
# define EXIT_SIGNAL_BASE 128
# define WS_SEP '\001'
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <limits.h>
# include <errno.h>
# include <fcntl.h>
# include <sys/types.h>
# include <unistd.h>
# include <stdbool.h>
# include <sys/wait.h>
# include <signal.h>
# include <sys/ioctl.h>
# include "libft/libft.h"

# define CLR_SCREEN "\033[1;1H\033[2J"
# define MAUVE "\001\033[38;2;203;166;247m\002"
# define PEACH "\001\033[38;2;250;179;135m\002"
# define GREY  "\001\033[38;2;166;173;200m\002"
# define SKY   "\001\033[38;2;180;195;254m\002"
# define RED   "\001\033[38;2;243;139;168m\002"
# define RESET "\001\033[0m\002"
# define HD_MARK "\033[38;2;108;112;134m· \033[0m"

typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_REDIR_APPEND,
	TOKEN_REDIR_HEREDOC
}				t_token_type;

typedef enum e_redir_type
{
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEND,
	REDIR_HEREDOC
}				t_redir_type;

typedef enum e_signal_modes
{
	INTERACTIVE,
	EXECUTION,
	FORKED,
}				t_signal_modes;

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
	int				heredoc_fd;
	bool			is_quoted;
}				t_redir;

typedef struct s_cmd
{
	char			**cmd_args;
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
	char			*historian;
}			t_shell;

/**			---     PARSING			---		*/
t_cmd			*parse(char *line, t_shell *shell);
t_cmd			*build_cmds(t_token *tokens);
t_token			*lexer(char *line);
t_token			*new_token(t_token_type token_type, char *value);
t_redir_type	token_to_redir_type(t_token_type token_type);
void			add_token(t_token **head, t_token **last, t_token *new_token);
void			free_tokens(t_token *tokens);
void			handle_operator(char *line, int *i, t_token **head,
					t_token **last);
void			append_redir(t_redir **head, t_redir_type type, char *file);
void			free_cmds(t_cmd *cmds);
void			fill_fields(char *value, char **cmd_args, int *i);
char			*strip_quotes(char *string);
char			*resolve_redir_file(t_redir_type type,
					char *file, bool *is_quoted);
char			**enver(char **environ);
char			*value_expand(char *value, int *i, t_shell *shell);
bool			expansion(t_token *head, t_shell *shell);
bool			validation(t_token *head);
bool			is_redir(t_token *tokens);
void			mark_range(char *s);
int				count_fields(char *value);

void	debug_cmds(t_cmd *cmds);
void	debug_redirs(t_cmd *cmd, int fd);
void	debug_tokens(t_token *tokens, char *line);
#endif
