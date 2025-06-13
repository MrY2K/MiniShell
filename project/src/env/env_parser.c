/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achoukri <achoukri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 11:23:33 by ajelloul          #+#    #+#             */
/*   Updated: 2025/06/13 20:05:05 by achoukri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*extract_env_name(const char *str)
{
	char	*new;
	int		i;

	if (!str)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	new = (char *)malloc(sizeof(char) * (i + 1));
	if (!new)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '=')
	{
		new[i] = str[i];
		i++;
	}
	new[i] = '\0';
	return (new);
}

char	*extract_env_value(const char *str)
{
	char	*value_ptr;

	if (!str)
		return (NULL);
	value_ptr = ft_strchr(str, '=');
	if (!value_ptr)
		return (ft_strdup(""));
	return (ft_strdup(value_ptr + 1));
}

t_env	*create_env_node(char *data)
{
	t_env	*new_node;

	if (!data)
		return (NULL);
	new_node = (t_env *)malloc(sizeof(t_env));
	if (!new_node)
		return (NULL);
	new_node->name = extract_env_name(data);
	new_node->value = extract_env_value(data);
	new_node->next = NULL;
	if (!new_node->name || !new_node->value)
	{
		free(new_node->name);
		free(new_node->value);
		free(new_node);
		return (NULL);
	}
	return (new_node);
}

void	add_node_to_env(t_env **head, t_env *node)
{
	t_env	*tmp;

	if (!head || !node)
		return ;
	if (!*head)
	{
		*head = node;
		return ;
	}
	tmp = *head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = node;
}

void	initialize_environment(t_minibash *info, char **env)
{
	int		i;
	t_env	*new_node;

	if (!info || !env)
		return ;
	i = 0;
	while (env[i])
	{
		new_node = create_env_node(env[i]);
		if (new_node)
			add_node_to_env(&info->env, new_node);
		i++;
	}
}
