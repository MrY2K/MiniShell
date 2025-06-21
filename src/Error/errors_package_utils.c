/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_package_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achoukri <achoukri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 12:52:07 by ajelloul          #+#    #+#             */
/*   Updated: 2025/06/21 20:29:34 by achoukri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	cd_error(t_minibash *bash)
{
	perror("minishell: cd");
	bash->exit_status = 1;
}

void	execute_error(t_minibash *bash, char *msg)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putendl_fd(msg, 2);
	bash->exit_status = 127;
}

void	redirection_error(t_minibash *bash)
{
	ft_putstr_fd("minishell: No such file or directory\n", 2);
	bash->exit_status = 1;
	exit(1);
}
