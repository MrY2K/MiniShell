/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 12:01:42 by ajelloul          #+#    #+#             */
/*   Updated: 2025/06/25 11:03:12 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
	signal(SIGINT, SIG_DFL) :
		If user presses Ctrl+C  we should stop heredoc and return to the shell
			 not exit the entire shell

	signal(SIGQUIT, SIG_IGN) :
		If user presses Ctrl+\ it should be ignored like in bash
*/

void	child_process(t_minibash *bash, t_env **env, t_heredoc *herdoc)
{
	char	*line;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		line = readline("heredoc> ");
		if (!line)
		{
			bash->exit_status = 0;
			exit(0);
		}
		if (!ft_strcmp(herdoc->delimiter, line))
		{
			bash->exit_status = 0;
			free (line);
			exit (0);
		}
		else
			write_in_heredoc_files(bash, env, herdoc, line);
		free (line);
	}
}

/*
	Signals :
		WIFEXITED(status): Checks if the child exited
		normally (not killed by a signal)

		WEXITSTATUS(status): Extracts extracts the exit code of a child process
		(only valid if WIFEXITED is true)

		WIFSIGNALED(status): Checks if the child was terminated by a signal

		WTERMSIG(status): Gets the signal number Ctrl+C

		*signal(SIGINT, sigint_handler)
			After heredoc is finished, we restore the original signal behavior


*/

/*
	SIGINT 	= This is the signal sent when you press Ctrl+C in your terminal
	SIG_IGN = This is a special flag that means "ignore this signal"

	Tells the parent to ignore Ctrl+C (SIGINT) during the heredoc input phase
	Because if the user presses Ctrl+C, we want only the child process to stop
		 not the entire shell
*/

int	fork_heredoc(t_minibash *bash, t_env **env, t_heredoc *herdoc)
{
	int	pid;
	int	status;

	signal(SIGINT, SIG_IGN);
	status = -1;
	pid = fork();
	if (!is_fork_succes(bash, pid))
		return (0);
	if (!pid)
		child_process(bash, env, herdoc);
	else
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status) && WEXITSTATUS(status) == 0)
			bash->exit_status = status;
		else if (WIFSIGNALED(status))
			bash->exit_status = 128 + WTERMSIG(status);
	}
	signal(SIGINT, sigint_handler);
	return (status);
}

/*
	WTERMSIG(status) :
		A macro that extracts the signal number from the process exit status

	SIGINT :
		checks if it was Ctrl+C  (signal 2)
*/

int	process_her_with_signals(t_minibash *bash, t_env **env, t_cmd *cmd)
{
	t_heredoc	*heredoc;
	int			status;

	status = -1;
	heredoc = cmd->heredoc;
	while (cmd && heredoc)
	{
		status = fork_heredoc(bash, env, heredoc);
		if (WTERMSIG(status) == SIGINT)
		{
			return (status);
		}
		heredoc = heredoc->next;
	}
	return (status);
}

/*
	WTERMSIG : Extracts the signal number if a child was killed by a signal

	SIGINT : Represents Ctrl+C (signal number 2)

	my code checkk: if (WTERMSIG(st) == SIGINT)
		detects if heredoc processing was interrupted by Ctrl+C

*/

bool	handle_heredocs(t_minibash *bash, t_env **env, t_cmd *tmp_cmd)
{
	t_cmd	*cmd;
	char	*idx_to_char;
	int		st;

	if (!tmp_cmd)
		return (false);
	idx_to_char = NULL;
	cmd = tmp_cmd;
	create_tmp_herdoc_files(cmd, idx_to_char);
	while (cmd)
	{
		st = process_her_with_signals(bash, env, cmd);
		if (WTERMSIG(st) == SIGINT)
		{
			return (true);
		}
		cmd = cmd->next;
	}
	return (false);
}
