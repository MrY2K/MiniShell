/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajelloul <ajelloul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 09:22:35 by ajelloul          #+#    #+#             */
/*   Updated: 2025/06/13 12:14:13 by ajelloul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static bool	is_n_option(char *str)
{
	int	i;

	if (!str || str[0] != '-')
		return (false);
	if (str[1] == '\0')
		return (false);
	i = 1;
	while (str[i])
	{
		if (str[i] != 'n')
			return (false);
		i++;
	}
	return (true);
}

static void	print_arguments(char **args, int start_idx)
{
	int	i;

	i = start_idx;
	while (args[i])
	{
		write(1, args[i], ft_strlen(args[i]));
		if (args[i + 1])
			write(1, " ", 1);
		i++;
	}
}

void	builtin_echo(t_minibash *bash, t_cmd *cmd)
{
	bool	no_newline;
	int		i;

	if (!cmd || !cmd->argument)
	{
		bash->exit_status = 0;
		return ;
	}
	no_newline = false;
	i = 0;
	while (cmd->argument[i] && is_n_option(cmd->argument[i]))
	{
		no_newline = true;
		i++;
	}
	print_arguments(cmd->argument, i);
	if (!no_newline)
		write(1, "\n", 1);
	bash->exit_status = 0;
}
