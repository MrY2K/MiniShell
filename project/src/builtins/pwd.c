/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajelloul <ajelloul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 09:50:57 by ajelloul          #+#    #+#             */
/*   Updated: 2025/06/15 16:34:09 by ajelloul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	builtin_pwd(t_minibash *bash, t_cmd *cmd)
{
	char	*current_dir;

	current_dir = getcwd(NULL, 0);
	if (!current_dir)
		return (exit_with_error("getcwd", 1, bash));
	if (cmd->argument[1] && cmd->argument[1][0] == '-'
		&& cmd->argument[1][1] != '\0')
	{
		print_cmd_err(bash, "pwd", "invalid option", 1);
		free(current_dir);
		return ;
	}
	ft_putendl_fd(current_dir, 1);
	free(current_dir);
	bash->exit_status = 0;
}
