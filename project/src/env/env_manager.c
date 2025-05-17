/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_manager.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajelloul <ajelloul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 10:43:22 by ajelloul          #+#    #+#             */
/*   Updated: 2025/05/17 12:43:03 by ajelloul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
** Retrieves the value of a specific environment variable
** @param name: Name of the environment variable to find
** @param bash: Pointer to the minibash structure
** @return: Value of the environment variable or NULL if not found
*/
char	*get_environment(const char *name, t_minibash *bash)
{
	t_env	*env;

	if (!name || !bash)
		return (NULL);
	env = bash->env;
	while (env)
	{
		if (!ft_strcmp(env->name, name))
			return (ft_strdup(env->value));
		env = env->next;
	}
	return (NULL);
}

/*
** Initializes the environment list from the environment array
** @param info: Pointer to the minibash structure
** @param env: Array of environment strings
*/
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

void	free_environment_node(t_env **node)
{
	free ((*node)->name);
	free ((*node)->value);
	(*node)->name = NULL;
	(*node)->value = NULL;
	free (*node);
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
