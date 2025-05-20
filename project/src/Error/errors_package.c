/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_package.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajelloul <ajelloul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 09:34:18 by ajelloul          #+#    #+#             */
/*   Updated: 2025/05/20 16:18:23 by ajelloul         ###   ########.fr       */
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
