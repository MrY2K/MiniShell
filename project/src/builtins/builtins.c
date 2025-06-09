// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   builtins.c                                         :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: ajelloul <ajelloul@student.42.fr>          +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2025/05/20 06:57:14 by ajelloul          #+#    #+#             */
// /*   Updated: 2025/05/22 17:26:08 by ajelloul         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

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


void	execute_builtins(t_minibash *bash, t_env **env, t_cmd *cmd)
{
	if (!cmd || !cmd->main_cmd)
		return ;
	if (!ft_strcmp(cmd->main_cmd, "cd"))
		builtin_cd(bash, env, cmd);
	else if (!ft_strcmp(cmd->main_cmd, "unset"))
		builtin_unset(bash, cmd->argument);
	// else if (!ft_strcmp(cmd->main_cmd, "export"))
	// 	export(bash, cmd);
	else if (!ft_strcmp(cmd->main_cmd, "pwd"))
		builtin_pwd(bash, cmd);
	else if (!ft_strcmp(cmd->main_cmd, "env"))
		builtin_env(bash, env);
	else if (!ft_strcmp(cmd->main_cmd, "echo"))
		builtin_echo(bash, cmd);
	else if (!ft_strcmp(cmd->main_cmd, "exit"))
		builtin_exit(bash, cmd);
}
