/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvaz <rvaz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 17:21:47 by fda-estr          #+#    #+#             */
/*   Updated: 2024/01/19 15:14:33 by rvaz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * @brief	returns name of the environment variable
*/
static char	*key_word(char *s, int *i)
{
	int		j;
	char	*key_wrd;

	j = 0;
	if (*s == '?')
	{
		*i += 2;
		return (ft_strdup("?"));
	}
	while (s[j] && s[j] != ' ' && s[j] != '\"' && s[j] != '\'' && s[j] != '$')
		j++;
	key_wrd = malloc(j + 1);
	key_wrd[j] = 0;
	j = -1;
	while (s[++j] && s[j] != ' ' && s[j] != '\"' && s[j] != '$' && s[j] != '\'')
		key_wrd[j] = s[j];
	*i += j + 1;
	return (key_wrd);
}

/**
 * @brief	expands the given string returning the value of the
 * 			environment variable
*/
static char	*expand(char *s, int *i)
{
	char	*key_wrd;
	char	*var;

	key_wrd = key_word(s, i);
	if (!ft_strncmp(key_wrd, "?", 1))
	{
		free (key_wrd);
		return (ft_itoa(get_env_struct()->exit_status));
	}
	var = get_env_var_value((const char *)key_wrd);
	free (key_wrd);
	if (!var)
	{
		var = safe_malloc(1);
		*var = '\0';
		return (var);
	}
	return (ft_strdup(var));
}

/**
 * @brief	checks if the given character '$' is the start of a valid expansion
*/
static void	limiter_masker(char *prompt)
{
	int	i;

	i = -1;
	while (prompt[++i])
	{
		if (is_inside_quotes(prompt, i) != 1
			&& prompt[i] == '<' && prompt[i + 1] == '<')
			i += 3;
		else
			continue ;
		while (prompt[i] && !(prompt[i] == ' '
				&& is_inside_quotes(prompt, i) == 0))
		{
			if (prompt[i] == '$')
				prompt[i] = -1;
			i++;
		}
	}
}

/**
 * @brief	expands all valid expansions in the given string
 * @return	the string with expanded values
*/
static char	*expansion(char *prompt, int rec, int i, char *expnd_str)
{
	char	*prd;

	if (!prompt || !*prompt)
		return (NULL);
	if (!expansion_check_str(prompt))
	{
		if (rec == 0)
			return (prompt);
		return (ft_strdup(prompt));
	}
	while (prompt[i] && prompt[i] != '$')
		i++;
	prompt[i] = '\0';
	expnd_str = ft_strjoin_free(prompt, expand(prompt + i + 1, &i), 2);
	prd = ft_strjoin_free(expnd_str,
			expansion(prompt + i, rec + 1, 0, NULL), 3);
	if (rec == 0)
		free (prompt);
	return (prd);
}

void	expansion_manager(char **prompt)
{
	int		i;

	i = -1;
	if (!expansion_check_str(*prompt))
		return ;
	expansion_prep(prompt, -1, 0, NULL);
	expansion_masker(*prompt);
	limiter_masker(*prompt);
	*prompt = expansion(*prompt, 0, 0, NULL);
	while ((*prompt)[++i])
		if ((*prompt)[i] == -1)
			(*prompt)[i] = '$';
}
