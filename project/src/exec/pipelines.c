/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipelines.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajelloul <ajelloul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 09:34:01 by ajelloul          #+#    #+#             */
/*   Updated: 2025/06/06 15:17:51 by ajelloul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../includes/minishell.h"

int	**allocate_pipe_fds(t_minibash *bash, int command_count)
{
	int	**pipe_fds;
	int	i;

	pipe_fds = (int **)malloc(sizeof(int *) * command_count);
	if (!pipe_fds)
	{
		perror("malloc pipe");
		bash->exit_status = 1;
		exit (1);
	}
	i = -1;
	while (++i < command_count)
	{
		pipe_fds[i] = (int *)malloc(sizeof(int) * 2);
		if (!pipe_fds[i])
		{
			perror("malloc pipe");
			while (i > 0)
			free(pipe_fds[i--]);
			free(pipe_fds);
        	bash->exit_status = 1;
        	exit(1);
		}
	}
	return (pipe_fds);
}

void	write_in_pipes(t_pipe *pi_pe, int i)
{
	if (i > 0) // Not the first command
	{
		close(pi_pe->pipe_fds[i - 1][1]); // Close write end of previous pipe
		dup2(pi_pe->pipe_fds[i - 1][0], 1);  // Redirect stdin to read from previous pipe
		close(pi_pe->pipe_fds[i - 1][0]);  // Close original read end
	}
	if (i < pi_pe->cmd_count - 1) // Not the last command
	{
		close (pi_pe->pipe_fds[i][0]); // Close read end of current pipe
		dup2(pi_pe->pipe_fds[i][1], 1); // Redirect stdout to write to current pipe
		close(pi_pe->pipe_fds[i][1]); // Close original write end
	}
}

void	execute_child_process(t_pipe *pi_pe, int i, t_minibash *bash, t_env **env)
{ // pipes_cmds

	write_in_pipes(pi_pe, i);
	pi_pe->arr_env = convert_env_list_to_array(env);
	if (has_redirections(pi_pe->current_cmd))
		handle_redirections(bash, pi_pe->current_cmd);
	if (is_builtins(pi_pe->current_cmd))
	{
		execute_builtins(bash, env, pi_pe->current_cmd);
		exit (0);
	}
	// ✅    ✅    ✅   herdoooc 
	if (pi_pe->current_cmd->heredoc)
	{
		pi_pe->fd_heredoc = handle_heredoc_input(pi_pe->current_cmd);
		dup2(pi_pe->fd_heredoc, 0);
		close (pi_pe->fd_heredoc);
	}
	pi_pe->path = command_path(bash, pi_pe->current_cmd);
	if (execve(pi_pe->path, pi_pe->current_cmd->argument, pi_pe->arr_env) == -1)
	{
		free_2d(pi_pe->arr_env);
		display_errno_exit("minishell: command not found", 127);
	}
}



// run pipe
void	execute_pipe_cmd(t_pipe *pi_pe, int i, t_minibash *bash, t_env **_env)
{
	t_env **env;

	env = _env;
	if (pi_pe->current_cmd->pipe == 1) // If current command has pipe move to next command in list
		pi_pe->current_cmd = pi_pe->current_cmd->next;
	if (pipe(pi_pe->pipe_fds[i]) == -1) // creat pipe
	{
		exit_with_error("pipe", 1, bash);
		exit (1);
	}
	pi_pe->child_pids[i] = fork(); // Creates child process
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


// // free_pid_pipe   // *************** 🆘 🆘   ********


void	cleanup_pipe_resources(t_pipe *pi_pe)
{
	int	i;

	if (!pi_pe)
		return ;
	if (pi_pe->pipe_fds)
	{
		i = 0;
		while (i < pi_pe->cmd_count)
		{
			if (pi_pe->pipe_fds[i])
			{
				free(pi_pe->pipe_fds[i]);
				pi_pe->pipe_fds[i] = NULL;
			}
			i++;
		}
		free(pi_pe->pipe_fds);
		pi_pe->pipe_fds = NULL;
	}
	if (pi_pe->child_pids)
	{
		free(pi_pe->child_pids);
		pi_pe->child_pids = NULL;
	}
}

// // close free andwait
void	wait_and_cleanup_pipes(t_minibash *bash, t_pipe *pi_pe)
{
	int	i;
	int	status;

	if (!pi_pe)
		return ;
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



void handle_pipes(t_minibash *bash, t_env **env, t_cmd *cmd)
{
	// handell pipelines
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
		cleanup_pipe_resources(&pi_pe); // claud
		exit(1);
	}
	i = 0;
	while (i < pi_pe.cmd_count)
	{
		// signal handell
		execute_pipe_cmd(&pi_pe, i, bash, env);
		i++;
	}
	wait_and_cleanup_pipes(bash, &pi_pe);
}
