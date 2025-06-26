/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   access.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajelloul <ajelloul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 11:42:38 by ajelloul          #+#    #+#             */
/*   Updated: 2025/06/26 16:24:04 by ajelloul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_handle_directory_check(t_minibash *bash, char *path, char **args)
{
	if (ft_is_directory(path))
		ft_handle_error_exit(bash, args, "is a directory\n", 126);
}

void	ft_handle_trailing_slash_path(t_minibash *bash, char *path, char **args)
{
	if (ft_is_directory(path))
		ft_handle_error_exit(bash, args, "is a directory\n", 126);
	else
		ft_handle_error_exit(bash, args, "Not a directory\n", 126);
}

void	handle_cmd_not_found(t_minibash *b, char **env, char *path, char **arg)
{
	ft_handle_file_not_found(b, env, path, arg);
	if (access(path, X_OK) == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		if (arg && arg[0])
		{
			ft_putstr_fd(arg[0], 2);
			ft_putstr_fd(": ", 2);
		}
		ft_putstr_fd("command not found\n", 2);
		b->exit_status = 127;
		exit(127);
	}
	if (ft_is_directory(path))
	{
		ft_putstr_fd("minishell: ", 2);
		if (arg && arg[0])
		{
			ft_putstr_fd(arg[0], 2);
			ft_putstr_fd(": ", 2);
		}
		ft_putstr_fd("command not found\n", 2);
		b->exit_status = 127;
		exit(127);
	}
}

void	ft_handle_absolute_path_script(t_minibash *bash,
	char *path, char **args)
{
	if (access(path, F_OK) == -1)
		ft_handle_error_exit(bash, args, "No such file or directory\n", 126);
	ft_handle_permission_denied(bash, path, args);
	ft_handle_directory_check(bash, path, args);
}

void	acc_ess(t_minibash *bash, char **env, char *path, char **args)
{
	if (!path || !args || !args[0])
	{
		bash->exit_status = 0;
		exit(0);
	}
	if (ft_strncmp(path, "./", 2) == 0 || path[0] == '/')
	{
		ft_handle_absolute_path_script(bash, path, args);
		return ;
	}
	if (path[ft_strlen(path) - 1] == '/')
	{
		ft_handle_trailing_slash_path(bash, path, args);
		return ;
	}
	handle_cmd_not_found(bash, env, path, args);
}
