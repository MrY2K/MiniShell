/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajelloul <ajelloul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 10:10:28 by ajelloul          #+#    #+#             */
/*   Updated: 2025/06/17 10:10:31 by ajelloul         ###   ########.fr       */
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

void	execute_builtins(t_minibash *bash, t_env **env, t_cmd *cmd)
{
	if (!cmd || !cmd->main_cmd)
		return ;
	if (!ft_strcmp(cmd->main_cmd, "cd"))
		builtin_cd(bash, env, cmd);
	else if (!ft_strcmp(cmd->main_cmd, "unset"))
		builtin_unset(bash, cmd->argument);
	else if (!ft_strcmp(cmd->main_cmd, "export"))
		builtin_export(bash, env, cmd);
	else if (!ft_strcmp(cmd->main_cmd, "pwd"))
		builtin_pwd(bash, cmd);
	else if (!ft_strcmp(cmd->main_cmd, "env"))
		builtin_env(bash, env);
	else if (!ft_strcmp(cmd->main_cmd, "echo"))
		builtin_echo(bash, cmd);
	else if (!ft_strcmp(cmd->main_cmd, "exit"))
		builtin_exit(bash, cmd);
}

void	execute_parent_builtin(t_minibash *bash, t_env **env, t_cmd *cmd)
{
	if (has_redirections(cmd))
		if (validate_redirection_file(cmd))
			return ;
	if (cmd->argument[1])
		execute_builtins(bash, env, cmd);
	if (!ft_strcmp(cmd->main_cmd, "exit") && !cmd->argument[1])
		execute_builtins(bash, env, cmd);
	if (!ft_strcmp(cmd->main_cmd, "cd") && !cmd->argument[1])
		execute_builtins(bash, env, cmd);
}

bool	is_parent_builtins(t_cmd *cmd)
{
	t_cmd	*tmp;

	tmp = cmd;
	if (ft_strcmp(tmp->main_cmd, "export") == 0 && tmp->argument[1])
		return (true);
	if (ft_strcmp(tmp->main_cmd, "unset") == 0 && tmp->argument[1])
		return (true);
	if (ft_strcmp(tmp->main_cmd, "cd") == 0)
		return (true);
	if (ft_strcmp(tmp->main_cmd, "exit") == 0)
		return (true);
	return (false);
}
