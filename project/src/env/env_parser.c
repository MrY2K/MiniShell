/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajelloul <ajelloul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 11:23:33 by ajelloul          #+#    #+#             */
/*   Updated: 2025/06/11 09:47:37 by ajelloul         ###   ########.fr       */
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


void initialize_environment(t_minibash *info, char **env)
{
    int     i;
    t_env   *new_node;

    if (!info || !env)
        return;
    i = 0;
    while (env[i])
    {
        new_node = create_env_node(env[i]);
        if (new_node)
            add_node_to_env(&info->env, new_node);
        i++;
    }
}


// /*
// ** Creates an empty environment node with just the name no value
// ** @param name: Name of the environment variable
// ** @return: Newly allocated environment node
// */
// t_env	*create_empty_env_node(char *name)
// {
// 	t_env	*new_node;

// 	if (!name)
// 		return (NULL);
// 	new_node = (t_env *)malloc(sizeof(t_env));
// 	if (!new_node)
// 		return (NULL);
// 	new_node->name = ft_strdup(name);
// 	new_node->value = ft_strdup("");
// 	new_node->next = NULL;
// 	if (!new_node->name || !new_node->value)
// 	{
// 		free(new_node->name);
// 		free(new_node->value);
// 		free(new_node);
// 		return (NULL);
// 	}
// 	return (new_node);
// }



//  ✅   ✅   ✅    second edition ✅  ✅ ✅   ✅ 


char **convert_env_list_to_array(t_env **env)
{
    t_env_converter conv;
    t_env 			*current;
    int 			i;

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

char	*get_environment_variable(char	**env, char *path)
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