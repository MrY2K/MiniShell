/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bouhammo <bouhammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 19:20:01 by bouhammo          #+#    #+#             */
/*   Updated: 2024/10/06 14:09:04 by bouhammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_pwd(t_command *list)
{
	char	*path;

	path = getcwd(NULL, 0);
	if (path == NULL)
	{
		perror("");
		g_exit_status = 1;
		return ;
	}
	if (list->arg[1] != NULL && list->arg[1][0] == '-'
		&& list->arg[1][1] != '\0')
	{
		ft_putstr_fd("pwd", 2);
		ft_putstr_fd(": invalid option\n", 2);
		g_exit_status = 1;
		return ;
	}
	ft_putstr_fd(path, 1);
	ft_putchar_fd('\n', 1);
	free(path);
	g_exit_status = 0;
}

t_environment	*find_env(t_environment *my_var, char *old)
{
	if (my_var == NULL || old == NULL)
		return (NULL);
	while (my_var)
	{
		if (ft_strcmp(my_var->var, old) == 0)
			return (my_var);
		my_var = my_var->next;
	}
	return (NULL);
}

void	printf_error_cd(char *s, int exit)
{
	ft_putstr_fd(s, 2);
	ft_putchar_fd('\n', 2);
	g_exit_status = exit;
}

int	herdoc_exist(t_command *list)
{
	t_command	*tmp;
	int			count;

	if (list == NULL)
		return (0);
	count = 0;
	tmp = list;
	count = count_herdoc(tmp);
	if (count != 0)
		return (1);
	else
		return (0);
}

void	sig_herdoc(int sig)
{
	(void)sig;
	printf("\n");
	exit(130);
}
