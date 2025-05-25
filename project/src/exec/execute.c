/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajelloul <ajelloul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 16:29:21 by ajelloul          #+#    #+#             */
/*   Updated: 2025/05/24 09:36:52 by ajelloul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


static void	execute_external_cmd(t_minibash *bash, t_cmd *cmd, char **args)
{
	char	*path;

	if (!cmd || !args || !args[0])
	{
		bash->exit_status = 127;
		exit(127);
	}
	path = command_path(bash, cmd);
	if (!path)
		exit(bash->exit_status);
	if (execve(path, args, bash->env) == -1)
	{
		perror("minishell");
		free(path);
		bash->exit_status = 126;
		exit(126);
	}
}

static void	execute_single_cmd(t_minibash *bash, t_cmd *cmd)
{
	if (!cmd)
	{
		bash->exit_status = 127;
		exit(127);
	}
	if (is_builtins(cmd))
		execute_builtin(bash, cmd);
	else
		execute_external_cmd(bash, cmd, cmd->argument);
}

static void	run_command(t_minibash *bash, t_cmd *cmd)
{
	// handel pipe and pipe
	
	if (has_pipes(cmd))
	{
		execute_pipe_chain (bash, cmd);
	}

	execute_single_cmd(bash, cmd);
}

static void	wait_for_child(t_minibash *bash, int pid)
{
	int	status;

	if (waitpid(pid, &status, 0) == -1)
	{
		perror("minishell");
		bash->exit_status = 1;
		return ;
	}
	if (WIFEXITED(status))
		bash->exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		bash->exit_status = 128 + WTERMSIG(status);
}

void	execution(t_minibash *bash, t_cmd *cmd)
{
	int	pid;

	if (!bash || !cmd)
		return ;
	if (is_builtins(cmd))
	{
		execute_builtin(bash, cmd);
		return ;
	}
	pid = fork();
	if (!is_fork_success(bash, pid))
		return ;
	if (pid == 0)
	{
		run_command(bash, cmd);
		exit(bash->exit_status);
	}
	else
		wait_for_child(bash, pid);
}
