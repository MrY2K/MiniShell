/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajelloul <ajelloul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 12:25:39 by ajelloul          #+#    #+#             */
/*   Updated: 2025/06/13 12:27:05 by ajelloul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**convert_env_list_to_array(t_env **env)
{
	t_env_converter	conv;
	t_env			*current;
	int				i;

	if (!env)
		return (NULL);
	current = *env;
	conv.len = get_environment_len(*env);
	conv.env_array = (char **)malloc(sizeof(char *) * (conv.len + 1));
	if (!conv.env_array)
		return (NULL);
	i = 0;
	while (i < conv.len)
	{
		conv.env_array[i] = create_env_entry(&conv, current);
		current = current->next;
		i++;
	}
	conv.env_array[i] = NULL;
	return (conv.env_array);
}

char	*get_environment_variable(char **env, char *path)
{
	int	i;
	int	path_len;

	if (!env || !*env || !path)
		return (NULL);
	i = 0;
	path_len = ft_strlen(path);
	while (env[i])
	{
		if (!ft_strncmp(env[i], path, path_len) && env[i][path_len] == '=')
			return (ft_strchr(env[i], '=') + 1);
		i++;
	}
	return (NULL);
}

void	free_environment_node(t_env **node)
{
	free((*node)->name);
	free((*node)->value);
	(*node)->name = NULL;
	(*node)->value = NULL;
	free(*node);
	*node = NULL;
}

/* Node is at the beginning of the list */
void	remove_env_variable(t_env **env, char *var)
{
	t_env	*cur;
	t_env	*prev;

	cur = *env;
	prev = NULL;
	while (cur && ft_strcmp(var, cur->name))
	{
		prev = cur;
		cur = cur->next;
	}
	if (cur)
	{
		if (!prev)
			*env = cur->next;
		else if (cur->next)
			prev->next = cur->next;
		else
			prev->next = NULL;
		free_environment_node(&cur);
	}
}
