/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bouhammo <bouhammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 12:22:56 by bouhammo          #+#    #+#             */
/*   Updated: 2024/10/06 12:48:59 by bouhammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	execution_cmd(t_environment **var, t_command *list, char **new)
{
	char	*ptr;
	char	**array;

	if (list == NULL || new == NULL || new[0] == NULL)
		return ;
	array = array_env(var);
	if (new[0][0] == '/')
		ptr = new[0];
	else
		ptr = path_command(new[0], array);
	if (!ptr)
	{
		ft_putstr_fd("minishell: command not found\n", 2);
		g_exit_status = 127;
		exit(127);
	}
	ft_access(ptr, new, array);
	if (execve(ptr, new, array) == -1)
	{
		free_args(array);
		ft_putstr_fd("minishell: command not found\n", 2);
		free(ptr);
		g_exit_status = 127;
		exit(127);
	}
}

void	run_simple_cmd(t_command *list, t_environment **var)
{
	if (test_redir(list) == 1)
	{
		hundle_redirections(list);
		built_in(var, list);
	}
	if (built_in_exist(list) == 0)
	{
		execution_cmd(var, list, list->arg);
	}
}

int	file_not_valid(t_command *list)
{
	t_command	*tmp;

	if (list == NULL)
		return (0);
	tmp = list;
	while (tmp->doc)
	{
		if (tmp->doc->type == DREDIR_OUT)
		{
			if (open(tmp->doc->store, O_WRONLY | O_CREAT | O_APPEND, 0644) < 0)
				return (1);
		}
		if (tmp->doc->type == REDIR_OUT)
		{
			if (open(tmp->doc->store, O_WRONLY | O_CREAT | O_TRUNC, 0644) < 0)
				return (1);
		}
		if (tmp->doc->type == REDIR_IN)
		{
			if (open(tmp->doc->store, O_RDONLY, 0644) < 0)
				return (1);
		}
		tmp->doc = tmp->doc->next;
	}
	return (0);
}

void	ft_built_in(t_environment **var, t_command *list)
{
	if (test_redir(list) == 1)
	{
		if (file_not_valid(list) == 1)
			return ;
	}
	if (list->arg[1] != NULL)
		built_in(var, list);
	if (ft_strcmp("cd", list->content) == 0 && list->arg[1] == NULL)
		built_in(var, list);
	if (ft_strcmp("exit", list->content) == 0 && list->arg[1] == NULL)
		built_in(var, list);
	return ;
}

int	run_herdoc_built(t_environment **var, t_command *cmd)
{
	t_command	*list;

	list = cmd;
	if (list == NULL)
		return (0);
	if (herdoc_exist(list) == 1)
	{
		if (handle_here_doc(var, list) == true)
			return (-1);
		if (built_in_exist(list) == 1 && !pipe_exist(list) && !test_redir(list))
		{
			built_in(var, list);
			return (1);
		}
	}
	if (built_in_exist(list) == 1 && pipe_exist(list) == 0
		&& herdoc_exist(list) == 0 && test_redir(list) == 0)
	{
		built_in(var, list);
		return (1);
	}
	else if (built_in_exist(list) == 1 && pipe_exist(list) == 0
		&& ft_check_built(list) == 1)
		ft_built_in(var, list);
	return (0);
}
