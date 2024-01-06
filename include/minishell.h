/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scosta-j <scosta-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 15:33:05 by scosta-j          #+#    #+#             */
/*   Updated: 2023/09/07 15:33:05 by scosta-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define _XOPEN_SOURCE 700							// Dunno what this is but now sigaction works on my home pc
# include "../lib/libft/libft.h"
# include "structs.h"
# include <sys/wait.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdbool.h>

# define STDIN 0
# define STDOUT 1
# define STDERR 2

# define CURSOR		"@minishell>"
# define DQUOTE		'\"'
# define SQUOTE		'\''

// Error handling

# define ES_PIPE 4
# define CMD_N_FOUND 127

enum e_redir
{
	NONE,
	RDIR_IN = -1,
	RDIR_HDOC = -2,
	RDIR_OUT = -3,
	RDIR_APP = -4,
	RDIR_PIPE = -5,
	RDIR_DPIPE = -6
};

enum e_negative_prompt
{
	GREAT = -62,
	MINOR = -60,
	PIPE = -124,
	SPC = -32,
	SINGQ = -39,
	DOUBQ = -34,
};

void		set_signals(void);

//	Built-ins

void		cd(char **cmds);
void		echo(char **prompt);
void		print_env(void);
void		exit_shell(t_exec *exec);
void		export(char **cmds);
void		set_env_var(const char *name, const char *value);
void		export_sort_print(void);
void		pwd(void);
void		unset(char **cmds);

//	utils.c

bool		var_name_check(const char *str);
void		lst_insert_before(t_env_var *lst, t_env_var *new_lst);
void		var_printcontent(void *content);
int			is_redir(char c);
int			is_inside_quotes(char *str, size_t index);
int			contains_only_nbr(char *str);

//	utils2.c

int			to_close(int fd);
int			what_redir_token(char *str);
void		set_shlvl();

// quote_check.c

int			quote_check(const char *str);

//	prompt_cleaner.c

char		*prompt_cleaner(const char *prompt);
char		*add_spaces_redirections(char *prompt);

// redir_check.c

int			redirection_check(char *prompt);

// redir_utils.c

int			is_redir(char c);
int			is_redir_val(char c);
int			what_redir(char *str);
int			hasredir(char *prompt);

// tokenizer.c

char		**tokenizer(char *s);

// here_doc.c

void		here_doc_manager(void);

// executor

void		process_generator(void);

// path_handeling.c

void		bin_finder(t_exec *exec);
void		path_finder(t_exec *exec, t_commands *cmd);

// redirections.c

void		redir_in(t_exec *exec, t_commands *cmd, t_redirection *redir);
void		redir_out_trunc(t_exec *exec, t_commands *cmd,
				t_redirection *redir);
void		redir_out_append(t_exec *exec, t_commands *cmd,
				t_redirection *redir);
void		redirect(t_exec *exec, t_commands *cmd);

// exec_utils.c
int			builtin_check(t_exec *exec, t_commands *cmd);
void		exec_destroy(t_exec *exec);

// destroyer
void		destroy_all(t_exec *exec, char *message, int exit_status);
void		desplay_error(char *error_msg);

#endif