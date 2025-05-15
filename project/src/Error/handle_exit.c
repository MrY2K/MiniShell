/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_exit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajelloul <ajelloul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 10:54:40 by ajelloul          #+#    #+#             */
/*   Updated: 2025/05/13 10:55:04 by ajelloul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
** Handles errors and sets the exit status
** @param msg: Error message to display
** @param exit_status: Exit status to set
** @param bash: Pointer to the minibash structure
*/
void	exit_with_error(const char *msg, int exit_status, t_minibash *bash)
{
	if (!bash)
		return ;
	bash->exit_status = exit_status;
	perror(msg);
}
