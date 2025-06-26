/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   access_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajelloul <ajelloul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 20:52:48 by ajelloul          #+#    #+#             */
/*   Updated: 2025/06/26 16:25:11 by ajelloul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*

	stat system call to get detailed information about 
		a file or directory at a specific path

	S_ISDIR = This is a macro that checks if the file is a directory

*/

int	ft_is_directory(char *path)
{
	struct stat	path_stat;

	if (stat(path, &path_stat) == 0 && S_ISDIR(path_stat.st_mode))
		return (1);
	return (0);
}

void	ft_handle_error_exit(t_minibash *bash, char **args, char *msg, int code)
{
	ft_putstr_fd("minishell: ", 2);
	if (args && args[0])
	{
		ft_putstr_fd(args[0], 2);
		ft_putstr_fd(": ", 2);
	}
	ft_putstr_fd(msg, 2);
	bash->exit_status = code;
	exit(code);
}

void	ft_handle_file_not_found(t_minibash *bash,
	char **env, char *path, char **args)
{
	if (access(path, F_OK) == -1)
	{
		if (get_env_variable("PATH", env) == NULL)
			ft_handle_error_exit(bash, args, "No such file or directory\n", 127);
		ft_handle_error_exit(bash, args, "command not found\n", 127);
	}
}

void	ft_handle_permission_denied(t_minibash *bash, char *path, char **args)
{
	if (access(path, X_OK) == -1)
		ft_handle_error_exit(bash, args, "Permission denied\n", 126);
}
