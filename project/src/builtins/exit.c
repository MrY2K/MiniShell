/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajelloul <ajelloul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 10:43:58 by ajelloul          #+#    #+#             */
/*   Updated: 2025/05/15 12:04:40 by ajelloul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
	1) - If no arguments, Exit with the last known exit code stored in 
	2) - exit ++5
	
*/

// static	bool has_double_sign_prefix(char *arg)
// {
// 	return (arg[0] == '+' || arg[0] == '-') &&
// 	       (arg[1] == '+' || arg[1] == '-');
// }

// void	exit(t_cmd *cmd, t_minibash *bash)
// {

// 	if (!cmd->argument|| !cmd->argument[0])
// 		exit(bash->exit_status);
// 	if (has_double_sign_prefix(cmd->argument[0]))
// 	{
// 		ft_putendl_fd("minishell: exit: numeric argument required", 2);
// 		bash->exit_status = 255;
// 		exit (255);
// 	}


// }
