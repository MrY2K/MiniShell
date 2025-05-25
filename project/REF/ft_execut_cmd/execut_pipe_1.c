/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execut_pipe_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bouhammo <bouhammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 12:38:50 by bouhammo          #+#    #+#             */
/*   Updated: 2024/09/26 15:44:49 by bouhammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	pipe_exist(t_command *list)
{
	t_command	*tmp;

	if (list == NULL)
		return (0);
	tmp = list;
	while (tmp)
	{
		if (tmp->is_pipe == 1)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

int	num_pipe(t_command *list)
{
	t_command	*tmp;
	int			i;

	tmp = list;
	i = 0;
	while (tmp)
	{
		if (tmp->is_pipe == 1)
			i++;
		tmp = tmp->next;
	}
	return (i);
}

int	**return_pipe(int num_cmd)
{
	int	**pipe;
	int	i;

	pipe = (int **)malloc(sizeof(int *) * num_cmd);
	if (!pipe)
	{
		perror("malloc");
		g_exit_status = 1;
		exit(EXIT_FAILURE);
	}
	i = 0;
	while (i < num_cmd)
	{
		pipe[i] = (int *)malloc(sizeof(int) * 2);
		if (!pipe[i])
		{
			perror("malloc");
			while (i > 0)
				free(pipe[i--]);
			g_exit_status = 1;
			exit(EXIT_FAILURE);
		}
		i++;
	}
	return (pipe);
}

void	free_pid_pipe(int *pids, int **pipefd, int num_cmd)
{
	int	i;

	i = 0;
	if (pipefd != NULL)
	{
		while (i < num_cmd)
		{
			free(pipefd[i]);
			pipefd[i] = NULL;
			i++;
		}
		free(pipefd);
		pipefd = NULL;
	}
	if (pids != NULL)
	{
		free(pids);
		pids = NULL;
	}
}
