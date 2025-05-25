/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajelloul <ajelloul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 06:57:14 by ajelloul          #+#    #+#             */
/*   Updated: 2025/05/22 17:26:08 by ajelloul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	is_builtins(t_cmd *cmd)
{
	if (!cmd || !cmd->main_cmd)
		return (false);
	return (!ft_strcmp(cmd->main_cmd, "cd")
		|| !ft_strcmp(cmd->main_cmd, "pwd")
		|| !ft_strcmp(cmd->main_cmd, "export")
		|| !ft_strcmp(cmd->main_cmd, "env")
		|| !ft_strcmp(cmd->main_cmd, "echo")
		|| !ft_strcmp(cmd->main_cmd, "exit")
		|| !ft_strcmp(cmd->main_cmd, "unset"));
}


static void	execute_builtins(t_minibash *bash, t_cmd *cmd)
{
	if (!cmd || !cmd->main_cmd)
		return ;
	if (!ft_strcmp(cmd->main_cmd, "cd"))
		cd(cmd, bash);
	else if (!ft_strcmp(cmd->main_cmd, "unset"))
		unset(bash, cmd->argument);
	else if (!ft_strcmp(cmd->main_cmd, "export"))
		export(bash, cmd);
	else if (!ft_strcmp(cmd->main_cmd, "pwd"))
		pwd(bash);
	else if (!ft_strcmp(cmd->main_cmd, "env"))
		env(bash);
	else if (!ft_strcmp(cmd->main_cmd, "echo"))
		echo(cmd);
	else if (!ft_strcmp(cmd->main_cmd, "exit"))
		builtin_exit(bash, cmd);
}

void	execute_builtin(t_minibash *bash, t_cmd *cmd)
{
	if (!cmd || !bash)
		return ;
	if (is_builtins(cmd))
		execute_builtins(bash, cmd);
}
