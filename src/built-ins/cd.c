/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvaz <rvaz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 12:44:29 by rvaz       	   #+#    #+#             */
/*   Updated: 2024/01/12 13:10:53 by rvaz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	set_pwd(char *oldpwd)
{
	char	*cwd;
	t_envp	*shell;

	shell = get_env_struct();
	cwd = getcwd(NULL, 0);
	if (cwd)
	{
		shell->set("PWD", cwd);
		free(cwd);
	}
	if (oldpwd)
		shell->set("OLDPWD", oldpwd);
}

/**
 * @brief change the working directory
*/
int	cd(char **cmds)
{
	int		r;
	char	*home;
	char	*oldpwd;

	if (count_cmds(cmds) > 1)
		return (display_error(ERR_CD_TOO_MANY_ARG, 1));
	home = get_env_struct()->get_value("HOME");
	if ((!cmds[0] || !cmds[0][0]) && !home)
		return (display_error(ERR_CD_HOME_NOT_SET, 1));
	oldpwd = getcwd(NULL, 0);
	if (!cmds[0])
		r = chdir(home);
	else
		r = chdir(cmds[0]);
	if (r < 0)
	{
		perror(ERR_CD);
		return (1);
	}
	else if (oldpwd)
		set_pwd(oldpwd);
	if (oldpwd)
		free(oldpwd);
	return (0);
}

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