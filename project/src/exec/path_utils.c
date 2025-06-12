/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajelloul <ajelloul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 11:13:02 by ajelloul          #+#    #+#             */
/*   Updated: 2025/06/12 12:55:43 by ajelloul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_env_variable(char *name, char **env)
{
	int		i;
	int		name_len;
	char	*equal_pos;

	if (!name || !env)
		return (NULL);
	name_len = ft_strlen(name);
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], name, name_len) == 0)
		{
			equal_pos = ft_strchr(env[i], '=');
			if (equal_pos && env[i][name_len] == '=')
				return (equal_pos + 1);
		}
		i++;
	}
	return (NULL);
}

bool	is_valid_executable(char *path)
{
	if (!path)
		return (false);
	if (access(path, F_OK) == -1)
		return (false);
	if (access(path, X_OK) == -1)
		return (false);
	return (true);
}

bool	is_directory_path(char *path)
{
	DIR	*dir;

	if (!path)
		return (false);
	dir = opendir(path);
	if (dir)
	{
		closedir(dir);
		return (true);
	}
	return (false);
}

char	*handle_absolute_path(char *command)
{
	if (access(command, F_OK) == -1)
		return (NULL);
	if (is_directory_path(command))
		return (NULL);
	if (!is_valid_executable(command))
		return (NULL);
	return (ft_strdup(command));
}

char	*handle_relative_path(char *command)
{
	if (ft_strcmp(command, ".") == 0)
		return (NULL);
	if (ft_strcmp(command, "..") == 0)
		return (NULL);
	if (access(command, F_OK) == -1)
		return (NULL);
	if (is_directory_path(command))
		return (NULL);
	if (!is_valid_executable(command))
		return (NULL);
	return (ft_strdup(command));
}
