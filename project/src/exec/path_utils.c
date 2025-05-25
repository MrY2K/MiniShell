/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajelloul <ajelloul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 11:13:02 by ajelloul          #+#    #+#             */
/*   Updated: 2025/05/21 11:47:30 by ajelloul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * Checks if a file exists and has execute permissions
 */
bool	is_file_executable(char *file_path)
{
	if (!file_path || !*file_path)
		return (false);
	if (access(file_path, F_OK) != 0)
		return (false);
	return (access(file_path, X_OK) == 0);
}

/**
 * Checks if path is a directory using opendir
 * Returns true if successfully opens as directory, false otherwise
 *
 * DIR - A directory stream type used for directory operations
 * return: 
 *   - On success: Returns a pointer to a DIR structure (DIR*)
 *     representing the opened directory stream.
 *   - On failure: Returns NULL, and errno is set to indicate
 */
bool	is_directory(char *path)
{
	DIR	*dir;

	dir = opendir(path);
	if (dir)
	{
		closedir(dir);
		return (true);
	}
	return (false);
}

/**
 * Checks if command contains path separators (should not use PATH)
 * Returns true if command has '/' character anywhere in string
 */
bool	contains_path_separator(char *command)
{
	int	i;

	i = 0;
	while (command[i])
	{
		if (command[i] == '/')
			return (true);
		i++;
	}
	return (false);
}
