/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bouhammo <bouhammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 20:46:31 by bouhammo          #+#    #+#             */
/*   Updated: 2024/10/20 22:29:39 by bouhammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	parent_proc(int pid)
{
	int	status;

	if (waitpid(pid, &status, 0) == -1)
	{
		perror("waitpid");
		g_exit_status = 1;
	}
	else
	{
		if (WIFEXITED(status))
			g_exit_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			g_exit_status = 128 + WTERMSIG(status);
	}
}

void	hundle_redirections(t_command *list)
{
	t_redirect	*tmp;

	tmp = list->doc;
	while (tmp != NULL)
	{
		if (tmp->type == REDIR_OUT)
		{
			hundle_redir_out(tmp->store, tmp->is_amb);
		}
		else if (tmp->type == REDIR_IN)
		{
			hundle_redir_in(tmp->store, tmp->is_amb);
		}
		else if (tmp->type == DREDIR_OUT)
		{
			hundle_dredir_out(tmp->store, tmp->is_amb);
		}
		tmp = tmp->next;
	}
}

void	run_command(t_command *list, t_environment **var)
{
	int	heredoc_fd;

	heredoc_fd = -1;
	if (herdoc_exist(list) == 1 && !pipe_exist(list) && test_redir(list))
	{
		heredoc_fd = hundle_file_herdoc(list);
		if (heredoc_fd != -1)
		{
			dup2(heredoc_fd, STDIN_FILENO);
			close(heredoc_fd);
		}
		hundle_redirections(list);
		execution_cmd(var, list, list->arg);
		exit(g_exit_status);
	}
	else if (pipe_exist(list) == 1)
	{
		handle_pipe(list, var);
		exit(g_exit_status);
	}
	else
	{
		run_simple_cmd(list, var);
		exit(g_exit_status);
	}
}

bool	execut_her_built(t_environment **var, t_command *cmd)
{
	t_command	*list;
	int			her;

	list = cmd;
	her = run_herdoc_built(var, cmd);
	if (her == -1)
	{
		delet_files(list);
		g_exit_status = 1;
		return (true);
	}
	if (her == 1)
	{
		delet_files(list);
		return (true);
	}
	return (false);
}

void	ft_exute(t_environment **var, t_command *cmd)
{
	t_command	*list;
	int			pid;

	list = cmd;
	if (execut_her_built(var, list) == true)
		return ;
	pid = fork();
	if (chech_fork(pid) == 1)
		return ;
	signal(SIGINT, SIG_IGN);
	if (pid == 0)
	{
		signal(SIGQUIT, handl_sig_exec);
		signal(SIGINT, SIG_DFL);
		run_command(list, var);
	}
	else
	{
		parent_proc(pid);
		signal(SIGINT, hhandle_sig);
	}
	delet_files(cmd);
}
