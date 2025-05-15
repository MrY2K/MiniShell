/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajelloul <ajelloul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 09:28:31 by ajelloul          #+#    #+#             */
/*   Updated: 2025/05/13 11:09:07 by ajelloul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
** Ensures that PWD and OLDPWD environment variables exist
** @param info: Pointer to the minibash structure
*/

void	ensure_path_variables_exist(t_minibash *info)
{
	t_env	*env;
	bool	found_pwd;
	bool	found_oldpwd;

	if (!info)
		return ;
	found_pwd = false;
	found_oldpwd = false;
	env = info->env;
	while (env)
	{
		if (!ft_strcmp(env->name, "PWD"))
			found_pwd = true;
		if (!ft_strcmp(env->name, "OLDPWD"))
			found_oldpwd = true;
		env = env->next;
	}
	if (!found_pwd)
		add_node_to_env(&info->env, create_empty_env_node("PWD"));
	if (!found_oldpwd)
		add_node_to_env(&info->env, create_empty_env_node("OLDPWD"));
}

/*
** Updates the environment working directory variables
** @param type: Type of update (PWD or OLDPWD)
** @param info: Pointer to the minibash structure
*/
void	update_env_working_dir(t_env_type type, t_minibash *info)
{
	t_env	*env;
	char	buffer[PATH_MAX];
	char	*var_name;

	if (!info)
		return ;
	env = info->env;
	if (type == ENV_OLDPWD)
		var_name = "OLDPWD";
	else
		var_name = "PWD";
	ensure_path_variables_exist(info);
	if (!getcwd(buffer, PATH_MAX))
		return (exit_with_error("getcwd", 1, info));
	while (env)
	{
		if (!ft_strcmp(env->name, var_name))
		{
			free(env->value);
			env->value = ft_strdup(buffer);
			break ;
		}
		env = env->next;
	}
}

/*
** Built-in cd command implementation
** @param cmd: Command structure containing arguments
** @param info: Pointer to the minibash structure
** @return: Status of the command execution
*/
t_status	cd(t_cmd *cmd, t_minibash *info)
{
	char	*directory;

	if (!info)
		return (EXIT_FAILURE);
	update_env_working_dir(ENV_OLDPWD, info);
	if (!cmd->argument || (cmd->argument[0] && cmd->argument[0][0] == '~'))
	{
		directory = get_environment("HOME", info);
		if (!directory)
		{
			ft_putstr_fd("minishell: cd: HOME not set\n", 2);
			info->exit_status = 1;
			return (EXIT_FAILURE);
		}
	}
	else
		directory = ft_strdup(cmd->argument[0]);
	if (chdir(directory) != 0)
	{
		exit_with_error("minishell: cd", 1, info);
		return (free(directory), EXIT_FAILURE);
	}
	update_env_working_dir(ENV_PWD, info);
	info->exit_status = 0;
	return (free(directory), EXIT_SUCCESS);
}
