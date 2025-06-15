/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_join.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bouhammo <bouhammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 08:32:43 by rel-mora          #+#    #+#             */
/*   Updated: 2024/09/28 13:53:05 by bouhammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_join_next(char ***arr_join, t_splitor **tmp_x, t_environment *my_env,
		int j)
{
	char	*s;

	s = NULL;
	while ((*tmp_x) != NULL && (*tmp_x)->state == G && ((*tmp_x)->type == -1
			|| (*tmp_x)->type == '$'))
	{
		if ((*tmp_x)->type == '$' && (*tmp_x)->state == G && j == 1)
		{
			s = ft_expand((*tmp_x)->in, &my_env);
			ft_split_expand(arr_join, s);
		}
		else
		{
			ft_join_arr(arr_join, (*tmp_x)->in);
		}
		(*tmp_x) = (*tmp_x)->next;
	}
}

void	ft_join_double(char ***arr_join, t_splitor **tmp_x,
		t_environment *my_env, int j)
{
	char	*s;

	s = NULL;
	if ((*tmp_x) != NULL && ((*tmp_x)->state != S && (*tmp_x)->type == '$')
		&& j == 1)
	{
		if ((*tmp_x)->type == '$' && (*tmp_x)->state == G && j == 1)
		{
			s = ft_expand((*tmp_x)->in, &my_env);
			ft_split_expand(arr_join, s);
		}
		else if ((*tmp_x)->type == '$' && (*tmp_x)->state == D && j == 1)
		{
			s = ft_expand((*tmp_x)->in, &my_env);
			ft_join_arr(arr_join, s);
			free(s);
		}
		(*tmp_x) = (*tmp_x)->next;
	}
	ft_join_words(arr_join, tmp_x, my_env, 1);
	ft_join_next(arr_join, tmp_x, my_env, 1);
}

char	**ft_double_and_sigle(t_splitor **tmp_x, t_environment *my_env, int j,
		char ***arr_join)
{
	char	*s;

	s = NULL;
	while (((*tmp_x) != NULL) && !(redirection(*tmp_x) && (*tmp_x)->state == G)
		&& ((*tmp_x)->state == D || (*tmp_x)->state == S
			|| (*tmp_x)->type == '\"' || (*tmp_x)->type == '\''))
	{
		if ((*tmp_x) != NULL && ((*tmp_x)->state == D && (*tmp_x)->type == '$')
			&& j == 1)
		{
			s = ft_expand((*tmp_x)->in, &my_env);
			ft_split_expand(arr_join, s);
		}
		else if ((*tmp_x) != NULL && ((*tmp_x)->state == D
				|| (*tmp_x)->state == S))
			ft_join_arr(arr_join, (*tmp_x)->in);
		else if ((*tmp_x) != NULL && (((*tmp_x)->type == '$')
				|| (*tmp_x)->type == -1))
			ft_join_arr(arr_join, (*tmp_x)->in);
		(*tmp_x) = (*tmp_x)->next;
		ft_join_double(arr_join, tmp_x, my_env, j);
	}
	return (*arr_join);
}
