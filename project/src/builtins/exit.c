/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajelloul <ajelloul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 08:33:49 by ajelloul          #+#    #+#             */
/*   Updated: 2025/05/16 09:25:08 by ajelloul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
	1) - If no arguments, Exit with the last known exit code stored in 
	2) - exit ++5
	
*/

/*
	if (status < 0)
		status += 256;

	exit -1000
	ft_atoi("-1000") → status = -1000

	-1000 + 256 = -744

	exit(-744) → undefined behavior 😵
	❌ You can't pass negative numbers to exit().

*/

/*

 * The shell exit code is determined using only the least significant 8 bits 
 * of the integer passed to exit().
 * This is equivalent to performing a modulo 256 operation:
 *     exit_code = status % 256;
 * 
 * In C, casting an int to an unsigned char automatically applies 
 * this modulo behavior,
 * wrapping any integer (positive or negative) into the range [0, 255].
 *
 * This prevents overflow and ensures consistent behavior:
 *   - Positive values larger than 255 are wrapped:   300 % 256 = 44
 *   - Negative values are wrapped to valid exit codes: -1 % 256 = 255
 *
 * By casting the value with (unsigned char), we ensure that:
 *   exit((unsigned char)status);
 * always provides a valid exit code in the standard shell range.
 */

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

void	builtin_exit(t_cmd *cmd, t_minibash *bash)
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
