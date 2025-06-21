/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achoukri <achoukri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 06:55:52 by ajelloul          #+#    #+#             */
/*   Updated: 2025/06/21 02:23:59 by achoukri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*extract_variable_name(char *str)
{
	char	*var_name;
	int		len;

	len = 0;
	while (str[len] && str[len] != '=')
		len++;
	var_name = (char *)malloc(sizeof(char) * (len + 1));
	if (!var_name)
		return (NULL);
	len = 0;
	while (str[len] && str[len] != '=')
	{
		var_name[len] = str[len];
		len++;
	}
	var_name[len] = 0;
	return (var_name);
}

char	**split_var_value_pair(char *str)
{
	char	**new;
	char	*equals_pos;

	new = (char **)malloc(sizeof(char *) * 3);
	if (!new)
		return (NULL);
	if (is_contains_char(str, '='))
	{
		new[0] = extract_variable_name(str);
		equals_pos = ft_strchr(str, '=');
		if (equals_pos)
			new[1] = ft_strdup(equals_pos + 1);
		else
			new[1] = NULL;
	}
	else
	{
		new[0] = ft_strdup(str);
		new[1] = NULL;
	}
	new[2] = NULL;
	return (new);
}

int	is_valid_variable_name(t_minibash *bash, char *str)
{
	int	i;

	if (!str)
		return (1);
	i = 0;
	if (str[i] == '=' || ft_isdigit(str[0]) || str[i] == '\0')
	{
		export_error(bash, str);
		return (1);
	}
	while (str[i] && str[i] != '=')
	{
		if (!is_allowed_variable_character(str[i]))
		{
			export_error(bash, str);
			return (1);
		}
		i++;
	}
	return (0);
}

int	init_empty_env(t_minibash *bash, t_env **env, t_cmd *cmd)
{
	t_export_parser	expo;

	if (*env)
		return (0);
	if (!cmd->argument[1] || cmd->argument[1][0] == '\0')
	{
		if (cmd->argument[1] != NULL && cmd->argument[1][0] == '\0')
		{
			export_error(bash, cmd->argument[1]);
		}
		return (1);
	}
	if (is_valid_variable_name(bash, cmd->argument[1]))
		return (1);
	expo.list = split_var_value_pair(cmd->argument[1]);
	expo.name = ft_strdup(expo.list[0]);
	if (expo.list[1])
		expo.value = ft_strdup(expo.list[1]);
	expo.env_node = create_new_node(expo.name, expo.value);
	add_node_to_env(env, expo.env_node);
	free_2d(expo.list);
	return (0);
}

/*
	export VAR1=hello VAR2=world VAR3=test
	ila faild foot  export var1=valid 2var=invalid var3=valid
*/

void	builtin_export(t_minibash *bash, t_env **env, t_cmd *cmd)
{
	int	i;

	if (!*env)
	{
		if (init_empty_env(bash, env, cmd))
			return ;
	}
	i = 1;
	while (cmd->argument[i])
	{
		if (is_valid_variable_name(bash, cmd->argument[i]))
			i++;
		else
			process_export_args(env, cmd, &i);
	}
	export(cmd->argument, *env);
}
