/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvaz <rvaz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 17:21:47 by fda-estr          #+#    #+#             */
/*   Updated: 2024/01/12 16:59:34 by rvaz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char *key_word(char *s)
{
	int		i;
	char	*key_wrd;

	i = 0;
	while (s[i] && s[i] != ' ' && s[i] != DQUOTE)
		i++;
	key_wrd = malloc(i + 1);
	key_wrd[i] = 0;
	i = -1;
	while (s[++i] && s[i] != ' ' && s[i] != DQUOTE)
		key_wrd[i] = s[i];
	return (key_wrd);
}

char	*expand(char *s)
{
	char	*key_wrd;
	char	*var;


	key_wrd = key_word(s);
	var = get_env_var_value((const char *)key_wrd);
	if (!var)
	{
		free (key_wrd);
		return (NULL);
	}
	free (key_wrd);
	return (ft_strdup(var));
}

static void	expansion_prep(char **prompt)
{
	int		i;
	int		neg_len;
	char	*prod;

	i = -1;
	neg_len = 0;
	if (!prompt || !*prompt || !**prompt)
		return ;
	while ((*prompt)[++i + 1])
	{
		if ((*prompt)[i] == '$' && ft_isdigit((*prompt)[i + 1]))
		{
			(*prompt)[i] = -1;
			(*prompt)[i + 1] = -1;
			neg_len += 2;
		}
	}
	prod = malloc(ft_strlen(*prompt) - neg_len + 1);
	i = -1;
	neg_len = 0;
	while ((*prompt)[++i])
	{
		prod[i - neg_len] = (*prompt)[i];
		if ((*prompt)[i] == -1)
			neg_len++;
	}
	prod[i - neg_len] = 0;
	free (*prompt);
	*prompt = prod;
}

static int	expansion_check(char *c, char *prompt, int i)
{
	if (*c != '$')
		return (1);
	if (ft_isalpha(*(++c)) || *c == '_' || *c == '?'
		|| is_inside_quotes(prompt, i) == 1)
		return (0);
	return (1);
}

char	*expansions(char *prompt, char *first_prompt)
{
	int		i;
	char	*expanded_str;
	char	*prod;

	i = 0;
	expanded_str = NULL;
	if (!prompt || !*prompt)
		return (prompt);
	while (prompt[i] && expansion_check(&prompt[i], prompt, i))
		i++;
	if (!prompt[i] || !(prompt[i + 1]))
		return (prompt);
	if (prompt[i + 1] == '?')
	{
		prompt[i] = 0;
		expanded_str = ft_strjoin_free(prompt,
				ft_itoa(get_env_struct()->exit_status), 2);
		if (prompt == first_prompt)
			free (prompt);
		return (expanded_str);
	}
	prompt[i] = 0;
	expanded_str = ft_strjoin_free(prompt, expand(prompt + i + 1), 2);
	while (prompt[++i] && prompt[i] != ' ' && prompt[i] != '\"')
		;
	if (!prompt[i])
	{
		if (prompt == first_prompt)
			free (prompt);
		return (expanded_str);
	}
	prod = ft_strjoin_free(expanded_str,
			expansions(prompt + i, first_prompt), 3);
	if (prompt && prompt == first_prompt)
		free (prompt);
	return (prod);
}

void	expansion_manager(char **prompt)
{
	expansion_prep(prompt);
	*prompt = expansions(*prompt, *prompt);
}
