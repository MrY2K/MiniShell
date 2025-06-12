/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_core.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajelloul <ajelloul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 10:17:14 by ajelloul          #+#    #+#             */
/*   Updated: 2025/06/10 11:36:29 by ajelloul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	display_export(t_env *env)
{
    t_env   *current;

    if (!env)
        return ;
    current = env;
    while (current)
    {
        if (!current->value)
            printf("declare -x %s\n", current->name);
        else
            printf("declare -x %s=\"%s\"\n", current->name, current->value);
        current = current->next;
    }
}

void	export(char **args, t_env *env)
{
    int     count;
    int     i;

    count = 0;
    i = 0;
    while (args[i] != NULL)
    {
        count++;
        i++;
    }
    if (count == 1 && ft_strcmp(args[0], "export") == 0)
        display_export(env);
}


static int	update_if_variable_exists(t_env **env, char **node)
{
	t_env	*tmp_env;

	if (!env || !*env)
		return (1);
	tmp_env = *env;
	while (tmp_env)
	{
		if (node[0] && !ft_strcmp(node[0], tmp_env->name)) // variable name matches current node
		{
			if (node[1] && !ft_strcmp(node[1], tmp_env->value))// If value is the same do nothing
				return (1337);
			else
			{
				if (node[1] == NULL)
					return (1337);
				free (tmp_env->value);
				tmp_env->value = ft_strdup(node[1]);
				return (1337);
			}
		}
		tmp_env = tmp_env->next;
	}
	return (0);
}

void	process_export_args(t_env **env, t_cmd *cmd, int *i)
{
	// char	*name;
	// char	*value;
	// char	**node;
	t_export_parser	expo;

	expo.list = split_var_value_pair(cmd->argument[*i]);
	if (update_if_variable_exists(env, expo.list) == 1337) // we found it 
		(*i)++;
	else if (!update_if_variable_exists(env, expo.list)) // The variable does not exist yet → we need to add it.
	{
		expo.name = ft_strdup(expo.list[0]);
		if (expo.list[1])
			expo.value = ft_strdup(expo.list[1]);
		expo.env_node = create_new_node(expo.name, expo.value);
		add_node_to_env(env, expo.env_node);
		(*i)++;
	}
	free_2d(expo.list);
}
