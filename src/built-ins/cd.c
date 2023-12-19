/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvaz <rvaz@student.42lisboa.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 12:44:29 by scosta-j          #+#    #+#             */
/*   Updated: 2023/09/23 15:11:54 by rvaz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	set_pwd(char *oldpwd)
{
	char	*oldpwd_var;
	char	*pwd_var;
	char	*cwd;
	t_envp	*shell;

	shell = get_env_struct();
	oldpwd_var = ft_strjoin("OLDPWD=", oldpwd);
	if (!oldpwd_var)
		return ;
	cwd = getcwd(NULL, 0);
	pwd_var = ft_strjoin("PWD=", cwd);
	if (!pwd_var)
		return ;
	shell->set(oldpwd_var);
	shell->set(pwd_var);
	free(oldpwd_var);
	free(pwd_var);
	if (cwd)
		free(cwd);
}

/**
 * @brief change the working directory
*/
void	cd(char *path)
{
	int		r;
	char	*home;
	char	*oldpwd;
	t_envp	*shell;

	
	shell = get_env_struct();
	home = shell->get_value("HOME");
	r = -1;
	if ((!path && !home) || (path && !*path))
		return ;
	oldpwd = getcwd(NULL, 0);
	if (!path)
		r = chdir(home);
	// else if (*path == '~')
	// {
	// 	path = ft_strjoin(home, path + 1);
	// 	r = chdir(path);
	// 	free(path);
	// 	if (r < 0)
	// 		perror("insert error message here");
	// }
	else
		r = chdir(path);
	if (r < 0)
		perror(""); // how do i make this work properly?
	else
		set_pwd(oldpwd);
	if (oldpwd)
		free(oldpwd);
}

//	do we have to define tab key behaviour?

/**
 * 	CD =============================
 * 
 * 	No args				->	cd to home				DONE
 * 	Empty args			->	do nothing				DONE
 *  Args 				->	cd to arg				DONE
 *	Args.Arg not found	->	error					NOT SIMILAR
 * 	
 *  HOME not set		->	"~" Doesn't work & no args does nothing
 * 	PWD/OLDPWD not set	->	everything works normally when changing
 * 							directories always updates PWD/OLDPWD
*/