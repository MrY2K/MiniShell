/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achoukri <achoukri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 02:20:27 by achoukri          #+#    #+#             */
/*   Updated: 2025/06/21 02:31:21 by achoukri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_check_ambiguous(t_token *tmp_t, t_env *env, t_minibash b)
{
	char	*s;
	char	**str;

	(void)b;
	s = NULL;
	while ((tmp_t) != NULL)
	{
		if ((tmp_t)->state == N && (redirection(tmp_t)
				|| tmp_t->type == '|' || tmp_t->type == ' '))
			break ;
		if ((tmp_t) != NULL && tmp_t->type == '$' && tmp_t->state == N)
		{
			s = ft_expand(tmp_t->value, &env);
			if (s == NULL || (s != NULL && (s[0] == ' ' || s[0] == '\0')))
				return (free(s), 1);
			str = ft_split(s, ' ');
			if (ft_len_arg(str) > 1)
				return (free(s), free_argument_array(str), 1);
			free(s);
			free_argument_array(str);
		}
		if ((tmp_t) != NULL)
			tmp_t = tmp_t->next;
	}
	return (0);
}

int	ft_check_quote(t_token **tmp_t, char **final)
{
	while (((*tmp_t) != NULL && (*tmp_t)->next != NULL
			&& ((*tmp_t)->state == N
				&& (*tmp_t)->next->state == N)) && (((*tmp_t)->type == '\"'
				&& (*tmp_t)->next->type == '\"') || ((*tmp_t)->type == '\''
				&& (*tmp_t)->next->type == '\''))
		&& ((*tmp_t)->next->next != NULL
			&& (redirection((*tmp_t)->next->next) != 1
				&& (*tmp_t)->next->next->type != 32
				&& (*tmp_t)->next->next->type == '$')))
	{
		(*tmp_t) = (*tmp_t)->next;
		return ((*tmp_t) = (*tmp_t)->next, 1);
	}
	if (((*tmp_t) != NULL && (*tmp_t)->next != NULL
			&& ((*tmp_t)->state == N
				&& (*tmp_t)->next->state == N)) && (((*tmp_t)->type == '\"'
				&& (*tmp_t)->next->type == '\"') || ((*tmp_t)->type == '\''
				&& (*tmp_t)->next->type == '\'')))
	{
		(*tmp_t) = (*tmp_t)->next;
		(*tmp_t) = (*tmp_t)->next;
		return (*final = ft_strdup(""), 1);
	}
	return (0);
}
