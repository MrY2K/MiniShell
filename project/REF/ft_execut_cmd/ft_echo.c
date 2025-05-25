/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bouhammo <bouhammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 09:06:30 by bouhammo          #+#    #+#             */
/*   Updated: 2024/10/06 12:58:11 by bouhammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	complet_function(t_command *list, int k, bool flag)
{
	while (list->arg[k])
	{
		ft_putstr_fd(list->arg[k], 1);
		if (list->arg[k + 1] != NULL)
			ft_putstr_fd(" ", 1);
		k++;
	}
	if (!flag || k == 1)
		ft_putstr_fd("\n", 1);
}

void	ft_echo(t_command *list)
{
	int		k;
	bool	flag;
	int		i;

	k = 1;
	flag = false;
	while (list->arg[k])
	{
		if (list->arg[k][0] == '-' && list->arg[k][1] != '\0')
		{
			i = 1;
			while (list->arg[k][i] == 'n')
				i++;
			if (list->arg[k][i] != '\0')
				break ;
			flag = true;
		}
		else
			break ;
		k++;
	}
	complet_function(list, k, flag);
	g_exit_status = 0;
}

void	print_error_exit(char *ptr, int ext)
{
	ft_putstr_fd(ptr, 2);
	exit(ext);
}
