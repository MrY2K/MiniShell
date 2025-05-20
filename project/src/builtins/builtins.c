/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajelloul <ajelloul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 06:57:14 by ajelloul          #+#    #+#             */
/*   Updated: 2025/05/20 16:14:32 by ajelloul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static bool	is_exist(t_cmd *cmd)
{
	return (cmd && cmd->argument && cmd->argument[0]
		&& (!ft_strcmp(cmd->argument[0], "cd")
			|| !ft_strcmp(cmd->argument[0], "pwd")
			|| !ft_strcmp(cmd->argument[0], "export")
			|| !ft_strcmp(cmd->argument[0], "env")
			|| !ft_strcmp(cmd->argument[0], "echo")
			|| !ft_strcmp(cmd->argument[0], "exit")
			|| !ft_strcmp(cmd->argument[0], "unset")));
}

static void	execute_builtins(t_minibash *bash, t_cmd *cmd)
{
	if (!cmd || !cmd->argument || !cmd->argument[0])
		return ;
	if (!ft_strcmp(cmd->argument[0], "cd"))
		cd(cmd, bash);
	else if (!ft_strcmp(cmd->argument[0], "unset"))
		unset(bash, cmd->argument);
	else if (!ft_strcmp(cmd->argument[0], "export"))
		export(bash, cmd);
	else if (!ft_strcmp(cmd->argument[0], "pwd"))
		pwd(bash);
	else if (!ft_strcmp(cmd->argument[0], "env"))
		env(bash);
	else if (!ft_strcmp(cmd->argument[0], "echo"))
		echo(cmd);
	else if (!ft_strcmp(cmd->argument[0], "exit"))
		builtin_exit(bash, cmd);
}

void	builtins(t_cmd *cmd, t_minibash *bash)
{
	if (is_exist(cmd))
		execute_builtins(bash, cmd);
}
