/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajelloul <ajelloul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 09:28:31 by ajelloul          #+#    #+#             */
/*   Updated: 2025/05/20 16:05:58 by ajelloul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
** Ensures that PWD and OLDPWD environment variables exist
** @param info: Pointer to the minibash structure
*/

void	ensure_path_variables_exist(t_minibash *bash)
{
	t_env	*env;
	bool	found_pwd;
	bool	found_oldpwd;

	if (!bash)
		return ;
	found_pwd = false;
	found_oldpwd = false;
	env = bash->env;
	while (env)
	{
		if (!ft_strcmp(env->name, "PWD"))
			found_pwd = true;
		if (!ft_strcmp(env->name, "OLDPWD"))
			found_oldpwd = true;
		env = env->next;
	}
	if (!found_pwd)
		add_node_to_env(&bash->env, create_empty_env_node("PWD"));
	if (!found_oldpwd)
		add_node_to_env(&bash->env, create_empty_env_node("OLDPWD"));
}

/*
** Updates the environment working directory variables
** @param type: Type of update (PWD or OLDPWD)
** @param info: Pointer to the minibash structure
*/
void	update_env_working_dir(t_env_type type, t_minibash *bash)
{
	t_env	*env;
	char	buffer[PATH_MAX];
	char	*var_name;

	if (!bash)
		return ;
	env = bash->env;
	if (type == ENV_OLDPWD)
		var_name = "OLDPWD";
	else
		var_name = "PWD";
	ensure_path_variables_exist(bash);
	if (!getcwd(buffer, PATH_MAX))
		return (exit_with_error("getcwd", 1, bash));
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
** @param bash: Pointer to the minibash structure
** @return: Status of the command execution
*/
t_status	cd(t_cmd *cmd, t_minibash *bash)
{
	char	*directory;

	if (!bash)
		return (EXIT_FAILURE);
	update_env_working_dir(ENV_OLDPWD, bash);
	if (!cmd->argument || (cmd->argument[0] && cmd->argument[0][0] == '~'))
	{
		directory = get_environment("HOME", bash);
		if (!directory)
		{
			ft_putstr_fd("minishell: cd: HOME not set\n", 2);
			bash->exit_status = 1;
			return (EXIT_FAILURE);
		}
	}
	else
		directory = ft_strdup(cmd->argument[0]);
	if (chdir(directory) != 0)
	{
		exit_with_error("minishell: cd", 1, bash);
		return (free(directory), EXIT_FAILURE);
	}
	update_env_working_dir(ENV_PWD, bash);
	bash->exit_status = 0;
	return (free(directory), EXIT_SUCCESS);
}
