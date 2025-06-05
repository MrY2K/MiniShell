/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajelloul <ajelloul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 08:14:27 by ajelloul          #+#    #+#             */
/*   Updated: 2025/06/05 13:07:14 by ajelloul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * Handles commands that start with '/' (absolute paths)
 * Checks file existence, directory status, and execute permissions
 * Sets appropriate exit codes matching bash behavior
 */
static char	*handle_absolute_path(t_minibash *bash, char *command)
{
	if (access(command, F_OK) != 0)
	{
		print_cmd_err(bash, command, "No such file or directory", 127);
		return (NULL);
	}
	if (is_directory(command))
	{
		print_cmd_err(bash, command, "Is a directory", 126);
		return (NULL);
	}
	if (!is_file_executable(command))
	{
		print_cmd_err(bash, command, "Permission denied", 126);
		return (NULL);
	}
	return (ft_strdup(command));
}

/**
 * Handles relative paths (./command or ../command)
 * Manages special cases like bare "." and ".." 
 * Validates file existence and execute permissions
 */
static char	*handle_relative_path(t_minibash *bash, char *command)
{
	if (ft_strcmp(command, ".") == 0)
	{
		return (print_cmd_err(bash, ".", "filename argument required", 2), NULL);
	}
	if (ft_strcmp(command, "..") == 0)
	{
		print_cmd_err(bash, "..", "command not found", 127);
		return (NULL);
	}
	if (access(command, F_OK) != 0)
	{
		print_cmd_err(bash, command, "No such file or directory", 127);
		return (NULL);
	}
	if (is_directory(command))
	{
		print_cmd_err(bash, command, "Is a directory", 126);
		return (NULL);
	}
	if (!is_file_executable(command))
	{
		print_cmd_err(bash, command, "Permission denied", 126);
		return (NULL);
	}
	return (ft_strdup(command));
}

/**
 * Constructs full executable path by joining directory and command name
 * Returns allocated string that caller must free, or NULL on failure
 */
char	*join_path(char *directory, char *command_name)
{
	char	*full_path;
	int		dir_len;
	int		cmd_len;
	int		i;

	if (!directory || !command_name || !*command_name)
		return (NULL);
	dir_len = ft_strlen(directory);
	cmd_len = ft_strlen(command_name);
	full_path = malloc(dir_len + cmd_len + 2);
	if (!full_path)
		return (NULL);
	i = -1;
	while (++i < dir_len)
		full_path[i] = directory[i];
	full_path[i++] = '/';
	dir_len = -1;
	while (++dir_len < cmd_len)
		full_path[i + dir_len] = command_name[dir_len];
	full_path[i + dir_len] = '\0';
	return (full_path);
}

/**
 * Searches PATH directories for the command
 * Iterates through all PATH entries and tests each one
 * Returns first executable match found or NULL if not found
 */
static char	*search_in_path_directories(t_minibash *bash, char *command)
{
	char	*full_path;
	int		i;

	if (!bash->path || !bash->path[0])
	{
		print_cmd_err(bash, command, "command not found", 127);
		return (NULL);
	}
	i = 0;
	while (bash->path[i])
	{
		full_path = join_path(bash->path[i], command);
		if (!full_path)
		{
			i++;
			continue ;
		}
		if (is_file_executable(full_path))
			return (full_path);
		free(full_path);
		i++;
	}
	print_cmd_err(bash, command, "command not found", 127);
	return (NULL);
}

/**
 * Main function: resolves command to full executable path
 * Determines if command needs PATH search or direct path handling
 * Returns allocated string that caller must free, or NULL on failure
 */
char	*command_path(t_minibash *bash, t_cmd *cmd)
{
	if (!cmd->main_cmd || !*(cmd->main_cmd))
	{
		bash->exit_status = 127;
		return (NULL);
	}
	if (contains_path_separator(cmd->main_cmd))
	{
		if (cmd->main_cmd[0] == '/')
			return (handle_absolute_path(bash, cmd->main_cmd));
		else
			return (handle_relative_path(bash, cmd->main_cmd));
	}
	return (search_in_path_directories(bash, cmd->main_cmd));
}
