/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_package.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajelloul <ajelloul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 09:34:18 by ajelloul          #+#    #+#             */
/*   Updated: 2025/05/24 12:17:10 by ajelloul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
** Handles errors and sets the exit status
** @param msg: Error message to display
** @param exit_status: Exit status to set
** @param bash: Pointer to the minibash structure
*/
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
/**
 * 	path.c
 * Prints error message and sets exit status for command errors
 * Centralizes error handling to eliminate code repetition
 * Handles different error types with appropriate exit codes
 */
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