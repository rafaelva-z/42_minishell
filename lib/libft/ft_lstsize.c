/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvaz <rvaz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 23:23:43 by rvaz              #+#    #+#             */
/*   Updated: 2023/09/16 12:08:45 by rvaz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_env_var *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}

/* 
#include <stdio.h>
int	main()
{
	t_env_var *list1;
	t_env_var *list2;
	t_env_var *list3;

	list1 = ft_lstnew("");
	list2 = ft_lstnew("");
	list3 = ft_lstnew("");

	ft_lstadd_front(&list1, list2);
	ft_lstadd_front(&list2, list3);
	printf("Result: %d", ft_lstsize(list1));
}  */