/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvaz <rvaz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 17:21:47 by fda-estr          #+#    #+#             */
/*   Updated: 2024/01/13 16:41:22 by fda-estr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*key_word(char *s, int *quote)
{
	int		i;
	char	*key_wrd;

	i = 0;
	while (s[i] && s[i] != ' ' && s[i] != DQUOTE && s[i] != '$')
		i++;
	key_wrd = malloc(i + 1);
	key_wrd[i] = 0;
	i = -1;
	while (s[++i] && s[i] != ' ' && s[i] != DQUOTE && s[i] != '$')
		key_wrd[i] = s[i];
	if (s[i] == DQUOTE)
		*quote = 1;
	return (key_wrd);
}

static char	*expand(char *s)
{
	char	*key_wrd;
	char	*var;
	int		quote;
	char	*prod;

	quote = 0;
	prod = NULL;
	key_wrd = key_word(s, &quote);
	if (!ft_strncmp(key_wrd, "?", 2))
	{
		free (key_wrd);
		return (ft_itoa(get_env_struct()->exit_status));
	}
	var = get_env_var_value((const char *)key_wrd);
	if (!var)
	{
		free (key_wrd);
		return (NULL);
	}
	free (key_wrd);
	if (quote)
		prod = "\"";
	return (ft_strjoin_free(var, prod, 0));
}

static char	*expansion(char *prpt, int rec, int i, char *expnd_str)
{
	char	*prd;

	if (!prpt || !*prpt)
		return (prpt);
	if (prpt[i] == '\"')
		prpt++;
	while (prpt[i] && expansion_check(&prpt[i], prpt, i))
		i++;
	if (!prpt[i] || !(prpt[i + 1]))
	{
		if (rec)
			return (ft_strdup(prpt));
		return (prpt);
	}
	prpt[i] = 0;
	expnd_str = ft_strjoin_free(prpt, expand(prpt + i + 1), 2);
	while (prpt[++i] && prpt[i] != ' ' && prpt[i] != '\"' && prpt[i] != '$')
		;
	if (!prpt[i] && rec == 0)
		free (prpt);
	if (!prpt[i])
		return (expnd_str);
	prd = ft_strjoin_free(expnd_str, expansion(prpt + i, rec + 1, 0, NULL), 3);
	expander_aux(prpt, rec);
	return (prd);
}

static void	limiter_protect(char *s)
{
	int	i;

	i = -1;
	while (s[++i])
	{
		if (s[i] == '<' && s[i + 1] == '<')
			i += 3;
		else
			continue ;
		if (s[i] == '\"')
			i++;
		while (s[i] && s[i] == ' ')
			i++;
		if (s[i] == '$')
			s[i] = -1;
	}
}

void	expansion_manager(char **prompt)
{
	int		i;
	char	*temp;

	i = -1;
	expansion_prep(prompt, -1, 0);
	limiter_protect(*prompt);
	*prompt = expansion(*prompt, 0, 0, NULL);
	temp = *prompt;
	while (temp[++i])
	{
		if (temp[i] == -1)
			temp[i] = '$';
	}
}
