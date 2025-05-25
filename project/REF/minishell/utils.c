/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-mora <rel-mora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 16:47:08 by rel-mora          #+#    #+#             */
/*   Updated: 2024/09/29 10:54:01 by rel-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_len_arg(char **arg)
{
	int	i;

	i = 0;
	if (arg == NULL || arg[0] == NULL)
		return (0);
	while (arg[i] != NULL)
	{
		i++;
	}
	return (i);
}

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
	return (free(s), ft_free_argment(expand_split), *arr_join);
}

char	**ft_join_arg(char **arg, char **join)
{
	t_ps	ps;

	ps.idx = 0;
	ps.j = 0;
	ps.len_of_arg = ft_len_arg(arg);
	ps.len_of_join = ft_len_arg(join);
	ps.new_arg = malloc(((ps.len_of_arg + ps.len_of_join) + 1)
			* sizeof(char *));
	ps.new_arg[0] = NULL;
	if (arg != NULL)
	{
		while (arg[ps.idx] != NULL)
		{
			ps.new_arg[ps.j] = ft_strdup(arg[ps.idx]);
			ps.j++;
			ps.idx++;
		}
	}
	ps.idx = 0;
	while (join[ps.idx])
		ps.new_arg[ps.j++] = ft_strdup(join[ps.idx++]);
	ps.new_arg[ps.j] = NULL;
	ft_free_argment(arg);
	return (ps.new_arg);
}

void	ft_join_arr(char ***arr_join, char *in)
{
	int		len_of_arr;
	char	*str;

	len_of_arr = ft_len_arg(*arr_join);
	if (in == NULL)
		return ;
	if (len_of_arr == 0)
	{
		*arr_join = NULL;
		*arr_join = malloc((1 + 1) * sizeof(char *));
		(*arr_join)[0] = ft_strdup(in);
		(*arr_join)[1] = NULL;
	}
	else
	{
		str = ft_strdup(in);
		len_of_arr--;
		(*arr_join)[len_of_arr] = ft_strjoin((*arr_join)[len_of_arr], str);
		free(str);
	}
}

void	ft_free_argment(char **arg)
{
	int	i;

	i = 0;
	if (arg == NULL)
		return ;
	while (arg[i] != NULL)
	{
		free(arg[i]);
		arg[i] = NULL;
		i++;
	}
	free(arg);
	arg = NULL;
}
