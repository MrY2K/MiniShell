/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajelloul <ajelloul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 10:34:10 by ajelloul          #+#    #+#             */
/*   Updated: 2025/05/13 10:51:54 by ajelloul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
** Extracts the environment variable name from a "name=value" string
** @param str: Environment variable string in format "name=value"
** @return: Newly allocated string containing just the name portion
*/
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

/*
** Extracts the environment variable value from a "name=value" string
** @param str: Environment variable string in format "name=value"
** @return: Newly allocated string containing just the value portion
*/
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

/*
** Creates a new environment variable node
** @param data: Environment variable string in format "name=value"
** @return: Newly allocated environment node
*/
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

/*
** Creates an empty environment node with just the name no value
** @param name: Name of the environment variable
** @return: Newly allocated environment node
*/
t_env	*create_empty_env_node(const char *name)
{
	t_env	*new_node;

	if (!name)
		return (NULL);
	new_node = (t_env *)malloc(sizeof(t_env));
	if (!new_node)
		return (NULL);
	new_node->name = ft_strdup(name);
	new_node->value = ft_strdup("");
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

/*
** Adds a node to the environment linked list
** @param head: Pointer to the head of the environment list
** @param node: Node to be added to the list
*/
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
