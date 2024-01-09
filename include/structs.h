/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvaz <rvaz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 12:06:56 by rvaz              #+#    #+#             */
/*   Updated: 2024/01/09 11:52:26 by rvaz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include "minishell.h"

typedef struct s_redirection
{
	char					*key_wrd;			//	[X]	The key word after the operand: limiter or file name
	int						type;				//	[X]	Redirection type (t_redir_type)
	struct s_redirection	*next;	 			//	[X]	Pointer to the next redirection struct
}				t_redirection;

typedef struct s_commands
{
	char				**cmds;					//	[X] The command and it respective arguments
	char				*cmd_path;				//	[ ] The path to the command's binary
	t_redirection		*redirects;				//	[X] All redirections
	int					hd_fd;					//	[ ] The fd corresponding to the here_doc
	int					read_fd;				//	[ ] The fd corresponding to the read_fd
	int					write_fd;				//	[ ] The fd corresponding to the write_fd
	struct s_commands	*next;					//	[X] Next command in the pipeline
	
}				t_commands;

typedef struct s_envp
{
	t_env_var			*vars;											//  pointer to var_list
	char				**env_array;									//	array with env
	int					exit_status;
	t_commands			*first_cmd_struct;								//Pointer to the struct of fist command in the pipeline
	char				*cursor;
	int					nbr_cmds;
	char				**tokens;
	t_env_var			*(*get)(const char *name);						//  (F) get env var struct 
	char				**(*make_array)(void);							//  (F) create env var array
	char				*(*get_value)(const char *name);				//  (F) get env var value
	void				(*set)(const char *name, const char *value);	//  (F) add var to envp
	void				(*unset)(const char *name);						//  (F) remove var from envp
	void				(*print)(void);									//  (F) print all env vars
	void				(*print_alpha)(void);							//	(F) prints variables sorted alphabetically
	void				(*destroy)();									//	(F) properly frees everything
																		//		that was allocated
}				t_envp;

typedef struct s_exec
{
	char			**bin_dir;					//	the splited binary directories
	int				nbr_bin;					//	number of binary directories
	int				fd[2];						//	pipe's file descriptors (in front)
	int				remainder_fd;				//	reading end of the back pipe
	pid_t			*pid;						//	pids of the command's processes
	t_envp			*envp;						//	pointer to envp struct
}				t_exec;

t_envp		*get_env_struct(void);

// commands.c

void			add_commands(t_commands **command_struct, char **tokens);
t_commands		*get_command_linkedlst(char *prompt);
void			addback_commandstruct(t_commands **lst,
					t_commands *new_commands);
void			free_commands(t_commands **command_struct);

//	env.c
void			init_env(char **envp);
void			destroy_env(void);
t_env_var		*get_env_var(const char *str);
char			*get_env_var_value(const char *str);
char			**create_env_array(void);
void			destroy_env_array(void);

// redirections.c

void			add_redirections(t_commands **command_struct, char **tokens);
t_redirection	*new_redirection(int type, char *key_wrd);
void			addback_redirection(t_redirection **head,
					t_redirection *new_redir);
void			free_redirections(t_redirection **redirections);
#endif