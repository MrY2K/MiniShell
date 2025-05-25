/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nodes_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-mora <rel-mora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 08:13:33 by rel-mora          #+#    #+#             */
/*   Updated: 2024/10/02 12:49:32 by rel-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_go_to_env(char **s, char *arg, int *i, t_environment **my_env)
{
	t_environment	*tmp_env;

	*s = NULL;
	tmp_env = *my_env;
	while (tmp_env != NULL)
	{
		if (ft_search(tmp_env->var, arg + (*i)))
		{
			*s = ft_strdup(tmp_env->data);
			break ;
		}
		else
			*s = NULL;
		tmp_env = tmp_env->next;
	}
}

char	*ft_expand(char *arg, t_environment **my_env)
{
	t_expand_her	id;

	id.i = 0;
	id.s = NULL;
	while (my_env != NULL && arg[id.i])
	{
		if (ft_search("$\"\"", arg))
			return (id.s = ft_strdup(""), id.s);
		else if (arg[id.i] == '$')
		{
			if (arg[id.i + 1] == '?')
				return (id.final = ft_itoa(g_exit_status),
					id.s = ft_strdup(id.final), free(id.final), id.s);
			id.i++;
			if (arg[id.i] == '\0')
				return (id.s = ft_strdup("$"), id.s);
			if (arg[id.i] == '\"' || arg[id.i] == '\'')
				return (id.s = ft_strdup(""), id.s);
			if (!ft_isalnum(arg[id.i]) || ft_isdigit(arg[id.i]))
				return (id.s);
			ft_go_to_env(&id.s, arg, &id.i, my_env);
		}
		id.i++;
	}
	return (id.s);
}

t_environment	*new_node(void *var, void *data)
{
	t_environment	*elem;

	elem = (t_environment *)malloc(sizeof(t_environment));
	if (!elem)
		return (NULL);
	elem->var = var;
	elem->data = data;
	elem->next = NULL;
	return (elem);
}

void	add_back_node(t_environment **lst, t_environment *new)
{
	t_environment	*p;

	if (!lst || !new)
		return ;
	p = *lst;
	if (!(*lst))
	{
		*lst = new;
		return ;
	}
	while (p->next)
	{
		p = p->next;
	}
	p->next = new;
}

t_environment	*ft_stock_envarment(char **env)
{
	t_environment	*var;
	int				i;
	int				j;

	var = NULL;
	i = 0;
	j = 0;
	while (env[i])
	{
		j = 0;
		while (env[i][j])
		{
			if (env[i][j] == '=')
			{
				add_back_node(&var, new_node(ft_substr(env[i], 0, j),
						ft_substr(env[i], j + 1, ft_strlen(env[i] + j))));
				break ;
			}
			j++;
		}
		i++;
	}
	return (var);
}
