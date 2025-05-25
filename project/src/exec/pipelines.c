/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipelines.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajelloul <ajelloul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 09:34:01 by ajelloul          #+#    #+#             */
/*   Updated: 2025/05/24 12:48:08 by ajelloul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../includes/minishell.h"

int	****allocate_pipe_fds(t_minibash *bash, int command_count)
{
	int	**pipe_fds;
	int	i;

	int **pipe_fds = (int **)malloc(sizeof(int *) * command_count);
	if (!pipe_fds)
	{
		perror("malloc:");
		bash->exit_status = 1;
		exit (1);
	}
	i = -1;
	while (++i < command_count)
	{
		pipe_fds[i] = (int *)malloc(sizeof(int) * 2);
		if (!pipe_fds[i])
		{
			perror("malloc:");
			while (i > 0)
			free(pipe_fds[i--]);
			free(pipe_fds);
        	bash->exit_status = 1;
        	exit(1);
		}
	}
	return (pipe_fds);
}

void	setup_pipe_connections(t_pipe pi_pe, int i)
{ // write_in_pipe
	if (i > 0)
	{
		close(pi_pe.pipe_fds[i - 1][1]);
		dup2(pi_pe.pipe_fds[i - 1][0], 1);
		close(pi_pe.pipe_fds[i - 1][0]);
	}
	if (i < pi_pe.cmd_count - 1)
	{
		close (pi_pe.pipe_fds[i][0]);
		dup2(pi_pe.pipe_fds[i][1], 1);
		close(pi_pe.pipe_fds[i][1]);
	}
}

void	execute_child_process(t_pipe *pi_pe, int i, t_minibash *bash)
{ // pipes_cmds

	if (pi_pe->child_pids[i] == 0)
	{
		setup_pipe_connections(pi_pe, i);
		if (is_builtins(pi_pe->current_cmd))
		{
			execute_builtin(bash, pi_pe->current_cmd);
			exit(0);
		}
		// handelle herdoc
		pi_pe->path = command_path(bash, pi_pe->current_cmd);
		if (execve(pi_pe->path, pi_pe->current_cmd->argument, bash->env) == -1)
		{
			free_env(bash->env);
			display_errno_exit("minishell: command not found", 127);
		}
	}
}
 // run pipe
void	execute_pipe_cmd(t_pipe *pi_pe, int i, t_minibash *bash)
{
	t_env **env;

	env = bash->env;
	if (!pi_pe || !env || i < 0)
		return (bash->exit_status = 1, );
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
	execute_child_process(pi_pe, i, bash);
	if (i > 0)
	{
		close(pi_pe->pipe_fds[i - 1][0]);
		close(pi_pe->pipe_fds[i - 1][1]);
	}
	pi_pe->current_cmd = pi_pe->current_cmd->next;
}
// free_pid_pipe   // *************** 🆘 🆘   ********
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
			free (pi_pe->pipe_fds[i]);
			pi_pe->pipe_fds[i] = NULL;
			i++;
		}
		free (pi_pe->pipe_fds);
		pi_pe->pipe_fds = NULL;
	}
	if (pi_pe->child_pids)
	{
		free (pi_pe->child_pids);
		pi_pe->child_pids = NULL;
	}
}

// close free andwait
void	wait_and_cleanup_pipes(t_minibash *bash, t_pipe *pi_pe)
{
	int	i;
	int	status;
	if (!pi_pe)
		return ;
	close([pi_pe->pipe_fds[pi_pe->cmd_count - 1][0]]);
	close([pi_pe->pipe_fds[pi_pe->cmd_count - 1][1]]);
	j = -1;
	while (++j < pi_pe->cmd_count)
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
	}
	
}



void execute_pipe_chain(t_minibash *bash, t_cmd *cmd)
{
	// handell pipelines
	t_pipe	pi_pe;
	int		i;

	pi_pe.cmd_count = count_pipes(cmd) + 1;
	pi_pe.pipe_fd = allocate_pipe_fds(pi_pe.cmd_count);
	pi_pe.current_cmd = cmd;
	pi_pe.child_pids = (pid_t *)malloc(sizeof(pid_t) * pi_pe.cmd_count);
	if (pi_pe.child_pids)
	{
		perror ("malloc");
		bash->exit_status = 1;
		exit(1);
	}
	i = -1;
	if (++i < pi_pe.cmd_count)
	{
		// signal handell
		execute_pipe_cmd(&pi_pe, i, bash);
	}
	wait_and_cleanup_pipes(bash, &pi_pe);
}
