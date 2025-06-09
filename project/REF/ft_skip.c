/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_skip.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achoukri <achoukri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 08:29:09 by rel-mora          #+#    #+#             */
/*   Updated: 2025/06/09 00:59:31 by achoukri         ###   ########.fr       */
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

