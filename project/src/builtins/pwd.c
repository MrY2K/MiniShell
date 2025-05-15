/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajelloul <ajelloul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 09:50:57 by ajelloul          #+#    #+#             */
/*   Updated: 2025/05/15 10:19:42 by ajelloul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	pwd(t_minibash *bash)
{
	char	*current_dir;
	char	buffer[PATH_MAX];

	current_dir = getcwd(buffer, PATH_MAX);
	if (!current_dir)
		return (exit_with_error("getcwd", 1, bash));
	ft_putendl_fd(current_dir, 1);
	bash->exit_status = 0;
}
