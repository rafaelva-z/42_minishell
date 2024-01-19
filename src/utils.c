/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvaz <rvaz@student.42lisboa.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 13:42:26 by rvaz              #+#    #+#             */
/*   Updated: 2024/01/18 13:50:41 by rvaz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/**
 * @brief print the given content (char *). To be used with ft_lstiter
 * @param content the content to print (char *)
*/
void	env_var_print(void *content)
{
	if (content && ft_strchr(content, '='))
		printf("%s\n", (char *)content);
}

/**
 * @brief checks if the string a valid enviroment variable name
 * @return 0 if invalid, 1 if valid
*/
bool	var_name_check(const char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (true);
	if (!ft_isalpha(str[i]) && str[i] != '_')
		return (false);
	while (str[++i] && str[i] != '=')
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (false);
	return (true);
}

/**
 * @brief insert a variable before the specified variable on the linked list
*/
void	lst_insert_before(t_env_var *lst, t_env_var *new_lst)
{
	new_lst->previous = lst->previous;
	new_lst->next = lst;
	if (lst->previous)
	{
		if (lst->previous->next)
			lst->previous->next = new_lst;
		lst->previous = new_lst;
	}
}

/**
 * @brief	checks if the given character is inside quotes
 * @return	0 if the character is not inside quotes,
 * 			1 if it is inside single quotes
 * 			2 if it is inside double quotes.
*/
int	is_inside_quotes(char *str, size_t index)
{
	char	c;

	c = 0;
	if (!str || index > ft_strlen(str))
		return (0);
	while (*str && index--)
	{
		if (!c)
		{
			if (*str == '\'' || *str == '\"')
				c = *str;
		}
		else if (c == *str)
			c = 0;
		str++;
	}
	if (c == *str)
		c = 0;
	return ((c == '\'') + ((c == '\"') * 2));
}

/**
 *	@brief	checks if the given string contains only numbers
*/
int	contains_only_nbr(char *str)
{
	int	i;

	i = -1;
	if (!str)
		return (0);
	if (str[0] == '-' || str[0] == '+')
		i++;
	while (str[++i])
		if (!ft_isdigit(str[i]))
			return (0);
	return (1);
}
