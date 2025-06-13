/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_manager.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajelloul <ajelloul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 10:43:22 by ajelloul          #+#    #+#             */
/*   Updated: 2025/06/13 12:27:43 by ajelloul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	get_environment_len(t_env *env)
{
	t_env	*cur;
	int		counter;

	if (!env)
		return (0);
	counter = 0;
	cur = env;
	while (cur)
	{
		counter++;
		cur = cur->next;
	}
	return (counter);
}

char	*create_env_entry(t_env_converter *conv, t_env *node)
{
	char	*entry;

	conv->tmp_name = ft_strdup(node->name);
	conv->tmp_block = ft_strjoin(node->name, "=");
	if (node->value)
	{
		conv->tmp_value = ft_strdup(node->value);
		entry = ft_strjoin(conv->tmp_block, conv->tmp_value);
		free(conv->tmp_value);
	}
	else
		entry = ft_strdup(conv->tmp_block);
	free(conv->tmp_name);
	free(conv->tmp_block);
	return (entry);
}

t_env	*find_env_variable(t_env *env, char *old)
{
	if (!env || !old)
		return (NULL);
	while (env)
	{
		if (!ft_strcmp(old, env->name))
			return (env);
		env = env->next;
	}
	return (NULL);
}

void	update_env_var(t_env **env, char **arr_env, char *path, char *old)
{
	t_env	*old_pwd;
	t_env	*pwd;

	old_pwd = find_env_variable(*env, old);
	if (old_pwd)
	{
		free(old_pwd->value);
		old_pwd->value = NULL;
		if (get_environment_variable(arr_env, "PWD"))
			old_pwd->value
				= ft_strdup(get_environment_variable(arr_env, "PWD"));
	}
	pwd = find_env_variable(*env, "PWD");
	if (pwd)
	{
		free(pwd->value);
		pwd->value = NULL;
		path = getcwd(NULL, 0);
		if (path)
		{
			pwd->value = ft_strdup(path);
			free(path);
		}
	}
}

void	free_env_arr(char **arr_env)
{
	int	i;

	if (arr_env == NULL)
		return ;
	i = 0;
	while (arr_env[i])
	{
		free(arr_env[i]);
		arr_env[i] = NULL;
		i++;
	}
	free(arr_env);
	arr_env = NULL;
}
