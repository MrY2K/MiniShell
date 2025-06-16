/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajelloul <ajelloul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 11:30:12 by ajelloul          #+#    #+#             */
/*   Updated: 2025/06/16 12:03:45 by ajelloul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	is_numeric_arg(char *arg)
{
	int	i;

	if (!arg || !*arg)
		return (0);
	i = 0;
	if (arg[0] == '+' || arg[0] == '-')
		i++;
	if (!arg[i])
		return (0);
	while (arg[i])
	{
		if (!ft_isdigit(arg[i]))
			return (0);
		i++;
	}
	return (1);
}

static int	count_arguments(char **args)
{
	int	count;

	if (!args)
		return (0);
	count = 0;
	while (args[count])
		count++;
	return (count);
}

void	exit_msg(char *arg, int exit_code)
{
	ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
	if (arg)
	{
		ft_putstr_fd(arg, STDERR_FILENO);
		ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
	}
	else
		ft_putstr_fd("too many arguments\n", STDERR_FILENO);
	exit(exit_code);
}

static void	handle_exit_cases(t_minibash *bash, t_cmd *cmd, int arg_count)
{
	int	exit_code;

	if (arg_count == 1)
		exit(bash->exit_status);
	else if (arg_count == 2)
	{
		if (!is_numeric_arg(cmd->argument[1]))
		{
			bash->exit_status = 255;
			exit_msg(cmd->argument[1], 255);
		}
		exit_code = ft_atoi(cmd->argument[1]);
		bash->exit_status = exit_code;
		exit(exit_code);
	}
	else
	{
		if (!is_numeric_arg(cmd->argument[1]))
		{
			bash->exit_status = 255;
			exit_msg(cmd->argument[1], 255);
		}
		bash->exit_status = 1;
		ft_putstr_fd("minishell: exit: too many arguments\n", STDERR_FILENO);
	}
}

void	builtin_exit(t_minibash *bash, t_cmd *cmd)
{
	int	arg_count;

	if (!bash || !cmd)
		return ;
	arg_count = count_arguments(cmd->argument);
	ft_putstr_fd("exit\n", STDOUT_FILENO);
	handle_exit_cases(bash, cmd, arg_count);
}
