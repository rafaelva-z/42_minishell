/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvaz <rvaz@student.42lisboa.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 13:42:26 by scosta-j          #+#    #+#             */
/*   Updated: 2023/11/06 15:17:57 by rvaz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/**
 * @brief print the given content (char *). To be used with ft_lstiter
 * @param content the content to print (char *)
*/
void var_printcontent(void *content)
{
	printf("%s\n", (char *)content);
}

/**
 * @brief checks if the string a valid enviroment variable with a valid name
 * @return 0 if invalid, 1 if valid
*/
bool	var_name_check(const char *str)
{
	int	i;

	i = 0;
	if (!str || (!ft_isalpha(str[i]) && str[i] != '_')
		|| ft_strchr(str, '=') == NULL)
		return (false);
	while (str[++i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (false);
	}
	return (true);
}

/**
 * @brief insert a variable before the specified variable on the linked list
*/
void	lst_insert_before(t_env_var *lst, t_env_var *new_lst)
{
	new_lst->previous = lst->previous;
	new_lst->next = lst;
	if(lst->previous)
	{
		if (lst->previous->next)
			lst->previous->next = new_lst;
		lst->previous = new_lst;
	}
}