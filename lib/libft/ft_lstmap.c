/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvaz <rvaz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 01:42:06 by rvaz              #+#    #+#             */
/*   Updated: 2023/09/16 12:08:45 by rvaz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_env_var	*ft_lstmap(t_env_var *lst, void *(*f)(void *), void (*del)(void *))
{
	t_env_var	*new;
	t_env_var	*tmp;

	if (!lst)
		return (NULL);
	new = ft_lstnew(f(lst->content));
	tmp = lst->next;
	while (tmp)
	{
		ft_lstadd_back(&new, ft_lstnew(f(tmp->content)));
		tmp = tmp->next;
	}
	del(tmp);
	return (new);
}
