/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bouhammo <bouhammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 12:21:29 by bouhammo          #+#    #+#             */
/*   Updated: 2024/10/06 12:49:14 by bouhammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_directory(char *path)
{
	struct stat	path_stat;

	if (stat(path, &path_stat) == 0 && S_ISDIR(path_stat.st_mode))
	{
		return (1);
	}
	return (0);
}

void	printf_error_exit(char *ptr, char **str, char *s, int ext)
{
	(void)str;
	ft_putstr_fd(ptr, 2);
	ft_putstr_fd(s, 2);
	g_exit_status = ext;
	exit(ext);
}

void	ft_access_2(char *ptr, char **str, char **env_v)
{
	if (access(ptr, F_OK) == -1)
	{
		if (ft_getenv("PATH", env_v) == NULL)
		{
			printf_error_exit("minishell ", str,
				": No such file or directory\n", 127);
		}
		if (access(ptr, X_OK) == -1)
		{
			printf_error_exit("minishell ", str, ": command not found\n", 127);
		}
	}
	else if (is_directory(ptr))
	{
		ft_putstr_fd("minishell", 2);
		ft_putstr_fd(": command not found\n", 2);
		if (ptr != str[0])
			free(ptr);
		g_exit_status = 127;
		exit(127);
	}
}

void	ft_access_1(char *ptr, char **str, char **env_v)
{
	if (ptr[ft_strlen(ptr) - 1] == '/')
	{
		if (is_directory(ptr))
		{
			printf_error_exit("minishell", str, ": is a directory\n", 126);
			exit(126);
		}
		else
		{
			printf_error_exit("minishell", str, ": Not a directory\n", 126);
			exit(126);
		}
	}
	else
	{
		ft_access_2(ptr, str, env_v);
	}
}

void	ft_access(char *ptr, char **str, char **env_v)
{
	if (ptr == NULL || str == NULL || *str == NULL)
		exit(0);
	if (ft_strncmp(ptr, "./", 2) == 0 || ptr[0] == '/')
	{
		if (access(ptr, F_OK) == -1)
		{
			printf_error_exit("minishell", str, ": No such file or directory\n",
				127);
			exit(127);
		}
		if (access(ptr, X_OK) == -1)
		{
			printf_error_exit("minishell", str, ": Permission denied\n", 126);
			exit(126);
		}
		if (is_directory(ptr))
		{
			printf_error_exit("minishell", str, ": is a directory\n", 126);
			exit(126);
		}
	}
	ft_access_1(ptr, str, env_v);
}
