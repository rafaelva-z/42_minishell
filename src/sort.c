#include "../include/minishell.h"

/**
 * 
 * 	THIS WASN'T TESTED AND MAY NOT WORK
 * 
*/

static void printcontent(void *content)
{
	printf("%s", (char *)content);
}

static void swap(char *cont1, char *cont2)
{
	char *tmp;

	tmp = cont1;
	cont1 = cont2;
	cont2 = tmp;
}

static int	sort(char **cont, int low, int high)
{
	int	i;
	int	j;

		i = low - 1;
		j = low;
		while (j < high)
		{
			if (cont[j] < cont[high])
			{
				i++;
				swap(cont[i], cont[j]);
			}
			j++;
		}
		swap(cont[i + 1], cont[high]);
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

void	export_sort_print()
{
	t_envp		*shell;
	t_env_var	*tmp;
	char		**cont_str;
	int			i;

	shell = get_env_struct();
	if (!shell->vars)
		return ;
	cont_str = malloc(ft_lstsize(shell->vars) * sizeof(char *));
	if (cont_str)
		return ; 
	tmp = shell->vars;
	i = -1;
	while (tmp)
	{
		cont_str[++i] = tmp->content;
		tmp = tmp->next;
	}
	quicksort_str(cont_str, 0, i);
	ft_lstiter(cont_str, printcontent);
	free(cont_str);
}

// void	lst_insert_before(t_env_var *lst, t_env_var *new)
// {
// 	new->previous = lst->previous;
// 	new->next = lst;
// 	lst->previous->next = new;
// 	lst->previous = new;
// }

// void	export_sort_print()
// {
// 	t_envp		*shell;
// 	t_env_var	*envp_copy;
// 	t_env_var	*tmp_i;
// 	t_env_var	*tmp_j;
// 	int			count;
// 	int			compare;

// 	//sort
// 	count = ft_lstsize(shell->vars);
// 	shell = get_env_struct();
// 	envp_copy = ft_lstnew(shell->vars->content);
// 	tmp_i = envp_copy;
// 	while (count)
// 	{
// 		tmp_j = shell->vars;
// 		while (tmp_j)
// 		{
// 			compare = ft_strncmp(tmp_i->content, tmp_j->content, ft_strlen(tmp_i->content));
// 			if (compare < 0)
// 			{
// 				lst_insert_before(tmp_i, ft_lstnew(tmp_j->content)); // add before tmp_i
// 				break;
// 			}
// 			tmp_j = tmp_j->next;
// 		}
// 		if (compare >= 0)
// 			ft_lstadd_back(&envp_copy, ft_lstnew(tmp_j->content));
// 		count--;
// 	}

// 	//print
// 	ft_lstiter(envp_copy, printcontent);
// 	ft_lstclear(&envp_copy, free);
// }
