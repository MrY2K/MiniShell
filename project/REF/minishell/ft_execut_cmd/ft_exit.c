/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bouhammo <bouhammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 23:39:14 by rel-mora          #+#    #+#             */
/*   Updated: 2024/10/05 19:10:12 by bouhammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_number(char *arg)
{
	int	i;

	i = 0;
	if (arg[0] == '+' || arg[0] == '-')
	{
		i++;
		while (arg[i])
		{
			if (!ft_isdigit(arg[i]))
				return (0);
			i++;
		}
	}
	else
	{
		while (arg[i])
		{
			if (!ft_isdigit(arg[i]))
				return (0);
			i++;
		}
	}
	return (1);
}

void	ft_free_when_exit(t_environment **var, char *str, int fd,
		t_command *cmd)
{
	(void)cmd;
	ft_putstr_fd(str, fd);
	ft_free_command(&cmd);
	ft_free_env(var);
}

void	ft_exit_comp(int len, char **ptr)
{
	if (len == 2 && is_number(ptr[1]) && ptr[0][0] == '-')
	{
		g_exit_status = 255;
		exit(255);
	}
	else if (ptr[1] && !is_number(ptr[1]))
	{
		g_exit_status = 255;
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(ptr[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		exit(255);
	}
	else if (len > 2 && ptr[1] && ptr[2] && !is_number(ptr[1])
		&& !is_number(ptr[2]))
	{
		g_exit_status = 255;
		ft_putstr_fd("minishell: exit: numeric argument required\n", 2);
		exit(255);
	}
	else if (len > 2)
	{
		g_exit_status = 1;
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
	}
}

void	ft_exit(t_environment **var, t_command *cmd)
{
	int	len;

	(void)var;
	len = ft_len_arg(cmd->arg);
	if (len == 1)
		exit(g_exit_status);
	else if (len == 2 && is_number(cmd->arg[1]) && (cmd->arg[1][0] != '+'
		|| cmd->arg[1][0] != '+'))
	{
		g_exit_status = ft_atoi(cmd->arg[1]);
		exit(ft_atoi(cmd->arg[1]));
	}
	else if (len == 2 && is_number(cmd->arg[1]) && cmd->arg[1][0] == '+')
	{
		g_exit_status = ft_atoi(cmd->arg[1]);
		exit(ft_atoi(cmd->arg[1]));
	}
	else
		ft_exit_comp(len, cmd->arg);
}
