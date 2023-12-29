/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_sort.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvaz <rvaz@student.42lisboa.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 19:56:58 by rvaz              #+#    #+#             */
/*   Updated: 2023/12/29 19:58:30 by rvaz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	swap(char **cont1, char **cont2)
{
	char	*tmp;

	tmp = *cont1;
	*cont1 = *cont2;
	*cont2 = tmp;
}

static int	sort(char **cont, int low, int high)
{
	int	i;
	int	j;

	i = low - 1;
	j = low;
	while (j < high)
	{
		if (ft_strncmp(cont[j], cont[high], ft_strlen(cont[j])) < 0)
		{
			i++;
			swap(&cont[i], &cont[j]);
		}
		j++;
	}
	swap(&cont[i + 1], &cont[high]);
	return (i + 1);
}

static void	quicksort_str(char **cont, int low, int high)
{
	int	pivot;

	if (low < high)
	{
		pivot = sort(cont, low, high);
		quicksort_str(cont, low, pivot - 1);
		quicksort_str(cont, pivot + 1, high);
	}
}

/**
 * @brief	sorts enviroment variables alphabetically using quicksort,
 * 			and prints all variables
*/
void	export_sort_print(void)
{
	t_envp		*shell;
	t_env_var	*tmp;
	char		**cont_str;
	int			i;
	int			j;

	shell = get_env_struct();
	if (!shell->vars)
		return ;
	cont_str = malloc(ft_lstsize(shell->vars) * sizeof(char *));
	if (!cont_str)
		return ;
	tmp = shell->vars;
	i = -1;
	while (tmp)
	{
		cont_str[++i] = tmp->content;
		tmp = tmp->next;
	}
	quicksort_str(cont_str, 0, i);
	j = 0;
	while (j <= i)
		printf("%s\n", cont_str[j++]);
	free(cont_str);
}