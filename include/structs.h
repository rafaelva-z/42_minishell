/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvaz <rvaz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 12:06:56 by rvaz              #+#    #+#             */
/*   Updated: 2024/01/13 13:16:18 by rvaz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include "minishell.h"

/**
 * char 			*key_wrd		The key word after the operand: limiter or file name
 * int				type			Redirection type (t_redir_type)
 * t_redirection	next			Pointer to the next redirection struct
*/
typedef struct s_redirection
{
	char					*key_wrd;
	int						type;
	struct s_redirection	*next;
}				t_redirection;

/**
 * char					**cmds;			the command and respective arguments 
 * char					*cmd_path;		The path to the command's binary
 * t_redirection		*redirects;		All redirections
 * int					hd_fd;			The fd corresponding to the here_doc
 * int					read_fd;		The fd corresponding to the read_fd
 * int					write_fd;		The fd corresponding to the write_fd
 * struct s_commands	*next;			Next command in the pipeline
*/
typedef struct s_commands
{
	char				**cmds;
	char				*cmd_path;
	t_redirection		*redirects;
	int					hd_fd;
	int					read_fd;
	int					write_fd;
	struct s_commands	*next;
}				t_commands;

/*
 * t_env_var			*vars			pointer to the linked list with all env vars
 * char					**env_array		pointer to an all env vars but in array format
 * t_commands			*commands		Pointer to the first command struct in the pipeline
 * char					*cursor			pointer to the cursor that is printed before every prompt
 * int					nbr_cmds		amount of command structs (pipe amount + 1)
*/
typedef struct s_envp
{
	t_env_var			*vars;
	char				**env_array;
	int					exit_status;
	t_commands			*commands;
	char				*cursor;
	int					nbr_cmds;
	char				**tokens;
	t_env_var			*(*get)(const char	*name);
	char				**(*make_array)(void);
	char				*(*get_value)(const char *name);
	void				(*set)(const char *name, const char *value);
	void				(*unset)(const char *name);
	int					(*print)(void);
	int					(*print_alpha)(void);
	void				(*destroy)();
}				t_envp;

/**
 * char				**bin_dir;			the splited binary directories
 * int				nbr_bin;			number of binary directories
 * int				fd[2];				pipe's file descriptors (in front)
 * int				remainder_fd;		reading end of the back pipe
 * pid_t			*pid;				pids of the command's processes
 * t_envp			*envp;				pointer to envp struct
*/
typedef struct s_exec
{
	char			**bin_dir;
	int				nbr_bin;
	int				fd[2];
	int				remainder_fd;
	pid_t			*pid;
	t_envp			*envp;
}				t_exec;

t_envp			*get_env_struct(void);

// commands.c

void			add_commands(t_commands **command_struct, char **tokens);
t_commands		*get_command_linkedlst(char *prompt);
void			addback_commandstruct(t_commands **lst,
					t_commands *new_commands);
void			free_commands(t_commands **command_struct);

//	env.c
void			init_env(char **envp);
void			free_env(void);
t_env_var		*get_env_var(const char *str);
char			*get_env_var_value(const char *str);
char			**create_env_array(void);
void			free_env_array(void);

// redirections.c

void			add_redirections(t_commands **command_struct, char **tokens);
t_redirection	*new_redirection(int type, char *key_wrd);
void			addback_redirection(t_redirection **head,
					t_redirection *new_redir);
void			free_redirections(t_redirection **redirections);
#endif