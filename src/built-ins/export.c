/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvaz <rvaz@student.42lisboa.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 14:28:32 by rvaz              #+#    #+#             */
/*   Updated: 2023/09/28 14:40:33 by rvaz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// static void printcontent(void *content)
// {
// 	printf("%s", (char *)content);
// }

static void swap(char **cont1, char **cont2)
{
	char *tmp;

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

		quicksort_str(cont,  low, pivot - 1);
		quicksort_str(cont, pivot + 1, high);
	}
}
/**
 * @brief sorts enviroment variables alphabetically using quicksort, and prints all variables
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


/**
 * @brief sets the env variable given
 * @param name the variable to set
 * @example set_env_var("PATH", "/bin:/usr/bin");
*/
static void	set_env_var(const char *name, const char *value)
{
	t_envp		*shell;
	t_env_var	*current;
	char		*var_name;

	if (!name)
		return ;
	shell = get_env_struct();
	current = get_env_var(name);
	var_name = ft_strjoin(name, "=");
	if (!current)
		ft_lstadd_back(&shell->vars, ft_lstnew(ft_strjoin(var_name, value)));
	else
	{
		free(current->content);
		current->content = ft_strjoin(var_name, value);
	}
	free(var_name);
	//  do nothing if var and value are the same as existing one
}

/**
 *	@brief set the export attribute for variables
 *	@example export("VAR_NAME=VAR_VALUE");
*/
void	export(const char *str)
{
	t_envp		*shell;
	char		*var_value;
	char		*var_name;
	int			i;

	i = 0;
	shell = get_env_struct();
	if (!str)
	{
		export_sort_print();
		return ;
	}
	if (!var_name_check(str))
		return ;
	while (str[i] != '=')
		i++;
	var_name = ft_substr(str, 0, i);
	var_value = ft_substr(str, i + 1, ft_strlen(str)
			- (ft_strlen(var_name) + 1));
	set_env_var(var_name, var_value);
	free(var_name);
	free(var_value);
}

/**
 * EXPORT =============================
 * 
 * 	Must begin with letter or underscore
 * 	var name can't start with a number
 * 	var name can't contain symbols or spaces
*/
