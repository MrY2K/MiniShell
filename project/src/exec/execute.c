// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   execute.c                                          :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: ajelloul <ajelloul@student.42.fr>          +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2025/05/20 16:29:21 by ajelloul          #+#    #+#             */
// /*   Updated: 2025/05/25 14:16:25 by ajelloul         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

#include "../../includes/minishell.h"


// static void	execute_external_cmd(t_minibash *bash, t_cmd *cmd, char **args)
// {
// 	char	*path;
// 	char	**envp;

// 	if (!cmd || !args || !args[0])
// 	{
// 		bash->exit_status = 127;
// 		exit(127);
// 	}
// 	path = command_path(bash, cmd);
// 	if (!path)
// 		exit(bash->exit_status);
// 	envp = env_to_array(bash->env);
// 	if (!envp)
// 	{
// 		free(path);
// 		perror("minishell");
// 		exit(1);
// 	}

// 	if (execve(path, args, envp) == -1)
// 	{
// 		perror("minishell");
// 		free(path);
// 		free_2d(envp);
// 		bash->exit_status = 126;
// 		exit(126);
// 	}
// }


// static void	execute_single_cmd(t_minibash *bash, t_cmd *cmd)
// {
// 	if (!cmd)
// 	{
// 		bash->exit_status = 127;
// 		exit(127);
// 	}
// 	if (is_builtins(cmd))
// 		execute_builtin(bash, cmd);
// 	else
// 		execute_external_cmd(bash, cmd, cmd->argument);
// }

// static void	run_command(t_minibash *bash, t_cmd *cmd)
// {
// 	// handel pipe and pipe
	
// 	if (has_pipes(cmd))
// 	{
// 		execute_pipe_chain (bash, cmd);
// 	}

// 	execute_single_cmd(bash, cmd);
// }

// static void	wait_for_child(t_minibash *bash, int pid)
// {
// 	int	status;

// 	if (waitpid(pid, &status, 0) == -1)
// 	{
// 		perror("minishell");
// 		bash->exit_status = 1;
// 		return ;
// 	}
// 	if (WIFEXITED(status))
// 		bash->exit_status = WEXITSTATUS(status);
// 	else if (WIFSIGNALED(status))
// 		bash->exit_status = 128 + WTERMSIG(status);
// }


void	create_tmp_herdoc_files(t_cmd *tmp_cmd, char *idx_to_char)
{
	t_cmd 		*cmd;
	t_heredoc	*heredoc;
	char		*path;
	char		*line;

	if (!tmp_cmd)
		return ;
	cmd = tmp_cmd;
	while (cmd)
	{
		heredoc = cmd->heredoc;
		while (cmd && heredoc)
		{
			idx_to_char = ft_itoa(heredoc->index);
			line = ft_strjoin_with_null(heredoc->delimiter, idx_to_char);
			free (idx_to_char);
			path = ft_strjoin_with_null("/tmp/minishell/heredoc", line);
			free (line);
			heredoc->fd = open(path, O_CREAT | O_WRONLY | O_APPEND, 0600);
			free (path);
			close(heredoc->fd);
			heredoc = heredoc->next;
		}
		cmd = cmd->next;
	}
}

char	*get_path(t_heredoc *heredoc)
{
	char	*path;
	char	*line;
	char	*index_toa;

	index_toa = ft_itoa(heredoc->index);
	line = ft_strjoin_with_null(heredoc->delimiter, index_toa);
	path = ft_strjoin("/tmp/minshell/heredoc", line);
	free (line);
	free (index_toa);
	return (path);
}

void	append_regular_characters(t_expand_heredoc *ex, char *line)
{
	ex->j = ex->index;
	while (line[ex->index] && line[ex->index] != '$')
	{
		ex->index++;
		ex->len++;
	}
	ex->str = ft_substr(line, ex->j, ex->len);
	ex->expanded_line = ft_strjoin(ex->expanded_line, ex->str);
	free (ex->str);
	ex->index--;
}

int	search(char *str, char *to_find)
{
    int str_idx;
    int find_idx;
    int find_len;

    if (!str || !to_find)
        return (0);
    str_idx = 0;
    find_idx = 0;
    find_len = ft_strlen(to_find);
    while (str[str_idx] && to_find[find_idx])
    {
        if (str[str_idx] == to_find[find_idx])
            find_idx++;
        if (find_len == find_idx && str[str_idx + 1] == to_find[find_idx])
            return (1);
        str_idx++;
    }
    return (0);
}

void	lookup_env_var(t_env **env, char *arg, char **str, int *i)
{
	t_env *_env;

	_env = *env;
	while (_env)
	{
		if (search(_env->name, arg + (*i)))
		{
			*str = ft_strdup(_env->value);
			break ;
		}
		else
			*str = NULL;
		_env = _env->next;
	}
}

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
					ex.str = ft_strdup(ex.expanded_line), free(ex.expanded_line), ex.str);
			ex.index++;
			if (!str[ex.index]) // echo $
				return (ex.str = ft_strdup("$"), ex.str);
			if (str[ex.index] == '\"' || str[ex.index] == '\'')
				return (ex.str = ft_strdup(""), ex.str); // bra
			// /* Handle $"..." and $'...' cases */
            // if (arg[id.i] == '\"' || arg[id.i] == '\'') // echo $'hello\nworld'
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

			if (!ft_isalnum(str[ex.index]) || ft_isdigit(str[ex.index])) // "$9var" "$_HOME" 
				return (ex.str);
			lookup_env_var(env, str, &ex.str, &ex.index);
		}
		ex.index++;
	}
	return (ex.str);
}

char	*expand_env_var_her(t_minibash *bash, t_env *env, char	**expanded_line, int *index, char *line)
{
	t_env_var	var;

	var.len = 0;
	(*index)++;
	var.j = *index;
	if (line[*index] == '?')
	{
		var.len++;
		(*index)++;
	}
	else
	{
		while (line[*index] && (ft_isalnum(line[*index])))
		{
			(*index)++;
			var.len++;
		}
	}
	(*index)--;
	var.j--;
	var.sub = ft_substr(line, var.j, ++var.len);
	var.str = expand(bash, &env, var.sub);
	*expanded_line = ft_strjoin(*expanded_line, var.str);
	free(var.sub);
	return (free (var.str), *expanded_line);
} // ✅     ✅  stop her  ✅     ✅;

char	*expand_env_var_in_heredoc(t_minibash *bash, char *line, t_env *env)
{
	t_expand_heredoc	ex;

	ex.index = 0;
	while (line[ex.index])
	{
		ex.len = 0;
		if (line[ex.index] == '$')
			ex.expanded_line = expand_env_var_her(bash, env, &ex.expanded_line, &ex.index, line);
		else
			append_regular_characters(&ex, line);
		ex.index++;
	}
	return (ex.expanded_line);
}

void	write_in_heredoc_files(t_minibash *bash, t_env **env, t_heredoc *heredoc, char *line)
{
	t_env 	*tmp_env;
	char	*path;
	char	*expanded_line;
	int		fd;

	expanded_line = NULL;
	tmp_env = *env;
	path = get_path(heredoc);
	fd = open(path, O_CREAT | O_WRONLY | O_APPEND, 0600);
	if (fd < 0)
		return (perror("open"));
	if (heredoc->expand == 1)
	{
		expanded_line = expand_env_var_in_heredoc(bash, line, tmp_env);
		ft_putendl_fd(expanded_line, fd);
		free (expanded_line);
	}
	else
		ft_putendl_fd(line, fd);
	free (path);
	close(fd);
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
		line = readline("> ");
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

	my code : If the user presses Ctrl+C, ignore it completely and continue whatever you were doing
*/

int	handell_fork(t_minibash *bash, t_env **env, t_heredoc *herdoc)
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
	// signal 		function
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
		status = handell_fork(bash, env, heredoc);
		if (WTERMSIG(status) == SIGINT)
		{
			return (status); // 130 (128 + 2)
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

int validate_redirection_file(t_cmd *list)
{
    t_cmd *cmd;
    int   fd;

    if (list == NULL)
        return (0);  // No error - success
    
    cmd = list;
    while (cmd->redirections)
    {
        fd = -1;
        
        if (cmd->redirections->type == TOKEN_REDIR_APPEND)
            fd = open(cmd->redirections->file_path, O_CREAT | O_WRONLY | O_APPEND, 0644);
        else if (cmd->redirections->type == TOKEN_REDIR_OUT)
            fd = open(cmd->redirections->file_path, O_CREAT | O_WRONLY | O_TRUNC, 0644);
        else if (cmd->redirections->type == TOKEN_REDIR_IN)
            fd = open(cmd->redirections->file_path, O_RDONLY, 0644);
        if (fd < 0)
            return (1);
        close(fd);
        cmd->redirections = cmd->redirections->next;
    }
    return (0);
}

void	execute_parent_builtin(t_minibash *bash, t_env **env, t_cmd *cmd)
{
	if (has_redirections(cmd))
		if (validate_redirection_file(cmd))
			return ;
	if (cmd->argument[1]) // with argument is normally unset export
		execute_builtins(bash, env, cmd);
	if (!ft_strcmp(cmd->main_cmd, "exit") && !cmd->argument[1])
		execute_builtins(bash, env, cmd);
	if (!ft_strcmp(cmd->main_cmd, "cd") && !cmd->argument[1])
		execute_builtins(bash, env, cmd);
}

int	process_herdoc_builtins(t_minibash *bash, t_env **env, t_cmd *cmd)
{
	t_cmd *tmp_cmd;

	tmp_cmd = cmd;
	if (!cmd)
		return (0);
	if (has_herdoc(tmp_cmd))
	{
		if (handle_heredocs(bash, env, tmp_cmd))
			return (-1);
		if (is_builtins(tmp_cmd) && !has_redirections(tmp_cmd) && !has_pipes(tmp_cmd)) // complet redirection 
		{
			execute_builtins(bash, env, tmp_cmd);
			return (1);
		}
	}
	if (is_builtins(tmp_cmd) && !has_redirections(tmp_cmd) && !has_pipes(tmp_cmd) && !has_herdoc(tmp_cmd))
	{
		execute_builtins(bash, env, tmp_cmd);
		return (1);
	}
	else if(is_parent_builtins(tmp_cmd) && !has_pipes(tmp_cmd))
	{
		execute_parent_builtin(bash, env, tmp_cmd);
	}
	return (0);
}

void delete_heredoc_files(t_minibash *bash, t_cmd *cmd) 
{
    t_heredoc_cleanup cleanup;

    cleanup.current_cmd = cmd;
    while (cleanup.current_cmd) 
	{
        cleanup.current_heredoc = cleanup.current_cmd->heredoc;
        while (cleanup.current_heredoc) 
		{
            cleanup.index_str = ft_itoa(cleanup.current_heredoc->index);
            cleanup.temp_path = ft_strjoin_with_null(cleanup.current_heredoc->delimiter, cleanup.index_str);
            cleanup.full_filepath = ft_strjoin("/tmp/minishell/heredoc", cleanup.temp_path);
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

int	execute_builtins_or_herdoc(t_minibash *bash, t_cmd *cmd)
{
	int	her_status;
	t_env	**env;

	env = &bash->env;
	her_status = process_herdoc_builtins(bash, env, cmd);
	if (her_status == -1) // SIGINT (Ctrl+C)
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


void	execution(t_minibash *bash, t_env **env, t_cmd *cmd)
{
	t_cmd	*tmp_cmd;
	int		pid;

	tmp_cmd = cmd;
	if (execute_builtins_or_herdoc(bash, tmp_cmd))
	{
		return ;
	}
	pid = fork();
	if (!is_fork_succes(bash, pid))
		return ;
	if (!pid)
	{
		// signals
		execute_command(bash, env, cmd);

	}
}
