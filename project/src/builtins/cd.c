/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achoukri <achoukri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 09:28:31 by ajelloul          #+#    #+#             */
/*   Updated: 2025/06/13 20:13:31 by achoukri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	handle_tilde_expansion(t_minibash *bash, char **env,
		char *path, char *arg)
{
	char	*home_path;
	char	*final_path;

	home_path = get_environment_variable(env, "HOME");
	if (arg[1] == '/')
	{
		final_path = ft_strjoin(home_path, ft_strchr(arg, '/'));
		path = final_path;
	}
	else
		path = home_path;
	if (!path)
		print_cmd_err(bash, "cd", "HOME not set", 1);
	else if (chdir(path) == -1)
		exit_with_error("cd", 1, bash);
	if (arg[1] == '/' && final_path)
		free(final_path);
}

void	handle_special_paths(t_minibash *bash, char **env, char *dir_path)
{
	bash->exit_status = 0;
	if (dir_path[0] == '-' && !dir_path[1])
	{
		dir_path = get_environment_variable(env, "OLDPWD");
		if (!dir_path)
			print_cmd_err(bash, "cd", "OLDPWD not set", 1);
		if (chdir(dir_path) == -1)
			print_cmd_err(bash, "cd", strerror(errno), 1);
		else
			printf("%s\n", dir_path);
	}
	else if (!ft_strcmp(dir_path, "--"))
	{
		dir_path = get_environment_variable(env, "HOME");
		if (!dir_path)
			print_cmd_err(bash, "cd", "HOME not set", 1);
		if (chdir(dir_path) == -1)
			print_cmd_err(bash, "cd", strerror(errno), 1);
	}
	else if (chdir(dir_path) == -1)
		print_cmd_err(bash, "cd", strerror(errno), 1);
}

void	builtin_cd(t_minibash *bash, t_env **env, t_cmd *cmd)
{
	t_cd	cd;

	cmd = NULL;
	cd.arr_env = convert_env_list_to_array(env);
    cd.user_arg = cmd->argument[1];
	if (!cmd->argument[1] || cmd->argument[1][0] == 0)
	{
		cd.path = get_environment_variable(cd.arr_env, "HOME");
		if (!cd.path)
			print_cmd_err(bash, "cd", "HOME not set", 1);
		else if (chdir(cd.path) == -1)
			exit_with_error("cd", 1, bash);
	}
	else
	{
		cd.path = cmd->argument[1];
		if (cd.path[0] == '~')
			handle_tilde_expansion(bash, cd.arr_env, cd.path, cmd->argument[1]);
		else
			handle_special_paths(bash, cd.arr_env, cd.path);
	}
	update_env_var(env, cd.arr_env, cd.user_arg, "OLDPWD");
	free_env_arr(cd.arr_env);
}
