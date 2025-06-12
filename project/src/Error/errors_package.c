/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_package.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achoukri <achoukri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 09:34:18 by ajelloul          #+#    #+#             */
/*   Updated: 2025/06/12 23:51:29 by achoukri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	exit_with_error(const char *msg, int exit, t_minibash *bash)
{
	if (!bash)
		return ;
	bash->exit_status = exit;
	perror(msg);
}

void	export_error(t_minibash *bash, char *content)
{
	ft_putstr_fd("minishell: export: `", 2);
	ft_putstr_fd(content, 2);
	ft_putendl_fd("`: not a valid identifier", 2);
	bash->exit_status = 1;
}

void	print_cmd_err(t_minibash *bash, char *cmd, char *msg, int exit)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(msg, 2);
	bash->exit_status = exit;
}

void	display_errno_exit(char *msg, int status)
{
	ft_putendl_fd(msg, 2);
	exit(status);
}

void	display_ambiguous_errno(t_minibash *bash, int exit_st)
{
	ft_putendl_fd("minishell: ambiguous redirect", 2);
	bash->exit_status = exit_st;
	exit(exit_st);
}
