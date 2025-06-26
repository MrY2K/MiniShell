/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipelines.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajelloul <ajelloul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 09:34:01 by ajelloul          #+#    #+#             */
/*   Updated: 2025/06/22 13:00:39 by ajelloul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	write_in_pipes(t_pipe *pi_pe, int i)
{
	if (i > 0)
	{
		close(pi_pe->pipe_fds[i - 1][1]);
		dup2(pi_pe->pipe_fds[i - 1][0], 0);
		close(pi_pe->pipe_fds[i - 1][0]);
	}
	if (i < pi_pe->cmd_count - 1)
	{
		close (pi_pe->pipe_fds[i][0]);
		dup2(pi_pe->pipe_fds[i][1], 1);
		close(pi_pe->pipe_fds[i][1]);
	}
}

void	execute_child_process(t_pipe *pi_pe, int i,
	t_minibash *bash, t_env **env)
{
	write_in_pipes(pi_pe, i);
	pi_pe->arr_env = convert_env_list_to_array(env);
	if (has_redirections(pi_pe->current_cmd))
		handle_redirections(bash, pi_pe->current_cmd);
	if (is_builtins(pi_pe->current_cmd))
	{
		execute_builtins(bash, env, pi_pe->current_cmd);
		exit (0);
	}
	if (pi_pe->current_cmd->heredoc)
	{
		pi_pe->fd_heredoc = handle_heredoc_input(pi_pe->current_cmd);
		dup2(pi_pe->fd_heredoc, 0);
		close (pi_pe->fd_heredoc);
	}
	pi_pe->path = path_command(pi_pe->current_cmd->main_cmd,
			pi_pe->arr_env, bash);
	if (execve(pi_pe->path, pi_pe->current_cmd->argument, pi_pe->arr_env) == -1)
	{
		free_2d(pi_pe->arr_env);
		display_errno_exit("minishell: command not found", 127);
	}
}

void	execute_pipe_cmd(t_pipe *pi_pe, int i, t_minibash *bash, t_env **_env)
{
	t_env	**env;

	env = _env;
	if (pi_pe->current_cmd->pipe == 1)
		pi_pe->current_cmd = pi_pe->current_cmd->next;
	if (pipe(pi_pe->pipe_fds[i]) == -1)
	{
		exit_with_error("pipe", 1, bash);
		exit (1);
	}
	pi_pe->child_pids[i] = fork();
	if (pi_pe->child_pids[i] == -1)
	{
		exit_with_error("fork", 1, bash);
		exit (1);
	}
	if (!pi_pe->child_pids[i])
		execute_child_process(pi_pe, i, bash, env);
	if (i > 0)
	{
		close(pi_pe->pipe_fds[i - 1][0]);
		close(pi_pe->pipe_fds[i - 1][1]);
	}
	pi_pe->current_cmd = pi_pe->current_cmd->next;
}

	/*i = 0;
	while (i < pi_pe->cmd_count - 1) claud
	{
		if (pi_pe->pipe_fds[i])
		{
			close(pi_pe->pipe_fds[i][0]);
			close(pi_pe->pipe_fds[i][1]);
		}
		i++;
	}*/

void	wait_and_cleanup_pipes(t_minibash *bash, t_pipe *pi_pe)
{
	int	i;
	int	status;

	if (!pi_pe)
		return ;
	close(pi_pe->pipe_fds[pi_pe->cmd_count - 1][0]);
	close(pi_pe->pipe_fds[pi_pe->cmd_count - 1][1]);
	i = 0;
	while (i < pi_pe->cmd_count)
	{
		if (waitpid(pi_pe->child_pids[i], &status, 0) == -1)
		{
			bash->exit_status = status;
			exit (status);
		}
		else
		{
			if (WIFEXITED(status))
				bash->exit_status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				bash->exit_status = WTERMSIG(status) + 128;
		}
		i++;
	}
	cleanup_pipe_resources(pi_pe);
}
/*
	If a user presses Ctrl+C while writing a heredoc or in a pipe :
		It only kills the child process that is running the heredoc

		ex : cat << EOF  
			^C
	
*/

void	handle_pipes(t_minibash *bash, t_env **env, t_cmd *cmd)
{
	t_pipe	pi_pe;
	int		i;

	pi_pe.cmd_count = count_pipes(cmd) + 1;
	pi_pe.pipe_fds = allocate_pipe_fds(bash, pi_pe.cmd_count);
	pi_pe.current_cmd = cmd;
	pi_pe.child_pids = (pid_t *)malloc(sizeof(pid_t) * pi_pe.cmd_count);
	if (!pi_pe.child_pids)
	{
		perror ("malloc pipe");
		bash->exit_status = 1;
		cleanup_pipe_resources(&pi_pe);
		exit(1);
	}
	i = 0;
	while (i < pi_pe.cmd_count)
	{
		signal(SIGINT, here_pipe_signals);
		execute_pipe_cmd(&pi_pe, i, bash, env);
		i++;
	}
	wait_and_cleanup_pipes(bash, &pi_pe);
}
