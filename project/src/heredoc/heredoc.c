/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajelloul <ajelloul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 12:01:42 by ajelloul          #+#    #+#             */
/*   Updated: 2025/06/19 20:39:33 by ajelloul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
	char	*expand(t_minibash *bash, t_env **env, char *str)
{
	t_expand_heredoc	ex;

	ex.index = 0;
	while (env && str[ex.index])
	{
		if (search("$\"\"", str)) // $""
			return (ex.str = ft_strdup(""), ex.str);
		else if (str[ex.index] == '$')
		{
			if (str[ex.index + 1] && str[ex.index + 1] == '?')
				return (ex.expanded_line = ft_itoa(bash->exit_status), 
					ex.str = ft_strdup(ex.expanded_line), 
					free(ex.expanded_line), ex.str);
			ex.index++;
			if (!str[ex.index]) // echo $
				return (ex.str = ft_strdup("$"), ex.str);
			if (str[ex.index] == '\"' || str[ex.index] == '\'')
				return (ex.str = ft_strdup(""), ex.str); // bra
			//  Handle $"..." and $'...' cases 
            // if (arg[id.i] == '\"' 
			|| arg[id.i] == '\'') // echo $'hello\nworld'
            // {
            //     char quote_type = arg[id.i];
            //     id.i++; // Skip opening quote
                
            //     // Find closing quote
            //     while (arg[id.i] && arg[id.i] != quote_type)
            //         id.i++;
                
            //     if (arg[id.i] == quote_type)
            //         id.i++; // Skip closing quote
                
            //     // For $"" return empty, for $'' process escapes
            //     if (quote_type == '\'')
            //         return (process_ansi_c_string(arg, &id.i));
            //     else
            //         return (id.s = ft_strdup(""), id.s);
            // }

			if (!ft_isalnum(str[ex.index]) || 
				ft_isdigit(str[ex.index])) // "$9var" "$_HOME" 
				return (ex.str);
			lookup_env_var(env, str, &ex.str, &ex.index);
		}
		ex.index++;
	}
	return (ex.str);
}
*/ 

char	*expand(t_minibash *bash, t_env **env, char *str)
{
	t_expand_heredoc	ex;

	ex.index = 0;
	while (env && str[ex.index])
	{
		if (search("$\"\"", str))
			return (ex.s = ft_strdup(""), ex.s);
		else if (str[ex.index] == '$')
		{
			if (str[ex.index + 1] && str[ex.index + 1] == '?')
				return (ex.expanded_line = ft_itoa(bash->exit_status), 
					ex.s = ft_strdup(ex.expanded_line), 
					free(ex.expanded_line), ex.s);
			ex.index++;
			if (!str[ex.index])
				return (ex.s = ft_strdup("$"), ex.s);
			if (str[ex.index] == '\"' || str[ex.index] == '\'')
				return (ex.s = ft_strdup(""), ex.s);
			if (!ft_isalnum(str[ex.index]) || ft_isdigit(str[ex.index])) 
				return (ex.s);
			lookup_env_var(env, str, &ex.s, &ex.index);
		}
		ex.index++;
	}
	return (ex.s);
}

/*
	signal(SIGINT, SIG_DFL) :
		Makes the child process terminate when Ctrl+C (SIGINT) is pressed
	
	signal(SIGQUIT, SIG_IGN) :
		Makes the child *ignore Ctrl+* (SIGQUIT)

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
		WIFEXITED(status): Checks if the child exited normally (not killed by a signal)

		WEXITSTATUS(status): Extracts the exit status (only valid if WIFEXITED is true)

		WIFSIGNALED(status): Checks if the child was terminated by a signal

		WTERMSIG(status): Gets the signal number that caused termination

*/

/*
	SIGINT 	= This is the signal sent when you press Ctrl+C in your terminal
	SIG_IGN = This is a special flag that means "ignore this signal"

	my code : If the user presses Ctrl+C, 
		ignore it completely and continue whatever you were doing
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
