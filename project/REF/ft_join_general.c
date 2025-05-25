/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_join_general.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bouhammo <bouhammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 17:16:53 by rel-mora          #+#    #+#             */
/*   Updated: 2024/09/28 14:04:37 by bouhammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_join_double_2(char ***arr_join, t_splitor **tmp_x,
		t_environment *my_env, int j)
{
	char	*s;

	s = NULL;
	while ((*tmp_x) != NULL && ((*tmp_x)->state == D || (*tmp_x)->state == S))
	{
		if ((*tmp_x) != NULL && (*tmp_x)->state != S && (*tmp_x)->type == '$'
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
		}
		else if ((*tmp_x) != NULL)
			ft_join_arr(arr_join, (*tmp_x)->in);
		(*tmp_x) = (*tmp_x)->next;
	}
}

void	ft_join_word_2(char ***arr_join, t_splitor **tmp_x,
		t_environment *my_env, int j)
{
	char	*s;

	s = NULL;
	if ((*tmp_x) != NULL && (*tmp_x)->state != S && (*tmp_x)->type == '$'
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
	}
	else if ((*tmp_x) != NULL && ((*tmp_x)->state == G && (*tmp_x)->type == -1))
		ft_join_arr(arr_join, (*tmp_x)->in);
	else if ((*tmp_x) != NULL && ((*tmp_x)->state == D || (*tmp_x)->state == S))
		ft_join_arr(arr_join, (*tmp_x)->in);
	if ((*tmp_x) != NULL && (*tmp_x)->type != ' ' && !(redirection(*tmp_x)
			&& (*tmp_x)->state == G))
		(*tmp_x) = (*tmp_x)->next;
}

void	ft_join_words(char ***arr_join, t_splitor **tmp_x,
		t_environment *my_env, int j)
{
	while ((*tmp_x) != NULL && (*tmp_x)->state == G && ((*tmp_x)->type == '\"'
			|| (*tmp_x)->type == '\''))
	{
		if (((*tmp_x) != NULL && (*tmp_x)->state == G)
			&& ((*tmp_x)->type == '\"' || (*tmp_x)->type == '\''))
			(*tmp_x) = (*tmp_x)->next;
		ft_join_double_2(arr_join, tmp_x, my_env, j);
		ft_join_word_2(arr_join, tmp_x, my_env, j);
	}
}

char	**ft_word(t_splitor **tmp_x, t_environment *my_env, int j,
		char ***arr_join)
{
	char	*s;

	s = NULL;
	while ((*tmp_x) != NULL && ((*tmp_x)->state == G && (*tmp_x)->type != ' '
			&& (*tmp_x)->type != '|' && (!redirection(*tmp_x) && !quotes(*tmp_x)
				&& (*tmp_x)->state == G)))
	{
		if ((*tmp_x)->type == '$' && (*tmp_x)->state == G && j == 1)
		{
			s = ft_expand((*tmp_x)->in, &my_env);
			ft_split_expand(arr_join, s);
		}
		else if ((*tmp_x)->type == '$' && (*tmp_x)->state == D && j == 1)
		{
			s = ft_expand((*tmp_x)->in, &my_env);
			ft_split_expand(arr_join, s);
		}
		else
			ft_join_arr(arr_join, (*tmp_x)->in);
		(*tmp_x) = (*tmp_x)->next;
		ft_join_words(arr_join, tmp_x, my_env, j);
	}
	return (*arr_join);
}
