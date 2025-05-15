/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajelloul <ajelloul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 10:40:45 by achoukri          #+#    #+#             */
/*   Updated: 2025/05/11 13:10:30 by ajelloul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int argc, char **argv)
{
	t_cmd	cmd;

	if (argc < 2)
		return (1);

	cmd.man_cmd = argv[1]; 
	cmd.argument = &argv[2];   // Skip the command name, pass the rest & 

	if (ft_strncmp(cmd.man_cmd, "echo", 4) == 0)
		echo(&cmd);
	else
		write (1, "tzzz", 5);
	return (0);
}
