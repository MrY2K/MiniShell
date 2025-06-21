/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_core.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajelloul <ajelloul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 10:17:14 by ajelloul          #+#    #+#             */
/*   Updated: 2025/06/16 10:31:37 by ajelloul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	display_export(t_env *env)
{
	t_env	*current;

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
	if (!args || !args[0])
		return ;
	if (ft_strcmp(args[0], "export") == 0 && args[1] == NULL)
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
		if (node[0] && !ft_strcmp(node[0], tmp_env->name))
		{
			if (node[1] && !ft_strcmp(node[1], tmp_env->value))
				return (1337);
			else
			{
				if (node[1] == NULL)
					return (1337);
				free(tmp_env->value);
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
	t_export_parser	expo;
	int				update_status;

	expo.list = split_var_value_pair(cmd->argument[*i]);
	update_status = update_if_variable_exists(env, expo.list);
	if (update_status == 1337)
		(*i)++;
	else if (update_status == 0)
	{
		expo.name = ft_strdup(expo.list[0]);
		expo.value = NULL;
		if (expo.list[1])
			expo.value = ft_strdup(expo.list[1]);
		expo.env_node = create_new_node(expo.name, expo.value);
		add_node_to_env(env, expo.env_node);
		(*i)++;
	}
	free_2d(expo.list);
}
