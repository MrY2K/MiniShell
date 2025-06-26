/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipelines_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajelloul <ajelloul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 12:56:50 by ajelloul          #+#    #+#             */
/*   Updated: 2025/06/25 20:13:10 by ajelloul         ###   ########.fr       */
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

/**
 * Handles SIGQUIT (Ctrl+\) signal in child process
 * Prints "Quit: 3" and optionally ignores further SIGQUIT signals
*/

void	handle_sigquit(int signum)
{
	if (signum == SIGQUIT)
	{
		signal(SIGQUIT, SIG_IGN);
	}
}
/*	130	*/

void	here_pipe_signals(int sig_nal)
{
	(void) sig_nal;
	write(1, "\n", 1);
	exit(130);
}
