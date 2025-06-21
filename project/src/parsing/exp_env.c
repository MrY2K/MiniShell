/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achoukri <achoukri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 02:00:29 by achoukri          #+#    #+#             */
/*   Updated: 2025/06/21 19:26:37 by achoukri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**ft_split_expand(char ***arr_join, char *s)
{
	char	**expand_split;

	expand_split = NULL;
	if (s != NULL)
	{
		expand_split = ft_split(s, ' ');
		if (ft_len_arg(expand_split) > 0)
		{
			if (s[0] == ' ')
				*arr_join = ft_join_arg(*arr_join, expand_split);
			else
			{
				ft_join_arr(arr_join, expand_split[0]);
				*arr_join = ft_join_arg(*arr_join, expand_split + 1);
			}
		}
	}
	else
	{
		if (s == NULL)
			return (*arr_join);
		else if (s[0] == '\0')
			return (ft_join_arr(arr_join, s), *arr_join);
	}
	return (free(s), free_argument_array(expand_split), *arr_join);
}

void	ft_go_to_env(char **s, char *arg, int *i, t_minibash **b)
{
	t_env	*tmp_env;

	if (!s || !arg || !i || !b || !(*b))
		return ;
	*s = NULL;
	tmp_env = (*b)->env;
	while (tmp_env != NULL)
	{
		if (ft_search(tmp_env->name, arg + (*i)))
		{
			*s = ft_strdup(tmp_env->value);
			break ;
		}
		else
			*s = NULL;
		tmp_env = tmp_env->next;
	}
}
