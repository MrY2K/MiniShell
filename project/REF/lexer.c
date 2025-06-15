/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bouhammo <bouhammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 15:25:28 by rel-mora          #+#    #+#             */
/*   Updated: 2024/10/04 23:27:29 by bouhammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_state	ft_get_state(t_idx *var, char s)
{
	if (var->in_d == -1 && s == '\"' && var->in_s == -1)
		return (var->in_d = 1, G);
	else if (var->in_d == 1 && s == '\"' && var->in_s == -1)
		return (var->in_d = -1, G);
	else if (var->in_d == 1 && ft_isprint(s) && var->in_s == -1)
		return (D);
	else if (var->in_d == -1 && ft_isprint(s) && var->in_s == -1 && s != '\'')
		return (G);
	else if (var->in_s == -1 && s == '\'' && var->in_d == -1)
		return (var->in_s = 1, G);
	else if (var->in_s == 1 && s == '\'' && var->in_d == -1)
		return (var->in_s = -1, G);
	else if (var->in_s == 1 && ft_isprint(s) && var->in_d == -1)
		return (S);
	else if (var->in_s == -1 && ft_isprint(s) && var->in_d == -1 && s != '\"')
		return (G);
	return (3);
}

void	ft_get_word(char *s, t_idx *var, t_splitor **x)
{
	int	i;

	i = 0;
	while (s[var->i] && !ft_check_input(s[var->i]))
	{
		var->state = ft_get_state(var, s[var->i]);
		var->i++;
		var->len++;
		i++;
	}
	ft_add(x, ft_lstnew(ft_substr(s, var->start, var->len), var->len, WORD,
			var->state));
}

void	ft_get_char(char *s, t_idx *var, t_splitor **x)
{
	var->len++;
	if (s[var->i] && s[var->i] == '$')
		ft_get_env(s, var, x);
	else
	{
		if (s[var->i] && ((s[var->i] == '>' && s[var->i + 1] == '>')
				|| (s[var->i] == '<' && s[var->i + 1] == '<')))
			ft_her_dir(x, var, s);
		else
			ft_add(x, ft_lstnew(ft_substr(s, var->start, var->len), var->len,
					ft_get_token(s[var->i]), ft_get_state(var, s[var->i])));
	}
	var->i++;
}

int	ft_lexer(char *s, t_splitor **x)
{
	t_idx	var;
	int		str_input_len;

	str_input_len = ft_strlen(s);
	var.i = 0;
	var.in_d = -1;
	var.in_s = -1;
	while (var.i < str_input_len)
	{
		var.start = var.i;
		var.len = 0;
		if (s[var.i] && !ft_check_input(s[var.i]))
			ft_get_word(s, &var, x);
		else if (s[var.i] && ft_check_input(s[var.i]))
			ft_get_char(s, &var, x);
	}
	if (var.in_d == 1 || var.in_s == 1 || ft_handler_syn_error(x))
		return (1);
	return (0);
}
