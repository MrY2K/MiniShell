/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_fork.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajelloul <ajelloul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 08:49:22 by ajelloul          #+#    #+#             */
/*   Updated: 2025/06/06 14:52:53 by ajelloul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*generate_heredoc_file_name(t_heredoc *her)
{
	char	*index;
	char	*join_del;
	char	*path;
	
	index = ft_itoa(her->index);
	join_del = ft_strjoin_with_null(her->delimiter, index);
	path = ft_strjoin_with_null("/tmp/minishell/heredoc", join_del);
	free (index);
	free (join_del);
	return (path);
}
static t_cmd	*get_last_heredoc(t_cmd *cmd)
{
	t_cmd	*tmp;

	tmp = cmd;
	while (tmp->heredoc->next)
		tmp->heredoc = tmp->heredoc->next;
	return (tmp);
}

static int	open_heredoc_file(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY, 0644);
	if (fd < 0)
	{
		ft_putendl_fd("minishell: No such file or directory", 2);
		return (-1);
	}
	return (fd);
}

static int	setup_heredoc_input(int fd, char *file)
{
	if (dup2(fd, STDIN_FILENO) < 0)
	{
		perror("dup2");
		close(fd);
		free(file);
		return (0);
	}
	close(fd);
	return (1);
}

int	handle_heredoc_input(t_cmd *cmd) // hundle_file_herdoc
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
	if (!setup_heredoc_input(fd, file))
		return (0);
	free(file);
	return (1);
}

void	execute_external_cmd(t_minibash *bash, t_env **env, t_cmd *cmd, char **args)
{
	char	*path;
	char	**envp;

	if (!cmd || !args || !args[0])
    	return (bash->exit_status = 127, (void)0);
		
	path = command_path(bash, cmd);
	if (!path)
		exit(127);
	envp = convert_env_list_to_array(env);
	if (!envp)
	{
		free(path);
		perror("minishell");
		exit(1);
	}
	if (execve(path, args, envp) == -1)
	{
		perror("minishell");
		free(path);
		free_2d(envp);
		bash->exit_status = 126;
		exit(126);
	}
}

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
		exit (bash->exit_status);
	}
	else if (has_pipes(cmd))
	{
		handle_pipes(bash, env, cmd);
		exit(bash->exit_status);
	}
	// else
	// {
	// 	execute_simple_command(bash, env, cmd);
	// }
}
