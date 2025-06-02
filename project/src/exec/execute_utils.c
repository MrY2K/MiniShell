// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   execute_utils.c                                    :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: ajelloul <ajelloul@student.42.fr>          +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2025/05/22 15:44:10 by ajelloul          #+#    #+#             */
// /*   Updated: 2025/05/25 14:17:48 by ajelloul         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

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

// void	free_env(char **env)
// {
// 	int	i;

// 	if (!env)
// 		return ;
// 	i = 0;
// 	while (env[i])
// 	{
// 		free(env[i]);
// 		env[i] = NULL;
// 		i++;
// 	}
// 	free(env);
// }

// bool	has_pipes(t_cmd *cmd)
// {
// 	t_cmd	*cur;

// 	if (!cmd)
// 		return (false);
// 	cur = cmd;
// 	while (cur)
// 	{
// 		if (cur->pipe == 1)
// 			return (true);
// 		cur = cur->next;
// 	}
// 	return (false);
// }

// int	count_pipes(t_cmd *cmd)
// {
// 	t_cmd *cur;
// 	int	count;

// 	if (!cmd)
// 		return (0);
// 	cur = cmd;
// 	count = 0;
// 	while (cur)
// 	{
// 		if (cur->pipe == 1)
// 			count++;
// 		cur = cur->next;
// 	}
// 	return (count);
// }

// /* TODO :       Implement again   */

// static int	env_len(t_env *env)
// {
// 	int	len;

// 	len = 0;
// 	while (env)
// 	{
// 		len++;
// 		env = env->next;
// 	}
// 	return (len);
// }

// static char	*env_to_string(t_env *node)
// {
// 	char	*res;
// 	char	*equal;

// 	if (!node->name || !node->value)
// 		return (NULL);
// 	equal = ft_strjoin(node->name, "=");
// 	if (!equal)
// 		return (NULL);
// 	res = ft_strjoin(equal, node->value);
// 	free(equal);
// 	return (res);
// }

// char	**env_to_array(t_env *env)
// {
// 	char	**arr;
// 	int		i;

// 	arr = malloc(sizeof(char *) * (env_len(env) + 1));
// 	if (!arr)
// 		return (NULL);
// 	i = 0;
// 	while (env)
// 	{
// 		arr[i] = env_to_string(env);
// 		if (!arr[i])
// 		{
// 			while (i--)
// 				free(arr[i]);
// 			free(arr);
// 			return (NULL);
// 		}
// 		i++;
// 		env = env->next;
// 	}
// 	arr[i] = NULL;
// 	return (arr);
// }

// void	free_2d(char **array)
// {
// 	int	i;

// 	if (!array)
// 		return ;
// 	i = 0;
// 	while (array[i])
// 	{
// 		free(array[i]);
// 		i++;
// 	}
// 	free(array);
// }
