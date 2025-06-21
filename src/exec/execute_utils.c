/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achoukri <achoukri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 15:44:10 by ajelloul          #+#    #+#             */
/*   Updated: 2025/06/21 02:49:04 by achoukri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	search(const char *str, const char *to_find)
{
	int	i;
	int	j;

	if (!str || !to_find)
		return (0);
	if (to_find[0] == '\0')
		return (1);
	i = 0;
	while (str[i])
	{
		j = 0;
		while (str[i + j] && to_find[j] && str[i + j] == to_find[j])
			j++;
		if (to_find[j] == '\0')
			return (1);
		i++;
	}
	return (0);
}

int	is_fork_succes(t_minibash *bash, int pid)
{
	if (pid == -1)
	{
		perror("minishell");
		bash->exit_status = 1;
		return (0);
	}
	return (1);
}

bool	has_redirections(t_cmd *cmd)
{
	t_redirect	*red;

	if (!cmd)
		return (false);
	red = cmd->red;
	while (red)
	{
		if (red->type == TOKEN_REDIR_APPEND || red->type == TOKEN_REDIR_IN
			|| red->type == TOKEN_REDIR_OUT)
			return (true);
		red = red->next;
	}
	return (false);
}

bool	has_pipes(t_cmd *cmd)
{
	t_cmd	*cur;

	if (!cmd)
		return (false);
	cur = cmd;
	while (cur)
	{
		if (cur->pipe == 1)
			return (true);
		cur = cur->next;
	}
	return (false);
}

int	count_pipes(t_cmd *cmd)
{
	t_cmd	*cur;
	int		count;

	if (!cmd)
		return (0);
	cur = cmd;
	count = 0;
	while (cur)
	{
		if (cur->pipe == 1)
			count++;
		cur = cur->next;
	}
	return (count);
}
