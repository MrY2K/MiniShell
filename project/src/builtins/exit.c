/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajelloul <ajelloul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 08:33:49 by ajelloul          #+#    #+#             */
/*   Updated: 2025/06/13 12:15:45 by ajelloul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	count_argument(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

static bool	is_valid_numeric_arg(const char *str)
{
	int	i;

	if (!str || !str[0])
		return (false);
	i = 0;
	if (str[0] == '+' || str[0] == '-')
		i++;
	if (!str[i])
		return (false);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (false);
		i++;
	}
	return (true);
}

static bool	has_double_sign_prefix(char *arg)
{
	return ((arg[0] == '+' || arg[0] == '-')
		&& (arg[1] == '+' || arg[1] == '-'));
}

static bool	is_valid_exit_argument(t_minibash *bash, char **argument)
{
	if (!is_valid_numeric_arg(argument[0]))
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(argument[0], 2);
		ft_putendl_fd(": numeric argument required", 2);
		bash->exit_status = 255;
		return (false);
	}
	if (count_argument(argument) > 1)
	{
		ft_putendl_fd("minishell: exit: too many arguments", 2);
		bash->exit_status = 1;
		return (false);
	}
	return (true);
}

void	builtin_exit(t_minibash *bash, t_cmd *cmd)
{
	int	exit_status;

	ft_putendl_fd("exit", 2);
	if (!cmd->argument || !cmd->argument[0])
		exit(bash->exit_status);
	if (has_double_sign_prefix(cmd->argument[0]))
	{
		ft_putendl_fd("minishell: exit: numeric argument required", 2);
		bash->exit_status = 255;
		exit(255);
	}
	if (!is_valid_exit_argument(bash, cmd->argument))
	{
		if (bash->exit_status == 1)
			return ;
		exit(255);
	}
	exit_status = ft_atoi(cmd->argument[0]);
	exit((unsigned char)exit_status);
}
