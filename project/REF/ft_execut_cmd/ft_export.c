/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bouhammo <bouhammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 19:19:52 by bouhammo          #+#    #+#             */
/*   Updated: 2024/10/05 19:11:15 by bouhammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**split_line(char *ptr)
{
	char	**arg;

	arg = (char **)malloc(sizeof(char *) * 3);
	if (arg == NULL)
		return (NULL);
	if (ft_str_eqal(ptr, '=') == 1)
	{
		arg[0] = first_word(ptr);
		arg[1] = ft_strdup(ft_strchr(ptr, '=') + 1);
	}
	else
	{
		arg[0] = ft_strdup(ptr);
		arg[1] = NULL;
	}
	arg[2] = NULL;
	return (arg);
}

int	check_is_valid_1(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '=')
	{
		ft_error(str, "minishell:");
		return (1);
	}
	if (ft_isdigit(str[0]) || str[i] == '\0')
	{
		ft_error(str, "minishell:");
		return (1);
	}
	while (str[i] && str[i] != '=')
	{
		if (str[i] < '0' || (str[i] >= ':' && str[i] <= '@') || (str[i] >= '['
				&& str[i] <= '^') || str[i] >= '{' || str[i] == '`')
		{
			ft_error(str, "minishell:");
			return (1);
		}
		i++;
	}
	return (0);
}

void	export_1(t_environment **var, t_command *str, int *i)
{
	char			*ptr_1;
	char			*ptr_2;
	t_environment	*elem;
	char			**list;

	ptr_2 = NULL;
	list = split_line(str->arg[*i]);
	if (test_exist(var, list) == 0)
	{
		(*i)++;
	}
	else if (test_exist(var, list) == 1)
	{
		ptr_1 = ft_strdup(list[0]);
		if (list[1] != NULL)
			ptr_2 = ft_strdup(list[1]);
		elem = new_node(ptr_1, ptr_2);
		add_back_node(var, elem);
		(*i)++;
	}
	free_args(list);
	return ;
}

int	ft_check_var(t_environment **var, t_command *str)
{
	t_check_var	check;

	check.ptr_2 = NULL;
	if (*var == NULL)
	{
		if (str->arg[1] == NULL)
			return (1);
		if (str->arg[1] != NULL && str->arg[1][0] == '\0')
		{
			ft_error(str->arg[1], "minishell:");
			return (1);
		}
		if (check_is_valid_1(str->arg[1]) == 1)
			return (1);
		check.list = split_line(str->arg[1]);
		check.ptr_1 = ft_strdup(check.list[0]);
		if (check.list[1] != NULL)
			check.ptr_2 = ft_strdup(check.list[1]);
		check.elem = new_node(check.ptr_1, check.ptr_2);
		add_back_node(var, check.elem);
		free_args(check.list);
	}
	return (0);
}

void	ft_export(t_environment **var, t_command *str)
{
	int	i;

	i = 1;
	g_exit_status = 0;
	if (ft_check_var(var, str) == 1)
		return ;
	while (str->arg[i] != NULL)
	{
		if (check_is_valid_1(str->arg[i]) == 1)
		{
			i++;
		}
		else
			export_1(var, str, &i);
	}
	affiche_export(str->arg, var);
}
