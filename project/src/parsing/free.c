/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achoukri <achoukri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 02:06:41 by achoukri          #+#    #+#             */
/*   Updated: 2025/06/21 02:30:43 by achoukri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/structs.h"

void	free_argument_array(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return ;
	while (arr[i])
	{
		free(arr[i]);
		arr[i] = NULL;
		i++;
	}
	free(arr);
	arr = NULL;
}

void	ft_free_doc(t_redirect **doc)
{
	t_redirect	*tmp;

	while (*doc != NULL)
	{
		tmp = *doc;
		*doc = (*doc)->next;
		if (tmp->file_path != NULL)
		{
			free(tmp->file_path);
			tmp->file_path = NULL;
		}
		free(tmp);
		tmp = NULL;
	}
}

void	ft_free_her(t_heredoc **her)
{
	t_heredoc	*tmp;

	while (*her != NULL)
	{
		tmp = *her;
		*her = (*her)->next;
		if (tmp->her_file != NULL)
		{
			free(tmp->her_file);
			tmp->her_file = NULL;
		}
		if (tmp->delimiter != NULL)
		{
			free(tmp->delimiter);
			tmp->delimiter = NULL;
		}
		free(tmp);
		tmp = NULL;
	}
}

void	free_cmd_list(t_cmd **cmd)
{
	t_cmd	*tmp_cmd;
	t_cmd	*next_cmd;

	if (cmd == NULL || *cmd == NULL)
		return ;
	tmp_cmd = *cmd;
	while (tmp_cmd)
	{
		free_argument_array(tmp_cmd->argument);
		if (tmp_cmd->red)
			ft_free_doc(&tmp_cmd->red);
		if (tmp_cmd->heredoc)
			ft_free_her(&tmp_cmd->heredoc);
		if (tmp_cmd->env_arr)
			free_argument_array(tmp_cmd->env_arr);
		next_cmd = tmp_cmd->next;
		free(tmp_cmd);
		tmp_cmd = NULL;
		tmp_cmd = next_cmd;
	}
}
