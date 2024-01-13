/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvaz <rvaz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 18:57:24 by rvaz              #+#    #+#             */
/*   Updated: 2024/01/08 18:57:24 by rvaz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef MINISHELL_H
# define MINISHELL_H

# define _XOPEN_SOURCE 700							// Dunno what this is but now sigaction works on my home pc
# include "../lib/libft/libft.h"
# include "structs.h"
# include <sys/wait.h>
# include <sys/stat.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdbool.h>
# include <termios.h>

# define CURSOR		"@minishell>"
# define DQUOTE		'\"'
# define SQUOTE		'\''

// Exit Status

# define ES_OP_N_PERM		1
# define ES_RDIR_TOKEN 		2
# define ES_PIPE			4
# define ES_ALLOC_FAIL		12
# define ES_K_N_AVAIL		126
# define ES_CMD_N_FOUND		127
# define ES_SIGINT			130

// Error Messages

# define ERR_ALLOC				"minishell: memory alocation failed\n"
# define ERR_QUOTES				"error: quotes open\n" 
# define ERR_RDIR				"syntax error unexpected token\n"
# define ERR_CD					"minishell: cd"
# define ERR_CD_TOO_MANY_ARG	"minishell: cd: too many arguments\n"
# define ERR_CD_HOME_NOT_SET	"minishell: cd: HOME not set\n"

# define MSG_EXIT				ft_strdup("exit\n")
# define MSG_HDOC_EOF			"minishell: warning: here-document delimited by end-of-file (wanted `EOF')\n"
# define MSG_SHLVL_HIGH			"warning: shell level (insert value here) too high, resetting to 1"

extern int	g_signal;

enum e_signalhandlers
{
	HNDLR_MAIN,
	HNDLR_CHILD_HD,
	HNDLR_LOOP
};

enum e_redir
{
	NONE,
	RDIR_IN		=	-1,
	RDIR_HDOC	=	-2,
	RDIR_OUT	=	-3,
	RDIR_APP	=	-4,
	RDIR_PIPE	=	-5,
	RDIR_DPIPE	=	-6
};

enum e_negative_char_prompt
{
	GREAT		=	-62,
	MINOR		=	-60,
	PIPE		=	-124,
	SPC			=	-32,
	SINGQ		=	-39,
	DOUBQ		=	-34,
};

void		set_signals(int process);
void		expansion_manager(char **prompt);
int			prompt_processing(char **prompt);

//	main.c

void		get_prompt_cursor(void);

//	Built-ins

int			cd(char **cmds);
int			echo(char **prompt);
int			print_env(void);
int			export(char **cmds);
void		set_env_var(const char *name, const char *value);
int			export_sort_print(void);
int			pwd(void);
int			unset(char **cmds);

//	free_memory.c

void		free_matrix_and_commands(void);
void		free_and_exit(t_exec *exec, char *message, int exit_status);

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

//	utils3.c

int			get_pipe_count(char *str);
int			count_commands(char **tokens, size_t pipe);

// quote_check.c

int			quote_check(const char *str);

//	prompt_cleaner.c

int			prompt_cleaner(char **prompt);
void		add_spaces_redirections(char **prompt);

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

// path_handling.c

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
void		builtin_exec_child(t_exec *exec, t_commands *cmd);
int			builtin_exec_parent(t_exec *exec, t_commands *cmd);
void		free_exec(t_exec *exec);

// destroyer
int		display_error(char *error_msg, int exit_status);

// error_handling

char		*message_joiner(int nbr, ...);

// expander_2.c

int			expansion_check(char *c, char *prompt, int i);
void		expansion_prep(char **prompt, int i, int neg_len);
void	    expander_aux(char *prpt, int rec);

#endif

/* "$DISPLAY" '?PATH' */