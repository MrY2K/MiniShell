/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajelloul <ajelloul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 15:44:10 by ajelloul          #+#    #+#             */
/*   Updated: 2025/05/24 10:14:03 by ajelloul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

void	free_env(char **env)
{
	int	i;

	if (!env)
		return ;
	i = 0;
	while (env[i])
	{
		free(env[i]);
		env[i] = NULL;
		i++;
	}
	free(env);
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
	t_cmd *cur;
	int	count;

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
