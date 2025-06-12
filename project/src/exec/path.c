/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajelloul <ajelloul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 08:14:27 by ajelloul          #+#    #+#             */
/*   Updated: 2025/06/10 10:14:32 by ajelloul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*build_full_path(char *dir, char *command)
{
	char	*temp_join;
	char	*full_path;

	if (command[0] == '/')
		return (ft_strdup(command));
	temp_join = ft_strjoin(dir, "/");
	if (!temp_join)
		return (NULL);
	full_path = ft_strjoin(temp_join, command);
	free(temp_join);
	return (full_path);
}

static char	*search_in_path_dirs(char **path_dirs, char *command)
{
	char	*full_path;
	int		i;

	if (!path_dirs || !command)
		return (NULL);
	i = 0;
	while (path_dirs[i])
	{
		full_path = build_full_path(path_dirs[i], command);
		if (full_path && is_valid_executable(full_path))
		{
			free_2d(path_dirs);
			return (full_path);
		}
		if (full_path)
			free(full_path);
		i++;
	}
	free_2d(path_dirs);
	return (NULL);
}

static bool	has_path_separator(char *command)
{
	int	i;

	if (!command)
		return (false);
	i = 0;
	while (command[i])
	{
		if (command[i] == '/')
			return (true);
		i++;
	}
	return (false);
}

char	*command_path(char *command, char **env)
{
	char	*path_env;
	char	**path_dirs;

	if (!command || !*command)
		return (NULL);
	if (has_path_separator(command))
	{
		if (command[0] == '/')
			return (handle_absolute_path(command));
		else
			return (handle_relative_path(command));
	}
	path_env = get_env_variable("PATH", env);
	if (!path_env)
		path_env = getcwd(NULL, 0);
	if (!path_env)
		return (NULL);
	path_dirs = ft_split(path_env, ':');
	if (!path_dirs)
		return (NULL);
	return (search_in_path_dirs(path_dirs, command));
}
