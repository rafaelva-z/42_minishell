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

/**
 * 	CD =============================
 * 
 * 	No arguments		->	cd to home
 * 	NULL argument(s)	->	do nothing
 *  file/exists			->	cd to path
 *	file/doesnt/exist	->	error
 * 	PWD/OLDPWD not set	->	everything works normally
 * 	$HOME not set		->	cd with no args doesn't work
 *	Note: When changing directories always updates PWD/OLDPWD
*/

/**
 *	@brief	sets the $PWD and $OLDPWD env vars to the current and last
 *			working directories respectively
*/
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

static int	cd_part2(int r)
{
	char	*oldpwd;

	if (r < 0)
	{
		perror(ERR_CD);
		return (1);
	}
	oldpwd = getcwd(NULL, 0);
	if (oldpwd)
	{
		set_pwd(oldpwd);
		free(oldpwd);
	}
	return (0);
}

/**
 * @brief change the working directory
*/
int	cd(char **cmds)
{
	int		r;
	char	*home;

	if (count_cmds(cmds) > 1)
		return (display_error(ERR_CD_TOO_MANY_ARG, 1));
	home = get_env_struct()->get_value("HOME");
	if (!cmds[0] && !home)
		return (display_error(ERR_CD_HOME_NOT_SET, 1));
	if (!cmds[0])
		r = chdir(home);
	else if (!cmds[0][0])
		return (0);
	else
		r = chdir(cmds[0]);
	if (cd_part2(r))
		return (1);
	return (0);
}
