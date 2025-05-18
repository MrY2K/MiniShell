/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achoukri <achoukri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 10:40:45 by achoukri          #+#    #+#             */
/*   Updated: 2025/05/18 02:47:33 by achoukri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "lib/libft.h"


#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
// #include "/goinfre/achoukri/homebrew/opt/readline/include/readline/readline.h"

void	ll(void) { system("leaks -q minishell"); }


int	main(void)
{
	char	*line;

	while (1)
	{
		line = readline("minishell$ ");
		if (!line)  /* Ctrl-D: readline returns NULL */
		{
			rl_clear_history();
			ft_error_msg("exit\n");
		}
		if (ft_strlen(line) > 0)
				add_history(line);
		/* tokeniz and parser here… */
		free(line);
	}

	return (0);
}
