/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   j.c                                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achoukri <achoukri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 02:07:58 by achoukri          #+#    #+#             */
/*   Updated: 2025/06/21 02:55:13 by achoukri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**ft_join_arg(char **arg, char **join)
{
	t_ps	ps;

	ps.idx = 0;
	ps.j = 0;
	ps.arg_len = ft_len_arg(arg);
	ps.join_len = ft_len_arg(join);
	ps.new_args = malloc(((ps.arg_len + ps.join_len) + 1)
			* sizeof(char *));
	ps.new_args[0] = NULL;
	if (arg != NULL)
	{
		while (arg[ps.idx] != NULL)
		{
			ps.new_args[ps.j] = ft_strdup(arg[ps.idx]);
			ps.j++;
			ps.idx++;
		}
	}
	ps.idx = 0;
	while (join[ps.idx])
		ps.new_args[ps.j++] = ft_strdup(join[ps.idx++]);
	ps.new_args[ps.j] = NULL;
	free_argument_array(arg);
	return (ps.new_args);
}

void	ft_join_arr(char ***arr_join, char *value)
{
	int		len_of_arr;
	char	*str;

	len_of_arr = ft_len_arg(*arr_join);
	if (value == NULL)
		return ;
	if (len_of_arr == 0)
	{
		*arr_join = NULL;
		*arr_join = malloc((1 + 1) * sizeof(char *));
		(*arr_join)[0] = ft_strdup(value);
		(*arr_join)[1] = NULL;
	}
	else
	{
		str = ft_strdup(value);
		len_of_arr--;
		(*arr_join)[len_of_arr] = ft_strjoin((*arr_join)[len_of_arr], str);
		free(str);
	}
}

void	ft_join_double_2(char ***arr_join, t_token **tmp_t,
		t_minibash *env, int j)
{
	char	*s;

	s = NULL;
	while ((*tmp_t) != NULL && ((*tmp_t)->state == D || (*tmp_t)->state == S))
	{
		if ((*tmp_t) != NULL && (*tmp_t)->state != S
			&& (*tmp_t)->type == '$' && j == 1)
		{
			if ((*tmp_t)->type == '$' && (*tmp_t)->state == N && j == 1)
			{
				s = ft_expand((*tmp_t)->value, env);
				ft_split_expand(arr_join, s);
			}
			else if ((*tmp_t)->type == '$' && (*tmp_t)->state == D && j == 1)
			{
				s = ft_expand((*tmp_t)->value, env);
				ft_join_arr(arr_join, s);
				free(s);
			}
		}
		else if ((*tmp_t) != NULL)
			ft_join_arr(arr_join, (*tmp_t)->value);
		(*tmp_t) = (*tmp_t)->next;
	}
}

void	ft_join_word_2(char ***arr_join, t_token **tmp_t,
		t_minibash *env, int j)
{
	char	*s;

	s = NULL;
	if ((*tmp_t) != NULL && (*tmp_t)->state != S && (*tmp_t)->type == '$'
		&& j == 1)
	{
		if ((*tmp_t)->type == '$' && (*tmp_t)->state == N && j == 1)
		{
			s = ft_expand((*tmp_t)->value, env);
			ft_split_expand(arr_join, s);
		}
		else if ((*tmp_t)->type == '$' && (*tmp_t)->state == D && j == 1)
		{
			s = ft_expand((*tmp_t)->value, env);
			ft_join_arr(arr_join, s);
			free(s);
		}
	}
	else if ((*tmp_t) != NULL && ((*tmp_t)->state == N && (*tmp_t)->type == -1))
		ft_join_arr(arr_join, (*tmp_t)->value);
	else if ((*tmp_t) != NULL && ((*tmp_t)->state == D || (*tmp_t)->state == S))
		ft_join_arr(arr_join, (*tmp_t)->value);
	if ((*tmp_t) != NULL && (*tmp_t)->type != ' ' && !(redirection(*tmp_t)
			&& (*tmp_t)->state == N))
		(*tmp_t) = (*tmp_t)->next;
}

void	ft_join_words(char ***arr_join, t_token **tmp_t,
		t_minibash *b, int j)
{
	while ((*tmp_t) != NULL && (*tmp_t)->state == N && ((*tmp_t)->type == '\"'
			|| (*tmp_t)->type == '\''))
	{
		if (((*tmp_t) != NULL && (*tmp_t)->state == N)
			&& ((*tmp_t)->type == '\"' || (*tmp_t)->type == '\''))
			(*tmp_t) = (*tmp_t)->next;
		ft_join_double_2(arr_join, tmp_t, b, j);
		ft_join_word_2(arr_join, tmp_t, b, j);
	}
}
