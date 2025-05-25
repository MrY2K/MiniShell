/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_skip.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-mora <rel-mora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 08:29:09 by rel-mora          #+#    #+#             */
/*   Updated: 2024/09/26 14:15:21 by rel-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_skip_spaces_in_count__2(t_splitor **tmp_x)
{
	while ((*tmp_x) != NULL && ((*tmp_x)->type == '\"'
			|| (*tmp_x)->type == '\''))
		(*tmp_x) = (*tmp_x)->next;
	ft_skip_spaces(tmp_x);
	while ((*tmp_x) != NULL && ((*tmp_x)->type == -1 || (*tmp_x)->type == '$'
			|| ((*tmp_x)->type == '\"' || (*tmp_x)->type == '\'')
			|| (((*tmp_x)->type == 32 && (*tmp_x)->state != G))))
		(*tmp_x) = (*tmp_x)->next;
	while ((*tmp_x) != NULL && ((*tmp_x)->type == '\"'
			|| (*tmp_x)->type == '\''))
		(*tmp_x) = (*tmp_x)->next;
}

void	ft_skip_spaces(t_splitor **tmp_x)
{
	while ((*tmp_x) != NULL && (*tmp_x)->type == ' ')
		(*tmp_x) = (*tmp_x)->next;
}

void	ft_skip_spaces_in_count(t_splitor **tmp_x)
{
	while ((*tmp_x) != NULL && ((*tmp_x)->type == '\"'
			|| (*tmp_x)->type == '\''))
		(*tmp_x) = (*tmp_x)->next;
	while ((*tmp_x) != NULL && (*tmp_x)->state != G)
		(*tmp_x) = (*tmp_x)->next;
	while ((*tmp_x) != NULL && ((*tmp_x)->type == '\"'
			|| (*tmp_x)->type == '\''))
		(*tmp_x) = (*tmp_x)->next;
}

void	ft_skip_not_word(t_splitor **tmp_x, t_environment *my_env)
{
	char	**str;

	str = NULL;
	while ((*tmp_x) != NULL && ((*tmp_x)->type == '<' || (*tmp_x)->type == '>'
			|| (*tmp_x)->type == DREDIR_OUT || (*tmp_x)->type == HERE_DOC))
	{
		(*tmp_x) = (*tmp_x)->next;
		ft_skip_spaces(tmp_x);
		while ((*tmp_x) != NULL && (*tmp_x)->state == G
			&& ((*tmp_x)->type == '\"' || (*tmp_x)->type == '\''))
			(*tmp_x) = (*tmp_x)->next;
		if ((*tmp_x) != NULL && (*tmp_x)->state == G && (*tmp_x)->type != '\"'
			&& (*tmp_x)->type != '\'' && (*tmp_x)->type != '|')
			ft_word(tmp_x, my_env, 0, &str);
		else if ((*tmp_x) != NULL && ((*tmp_x)->state == D
				|| (*tmp_x)->state == S))
			ft_double_and_sigle(tmp_x, my_env, 0, &str);
	}
	free_args(str);
}
