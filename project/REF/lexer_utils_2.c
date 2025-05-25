/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bouhammo <bouhammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 16:43:45 by rel-mora          #+#    #+#             */
/*   Updated: 2024/10/02 16:35:53 by bouhammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_her_dir(t_splitor **x, t_idx *var, char *s)
{
	var->len++;
	var->i++;
	if (var->len >= 1 && s[var->i] == '<')
		ft_add(x, ft_lstnew(ft_substr(s, var->start, var->len), var->len,
				HERE_DOC, ft_get_state(var, s[var->i])));
	else if (var->len >= 1 && s[var->i] == '>')
		ft_add(x, ft_lstnew(ft_substr(s, var->start, var->len), var->len,
				DREDIR_OUT, ft_get_state(var, s[var->i])));
}

void	ft_else(char *s, t_idx *var)
{
	var->state = ft_get_state(var, s[var->i]);
	var->i++;
	var->len++;
}

void	ft_num_env(char *s, t_idx *var)
{
	if (s[var->i] && ft_isdigit(s[var->i + 1]))
	{
		if (s[var->i] && ft_isdigit(s[var->i + 1]))
		{
			var->state = ft_get_state(var, s[var->i++]);
			var->len++;
		}
	}
	else
	{
		while (s[var->i] && !ft_check_input(s[var->i + 1])
			&& ft_isalnum(s[var->i + 1]))
		{
			var->state = ft_get_state(var, s[var->i++]);
			var->len++;
		}
	}
}

void	ft_check_env(char *s, t_idx *var)
{
	if (s[var->i] && s[var->i] == '$' && ft_isalnum(s[var->i + 1])
		&& !ft_check_input(s[var->i + 1]))
		ft_num_env(s, var);
	else if (s[var->i] && s[var->i] == '$' && s[var->i + 1] == '?')
		ft_else(s, var);
	else if (s[var->i] && s[var->i] == '$' && !ft_isalnum(s[var->i + 1])
		&& !ft_check_input(s[var->i + 1]))
	{
		while (s[var->i] && s[var->i] == '$' && !ft_isalnum(s[var->i + 1])
			&& !ft_check_input(s[var->i + 1]))
		{
			var->state = ft_get_state(var, s[var->i++]);
			var->len++;
		}
	}
	else
	{
		var->state = ft_get_state(var, s[var->i]);
	}
}

void	ft_get_env(char *s, t_idx *var, t_splitor **x)
{
	if ((s[var->i] && s[var->i + 1] && s[var->i + 2] && s[var->i] == '$')
		&& ((s[var->i + 1] == '\"' && s[var->i + 2] == '\"') || (s[var->i
					+ 1] == '\'' && s[var->i + 2] == '\'')))
	{
		var->state = G;
		var->i++;
		var->i++;
		var->i++;
		var->len++;
		var->len++;
		var->len++;
	}
	else if ((s[var->i] && s[var->i + 1] && s[var->i + 2] && s[var->i] == '$')
		&& ((s[var->i + 1] == '\"') || (s[var->i + 1] == '\'')) && (s[var->i
				+ 2] != '\'' || s[var->i + 2] != '\"'))
	{
		var->i++;
		var->state = ft_get_state(var, s[var->i]);
		var->len++;
	}
	else
		ft_check_env(s, var);
	ft_add(x, ft_lstnew(ft_substr(s, var->start, var->len), var->len, ENV,
			var->state));
}
