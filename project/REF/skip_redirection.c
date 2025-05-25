/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skip_redirection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-mora <rel-mora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 19:53:40 by rel-mora          #+#    #+#             */
/*   Updated: 2024/10/07 10:44:32 by rel-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_fill_final(char **s)
{
	int		i;
	char	*final;

	final = NULL;
	i = 0;
	while (s[i] != NULL)
	{
		final = ft_strjoin(final, s[i]);
		if (s[i + 1] != NULL)
			final = ft_strjoin(final, " ");
		i++;
	}
	return (final);
}

int	ft_check_ambiguous(t_splitor *tmp_x, t_environment *my_env)
{
	char	*s;
	char	**str;

	s = NULL;
	while ((tmp_x) != NULL)
	{
		if ((tmp_x)->state == G && (redirection(tmp_x) || tmp_x->type == '|'
				|| tmp_x->type == ' '))
			break ;
		if ((tmp_x) != NULL && tmp_x->type == '$' && tmp_x->state == G)
		{
			s = ft_expand(tmp_x->in, &my_env);
			if (s == NULL || (s != NULL && (s[0] == ' ' || s[0] == '\0')))
				return (free(s), 1);
			str = ft_split(s, ' ');
			if (ft_len_arg(str) > 1)
				return (free(s), ft_free_argment(str), 1);
			free(s);
			ft_free_argment(str);
		}
		if ((tmp_x) != NULL)
			tmp_x = tmp_x->next;
	}
	return (0);
}

int	ft_check_quote(t_splitor **tmp_x, char **final)
{
	while (((*tmp_x) != NULL && (*tmp_x)->next != NULL && ((*tmp_x)->state == G
				&& (*tmp_x)->next->state == G)) && (((*tmp_x)->type == '\"'
				&& (*tmp_x)->next->type == '\"') || ((*tmp_x)->type == '\''
				&& (*tmp_x)->next->type == '\''))
		&& ((*tmp_x)->next->next != NULL
			&& (redirection((*tmp_x)->next->next) != 1
				&& (*tmp_x)->next->next->type != 32
				&& (*tmp_x)->next->next->type == '$')))
	{
		(*tmp_x) = (*tmp_x)->next;
		(*tmp_x) = (*tmp_x)->next;
		return (1);
	}
	if (((*tmp_x) != NULL && (*tmp_x)->next != NULL && ((*tmp_x)->state == G
				&& (*tmp_x)->next->state == G)) && (((*tmp_x)->type == '\"'
				&& (*tmp_x)->next->type == '\"') || ((*tmp_x)->type == '\''
				&& (*tmp_x)->next->type == '\'')))
	{
		(*tmp_x) = (*tmp_x)->next;
		(*tmp_x) = (*tmp_x)->next;
		*final = ft_strdup("");
		return (1);
	}
	return (0);
}

char	*ft_skip_direction(t_splitor **tmp_x, t_environment *my_env,
		int *is_amb, int her)
{
	t_dir	id;

	id.str = NULL;
	id.final = NULL;
	if (ft_check_quote(tmp_x, &id.final))
		;
	else if ((*tmp_x) != NULL && (*tmp_x)->state == G && ((*tmp_x)->type == '\"'
			|| (*tmp_x)->type == '\''))
	{
		*is_amb = ft_check_ambiguous((*tmp_x), my_env);
		if (*is_amb == 1 && her == 1)
			return (NULL);
		ft_double_and_sigle(tmp_x, my_env, her, &id.str);
	}
	else if ((*tmp_x) != NULL && (*tmp_x)->state == G)
	{
		*is_amb = ft_check_ambiguous((*tmp_x), my_env);
		if (*is_amb == 1 && her == 1)
			return (NULL);
		ft_word(tmp_x, my_env, her, &id.str);
	}
	if (id.str != NULL)
		id.final = ft_fill_final(id.str);
	return (free_args(id.str), id.final);
}
