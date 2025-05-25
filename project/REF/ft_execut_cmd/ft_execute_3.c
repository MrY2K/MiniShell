/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute_3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bouhammo <bouhammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 18:02:52 by bouhammo          #+#    #+#             */
/*   Updated: 2024/09/28 13:13:45 by bouhammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	built_in_exist(t_command *list)
{
	if (list == NULL)
		return (0);
	if (ft_strcmp(list->content, "exit") == 0)
		return (1);
	if (ft_strcmp(list->content, "cd") == 0)
		return (1);
	if (ft_strcmp(list->content, "pwd") == 0)
		return (1);
	if (ft_strcmp(list->content, "export") == 0)
		return (1);
	if (ft_strcmp(list->content, "unset") == 0)
		return (1);
	if (ft_strcmp(list->content, "env") == 0)
		return (1);
	if (ft_strcmp(list->content, "echo") == 0)
		return (1);
	return (0);
}

void	built_in(t_environment **var, t_command *list)
{
	if (list == NULL)
		return ;
	if (ft_strcmp(list->content, "exit") == 0)
		(ft_exit(var, list));
	if (ft_strcmp(list->content, "cd") == 0)
		(ft_cd(var, list));
	if (ft_strcmp(list->content, "pwd") == 0)
		(ft_pwd(list));
	if (ft_strcmp(list->content, "export") == 0)
	{
		(ft_export(var, list));
	}
	if (ft_strcmp(list->content, "unset") == 0)
		(ft_unset(var, list));
	if (ft_strcmp(list->content, "env") == 0)
		(ft_env(var));
	if (ft_strcmp(list->content, "echo") == 0)
	{
		(ft_echo(list));
	}
}

int	ft_str_eqal(char *ptr, char c)
{
	int	i;

	i = 0;
	while (ptr[i])
	{
		if (ptr[i] == c)
			return (1);
		i++;
	}
	return (0);
}

void	delet_files(t_command *cmd)
{
	t_delet	del;

	del.tmp = cmd;
	while (del.tmp != NULL)
	{
		del.her = del.tmp->her;
		while (del.her != NULL)
		{
			del.itoa = ft_itoa(del.her->idx);
			del.ptr = ft_strjoin_1(del.her->store, del.itoa);
			free(ft_itoa(del.her->idx));
			del.file = ft_join("/tmp/herdoc", del.ptr);
			free(del.ptr);
			if (unlink(del.file) != 0)
			{
				g_exit_status = 1;
				perror("");
			}
			free(del.file);
			del.her = del.her->next;
			free(del.itoa);
		}
		del.tmp = del.tmp->next;
	}
}
