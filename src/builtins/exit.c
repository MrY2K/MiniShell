/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajelloul <ajelloul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 11:30:12 by ajelloul          #+#    #+#             */
/*   Updated: 2025/06/17 11:46:40 by ajelloul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

static void	exit_msg(char *arg, int exit_code)
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

/*
	CASE 1 :
		exit -> It exits with the last command's exit status

	CASE 2 :
		exit <number>
	
	CASE 3 :
		exit abc  12 ->  numeric argument required
		exit 12 42  ->   too many arguments , no exit 

*/

/*
	exit(300); // Will actually return 44 → Because 300 % 256 = 44
*/

static void	handle_exit_cases(t_minibash *bash, t_cmd *cmd, int arg_count)
{
	long long	exit_code_ll;

	if (arg_count == 1)
		exit(bash->exit_status);
	else if (arg_count == 2)
	{
		if (!is_valid_exit_arg(cmd->argument[1]))
		{
			bash->exit_status = 255;
			exit_msg(cmd->argument[1], 255);
		}
		exit_code_ll = ft_atoll(cmd->argument[1]);
		bash->exit_status = (int)exit_code_ll;
		exit((unsigned char)exit_code_ll);
	}
	else
	{
		if (!is_valid_exit_arg(cmd->argument[1]))
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
