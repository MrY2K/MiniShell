/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd_4.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achoukri <achoukri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 02:13:56 by achoukri          #+#    #+#             */
/*   Updated: 2025/06/21 02:30:54 by achoukri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_join_next(char ***arr_join, t_token **tmp_x, t_env *env,
		int j)
{
	char	*s;

	s = NULL;
	while ((*tmp_x) != NULL && (*tmp_x)->state == N && ((*tmp_x)->type == -1
			|| (*tmp_x)->type == '$'))
	{
		if ((*tmp_x)->type == '$' && (*tmp_x)->state == N && j == 1)
		{
			s = ft_expand((*tmp_x)->value, &env);
			ft_split_expand(arr_join, s);
		}
		else
		{
			ft_join_arr(arr_join, (*tmp_x)->value);
		}
		(*tmp_x) = (*tmp_x)->next;
	}
}

void	ft_join_double(char ***arr_join, t_token **tmp_t,
		t_env *env, int j)
{
	char	*s;

	s = NULL;
	if ((*tmp_t) != NULL && ((*tmp_t)->state != S && (*tmp_t)->type == '$')
		&& j == 1)
	{
		if ((*tmp_t)->type == '$' && (*tmp_t)->state == N && j == 1)
		{
			s = ft_expand((*tmp_t)->value, &env);
			ft_split_expand(arr_join, s);
		}
		else if ((*tmp_t)->type == '$' && (*tmp_t)->state == D && j == 1)
		{
			s = ft_expand((*tmp_t)->value, &env);
			ft_join_arr(arr_join, s);
			free(s);
		}
		(*tmp_t) = (*tmp_t)->next;
	}
	ft_join_words(arr_join, tmp_t, env, 1);
	ft_join_next(arr_join, tmp_t, env, 1);
}

char	**process_quoted(t_token **tok_ptr, t_env *env, int flag,
					char ***arg_arr)
{
	char	*s;

	s = NULL;
	while ((*tok_ptr) != NULL
		&& !is_redirection(*tok_ptr)
		&& ((*tok_ptr)->state == D || (*tok_ptr)->state == S
			|| (*tok_ptr)->type == '"' || (*tok_ptr)->type == '\''))
	{
		if ((*tok_ptr)->state == D && (*tok_ptr)->type == '$' && flag)
		{
			s = ft_expand((*tok_ptr)->value, &env);
			ft_split_expand(arg_arr, s);
		}
		else if ((*tok_ptr)->state == D || (*tok_ptr)->state == S)
		{
			ft_join_arr(arg_arr, (*tok_ptr)->value);
		}
		else if ((*tok_ptr)->type == '$' || (*tok_ptr)->type == -1)
		{
			ft_join_arr(arg_arr, (*tok_ptr)->value);
		}
		*tok_ptr = (*tok_ptr)->next;
		ft_join_double(arg_arr, tok_ptr, env, flag);
	}
	return (*arg_arr);
}
