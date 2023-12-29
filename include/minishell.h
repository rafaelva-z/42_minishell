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
// # define IN		'<'
// # define OUT		'>'
// # define PIPE	'|'

enum e_redir
{
	NONE,
	RDIR_IN,
	RDIR_OUT,
	RDIR_PIPE,
	RDIR_APP,
	RDIR_HDOC,
	RDIR_DPIPE
};

typedef struct s_envp
{
	t_env_var			*vars;								//  pointer to var_list
	char				**env_array;						//	array with env
	int					exit_status;
	t_env_var			*(*get)(const char *name);			//  (F) get env var struct 
	char				**(*make_array)(void);				//  (F) create env var array
	char				*(*get_value)(const char *name);	//  (F) get env var value
	void				(*set)(const char *str);			//  (F) add var to envp
	void				(*unset)(const char *name);			//  (F) remove var from envp
	void				(*print)(void);						//  (F) print all env vars
	void				(*print_alpha)(void);				//	(F) prints variables sorted alphabetically
	void				(*destroy)();						//	(F) properly frees everything
															//		that was allocated
}				t_envp;

// typedef struct s_commands
// {
// 	char				**cmds;					//	[X] The command and it respective arguments
// 	char				*cmd_path;				//	[ ] The path to the command's binary
// 	t_redirection		*redirect;				//	[X] All redirections
// 	int					hd_fd;					//	[ ] The fd corresponding to the here_doc
// 	int					read_fd;				//	[ ] The fd corresponding to the read_fd
// 	int					write_fd;				//	[ ] The fd corresponding to the write_fd
// 	struct s_commands	*next;					//	[X] Next command in the pipeline
	
// }				t_commands;

t_envp		*get_env_struct(void);
void		set_signals(void);

//	Built-ins

void		cd(char *path);
void		echo(char *arg);
void		print_env(void);
void		exit_shell(int exit_code);
void		export(const char *str);
void		export_sort_print(void);
void		pwd(void);
void		unset(const char *str);
void		pwd(void);

//	Utils

bool		var_name_check(const char *str);
void		lst_insert_before(t_env_var *lst, t_env_var *new_lst);
void		var_printcontent(void *content);
int			is_redir(char c);

//	_env.c

void		init_env(char **envp);
void		destroy_env(void);
t_env_var	*get_env_var(const char *str);
char		*get_env_var_value(const char *str);
char		**create_env_array(void);
void		destroy_env_array(void);

//	prompt_cleaner.c

char		*prompt_cleaner(const char *prompt);
int			quote_check(const char *str);

// redir_check.c

int			redirection_check(char *prompt);
int			is_inside_quotes(char *str, int index);

// redir_utils.c

int			is_redir(char c);
int			what_redir(char *str);
int			hasredir(char *prompt);

#endif