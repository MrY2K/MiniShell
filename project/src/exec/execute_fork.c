// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   execute_fork.c                                     :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: achoukri <achoukri@student.42.fr>          +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2025/06/05 08:49:22 by ajelloul          #+#    #+#             */
// <<<<<<< HEAD
// /*   Updated: 2025/06/15 14:52:31 by ajelloul         ###   ########.fr       */
// =======
// /*   Updated: 2025/06/13 20:06:53 by achoukri         ###   ########.fr       */
// >>>>>>> origin/achoukri
// /*                                                                            */
// /* ************************************************************************** */

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
		free(file);
		return (0);
	}
	if (!setup_heredoc_input(fd))
	{
		free(file);
		return (0);
	}
	free(file);
	return (1);
}

void	execute_external_cmd(t_minibash *bash, t_env **env,
	t_cmd *cmd, char **args)
{
	char	*path;
	char	**envp;

	if (!cmd || !args || !args[0])
		return (bash->exit_status = 127, (void)0);
	envp = convert_env_list_to_array(env);
	if (args[0][0] == '/')
		path = args[0];
	else
		path = command_path(args[0], envp);
	if (!path)
	{
		ft_putendl_fd("minishell: command not found", 2);
		free_2d(envp);
		bash->exit_status = 127;
		exit(127);
	}
	if (execve(path, args, envp) == -1)
	{
		ft_putendl_fd("minishell: command not found", 2);
		free(path);
		free_2d(envp);
		bash->exit_status = 127;
		exit(127);
	}
}

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

*/

void	execute_command(t_minibash *bash, t_env **env, t_cmd *cmd)
{
	(void) env;
	if (has_herdoc(cmd) && has_redirections(cmd) && !has_pipes(cmd))
	{
		if (!handle_heredoc_input(cmd))
		{
			bash->exit_status = 1;
			return ;
		}
		handle_redirections(bash, cmd);
		execute_external_cmd(bash, env, cmd, cmd->argument);
	}
	else if (has_pipes(cmd))
	{
		handle_pipes(bash, env, cmd);
	}
	else
	{
		execute_single_cmd(bash, env, cmd);
	}
	exit (bash->exit_status);
}
