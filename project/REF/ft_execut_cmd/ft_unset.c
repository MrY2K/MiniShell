/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bouhammo <bouhammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 19:06:34 by bouhammo          #+#    #+#             */
/*   Updated: 2024/10/07 13:09:22 by bouhammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_environment	*delet_first_node(t_environment **my_env)
{
	t_environment	*start;
	t_environment	*end;

	start = *my_env;
	end = (*my_env)->next;
	free(start->data);
	start->data = NULL;
	free(start->var);
	start->var = NULL;
	free(start);
	*my_env = end;
	return (end);
}

int	check_is_valid(char *str)
{
	int	i;

	if (str == NULL)
		return (0);
	if (ft_isdigit(str[0]) || str[0] == '\0')
	{
		ft_error(str, "minishell :");
		return (1);
	}
	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || (str[i] >= ':' && str[i] <= '@') || (str[i] >= '['
				&& str[i] <= '^') || str[i] >= '{' || str[i] == '`')
		{
			ft_error(str, "minishell :");
			return (1);
		}
		i++;
	}
	return (0);
}

void	delet_first(t_environment **var, char *ptr)
{
	t_environment	*env;

	if (var == NULL || *var == NULL || ptr == NULL)
		return ;
	env = (*var);
	if (ft_strcmp(env->var, ptr) == 0)
	{
		*var = delet_first_node(var);
	}
}

void	delet_environment(t_environment **var, char *str)
{
	t_environment	*env;
	t_environment	*env_1;
	t_environment	*prev;

	env = *var;
	prev = NULL;
	while (env)
	{
		if (ft_strcmp(env->var, str) == 0)
		{
			if (prev)
				prev->next = env->next;
			else
				*var = env->next;
			env_1 = env;
			env = env->next;
			free(env_1->var);
			free(env_1->data);
			free(env_1);
			return ;
		}
		prev = env;
		if (env)
			env = env->next;
	}
}

void	ft_unset(t_environment **var, t_command *list)
{
	int		i;
	char	*ptr;

	if (!var || !*var || !list)
		return ;
	i = 1;
	ptr = (*var)->var;
	g_exit_status = 0;
	while (list->arg[i])
	{
		if (check_is_valid(list->arg[i]) == 1)
			i++;
		else
		{
			if (ft_strncmp(ptr, list->arg[1], ft_strlen(ptr)) == 0)
				delet_first(var, ptr);
			delet_environment(var, list->arg[i]);
			i++;
		}
	}
}
