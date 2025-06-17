/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achoukri <achoukri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 00:00:00 by achoukri          #+#    #+#             */
/*   Updated: 2025/06/17 01:57:02 by achoukri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_ft_split(char **list)
{
	int	i;

	if (list == NULL)
		return ;
	i = 0;
	while (list[i] != NULL)
	{
		free(list[i]);
		i++;
	}
	free(list);
}

static char	*search_in_path(char **list, char *cmd)
{
	char	*tmp;
	char	*full_path;
	int		i;

	i = 0;
	while (list[i])
	{
		if (cmd[0] == '/')
			full_path = ft_strdup(cmd);
		else
		{
			tmp = ft_strjoin(list[i], "/");
			full_path = ft_strjoin(tmp, cmd);
			free(tmp);
		}
		if (access(full_path, F_OK) != -1 && access(full_path, X_OK) != -1)
		{
			free_ft_split(list);
			return (full_path);
		}
		free(full_path);
		i++;
	}
	return (NULL);
}

static char	*get_path_variable(char **env, t_minibash *minibash)
{
	char	*path;

	path = get_env_variable("PATH", env);
	if (path == NULL)
	{
		path = getcwd(NULL, 0);
		if (!path)
		{
			ft_putstr_fd("No such file or directory\n", 2);
			minibash->exit_status = 127;
			exit(EXIT_FAILURE);
		}
	}
	return (path);
}

char	*path_command(char *cmd, char **env, t_minibash *minibash)
{
	char	*path;
	char	**path_list;
	char	*result;

	if (cmd != NULL && cmd[0] == '\0')
	{
		ft_putstr_fd("minishell: command not found\n", 2);
		minibash->exit_status = 127;
		exit(127);
	}
	if (cmd == NULL)
		return (NULL);
	if (cmd[0] == '.')
		return (cmd);
	path = get_path_variable(env, minibash);
	path_list = ft_split(path, ':');
	result = search_in_path(path_list, cmd);
	if (result == NULL)
	{
		free_2d(path_list);
		return (cmd);
	}
	return (result);
}
