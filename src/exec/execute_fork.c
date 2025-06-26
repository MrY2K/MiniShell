/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_fork.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajelloul <ajelloul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 12:24:24 by ajelloul          #+#    #+#             */
/*   Updated: 2025/06/25 19:47:26 by ajelloul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
	1 - Get the last heredoc in the command (only the last one is used as input)
	2 - Generate a unique temporary filename for the heredoc
	3 - Open the temporary heredoc file for reading
	4 - Redirect the file to STDIN using dup2 so the command reads from it
*/

int	handle_heredoc_input(t_cmd *cmd)
{
	t_cmd	*tmp;
	char	*file;
	int		fd;

	if (!cmd || !cmd->heredoc)
		return (0);
	tmp = get_last_heredoc(cmd);
	file = generate_heredoc_file_name(tmp->heredoc);
	if (!file)
		return (0);
	fd = open_heredoc_file(file);
	if (fd < 0)
	{
		ft_putstr_fd("minishell: No such file or directory\n", 2);
		free(file);
		exit(1);
	}
	if (dup2(fd, 0) < 0)
	{
		free(file);
		exit(1);
	}
	free(file);
	close(fd);
	return (fd);
}

void	execute_external_cmd(t_minibash *bash, t_env **env,
	t_cmd *cmd, char **args)
{
	char	*path;
	char	**envp;

	if (!cmd || !args || !args[0])
		return ;
	envp = convert_env_list_to_array(env);
	if (args[0][0] == '/')
		path = args[0];
	else
		path = path_command(args[0], envp, bash);
	if (!path)
	{
		execute_error(bash, "PATH");
		free_2d(envp);
		exit(127);
	}
	acc_ess(bash, envp, path, args);
	if (execve(path, args, envp) == -1)
	{
		execute_error(bash, "command not found");
		free(path);
		free_2d(envp);
		exit(127);
	}
}

/*
	case 1 : export > file
*/

void	execute_single_cmd(t_minibash *bash, t_env **env, t_cmd *cmd)
{
	if (has_redirections(cmd))
	{
		handle_redirections(bash, cmd);
		execute_builtins(bash, env, cmd);
	}
	if (!is_builtins(cmd))
		execute_external_cmd(bash, env, cmd, cmd->argument);
}

/*
	Case 1 :
		cat << ONE << TWO > out.txt

		cat << 42 < input -> cat the input of input

		cat << 42 < input > out   ->  The content of input will be written to out.

*/

static void	handle_heredoc_execution(t_minibash *bash, t_env **env, t_cmd *cmd)
{
	int	her_fd;

	her_fd = handle_heredoc_input(cmd);
	if (her_fd != -1)
	{
		dup2(her_fd, 0);
		close(her_fd);
	}
	if (has_redirections(cmd))
		handle_redirections(bash, cmd);
	execute_external_cmd(bash, env, cmd, cmd->argument);
}
/*
	cat << ONE << TWO > out.txt

	cat << 42

*/

void	execute_command(t_minibash *bash, t_env **env, t_cmd *cmd)
{
	if (has_herdoc(cmd) && has_redirections(cmd) && !has_pipes(cmd))
		handle_heredoc_execution(bash, env, cmd);
	else if (has_herdoc(cmd) && !has_pipes(cmd))
		handle_heredoc_execution(bash, env, cmd);
	else if (has_pipes(cmd))
		handle_pipes(bash, env, cmd);
	else
		execute_single_cmd(bash, env, cmd);
	exit(bash->exit_status);
}
