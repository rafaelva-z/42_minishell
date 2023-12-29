/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvaz <rvaz@student.42lisboa.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 23:57:46 by rvaz              #+#    #+#             */
/*   Updated: 2023/12/29 19:47:11 by rvaz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_env_var **lst, t_env_var *new_lst)
{
	t_env_var	*last;

	if (!new_lst)
		return ;
	new_lst->next = NULL;
	if (!*lst)
	{
		*lst = new_lst;
		new_lst->previous = NULL;
		return ;
	}
	else
	{
		last = ft_lstlast(*lst);
		last->next = new_lst;
		new_lst->previous = last;
	}
}

/* #include <stdio.h>
int	main()
{
	t_env_var *list1;
	t_env_var *list2;
	t_env_var *list3;

	list1 = ft_lstnew("");
	list2 = ft_lstnew("");
	list3 = ft_lstnew("");

	ft_lstadd_back(&list1, list2);
	ft_lstadd_back(&list2, list3);
	printf("Result: %d", ft_lstsize(list1));
} */