/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajelloul <ajelloul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 16:29:21 by ajelloul          #+#    #+#             */
/*   Updated: 2025/06/12 12:38:43 by ajelloul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* Case 1: Handle heredoc operations
	1.1
		echo hej << 42  :  print hej

	Case 3 :
		cd > file.txt -> change cur dir + create file
*/

int	process_herdoc_builtins(t_minibash *bash, t_env **env, t_cmd *cmd)
{
	t_cmd	*tmp_cmd;

	tmp_cmd = cmd;
	if (!cmd)
		return (0);
	if (has_herdoc(tmp_cmd))
	{
		if (handle_heredocs(bash, env, tmp_cmd))
			return (-1);
		if (is_builtins(tmp_cmd) && !has_redirections(tmp_cmd)
			&& !has_pipes(tmp_cmd))
		{
			execute_builtins(bash, env, tmp_cmd);
			return (1);
		}
	}
	if (is_builtins(tmp_cmd) && !has_redirections(tmp_cmd)
		&& !has_pipes(tmp_cmd) && !has_herdoc(tmp_cmd))
	{
		execute_builtins(bash, env, tmp_cmd);
		return (1);
	}
	else if (is_parent_builtins(tmp_cmd) && !has_pipes(tmp_cmd))
		execute_parent_builtin(bash, env, tmp_cmd);
	return (0);
}

void	delete_heredoc_files(t_minibash *bash, t_cmd *cmd)
{
	t_heredoc_cleanup	cleanup;

	cleanup.current_cmd = cmd;
	while (cleanup.current_cmd)
	{
		cleanup.current_heredoc = cleanup.current_cmd->heredoc;
		while (cleanup.current_heredoc)
		{
			cleanup.index_str = ft_itoa(cleanup.current_heredoc->index);
			cleanup.temp_path = ft_strjoin_with_null(
					cleanup.current_heredoc->delimiter, cleanup.index_str);
			cleanup.full_filepath = ft_strjoin(
					"/tmp/minishell/heredoc", cleanup.temp_path);
			if (unlink(cleanup.full_filepath) != 0)
			{
				bash->exit_status = 1;
				perror("Failed to delete heredoc file");
			}
			free(cleanup.index_str);
			free(cleanup.temp_path);
			free(cleanup.full_filepath);
			cleanup.current_heredoc = cleanup.current_heredoc->next;
		}
		cleanup.current_cmd = cleanup.current_cmd->next;
	}
}

/* Case 1: SIGINT (Ctrl+C) during heredoc */
/* Case 2: Builtin executed successfully */
/* Case 3: Continue to pipe/fork execution */

int	execute_builtins_or_herdoc(t_minibash *bash, t_cmd *cmd)
{
	int		her_status;
	t_env	**env;

	env = &bash->env;
	her_status = process_herdoc_builtins(bash, env, cmd);
	if (her_status == -1)
	{
		delete_heredoc_files(bash, cmd);
		bash->exit_status = 1;
		return (1);
	}
	if (her_status == 1)
	{
		delete_heredoc_files(bash, cmd);
		return (1);
	}
	return (0);
}

static void	wait_for_child(t_minibash *bash, int pid)
{
	int	status;

	if (waitpid(pid, &status, 0) == -1)
	{
		perror("minishell waitpid");
		bash->exit_status = 1;
		return ;
	}
	if (WIFEXITED(status))
		bash->exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		bash->exit_status = 128 + WTERMSIG(status);
}

void	execution(t_minibash *bash, t_env **env, t_cmd *cmd)
{
	t_cmd	*tmp_cmd;
	int		pid;

	tmp_cmd = cmd;
	if (execute_builtins_or_herdoc(bash, tmp_cmd))
		return ;
	pid = fork();
	if (!is_fork_succes(bash, pid))
		return ;
	if (!pid)
		execute_command(bash, env, cmd);
	else
		wait_for_child(bash, pid);
	delete_heredoc_files(bash, cmd);
}
