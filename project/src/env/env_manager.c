/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_manager.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajelloul <ajelloul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 10:43:22 by ajelloul          #+#    #+#             */
/*   Updated: 2025/05/13 11:09:26 by ajelloul         ###   ########.fr       */
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
