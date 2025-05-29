/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajelloul <ajelloul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 06:55:52 by ajelloul          #+#    #+#             */
/*   Updated: 2025/05/21 10:13:46 by ajelloul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
	* In shell scripting, the export command is used to make 
		shell variables available to child processes;
	
	* What export Does:
		* By default, variables in a shell script are local to the current shell.
		* When you export a variable, it becomes an environment variable,
			meaning it is inherited by any child processes 

*/

/*
	* the difference between a shell and a subshell :
		* A shell is a command-line interface that allows users to interact with
			the operating system by executing commands. It interprets user input
			and communicates with the kernel to perform tasks.(shells include Bash Zsh).
		
		* A subshell is a child process created by the shell to execute commands
			in a separate environment. It inherits the environment of the parent shell
			but can have its own variables and settings
*/

/*	In shell syntax, the # symbol starts a comment	*/

void	display_exported_variable(t_minibash *bash)
{
	t_env	*env;

	env = bash->env;
	while (env)
	{
		if (!env->value)
			printf("declare -x %s\n", env->name);
		else if (env->name && env->value)
		{
			ft_putstr("declare -x ");
			ft_putstr(env->name);
			ft_putstr("=\"");
			ft_putstr(env->value);
			ft_putendl_fd("\"", 1);
		}
		env = env->next;
	}
	bash->exit_status = 0;
}

static bool	is_valide_env_identifier(t_minibash *bash, char *args)
{
	int	i;

	if (!args || !args[0])
		return (export_error(bash, ""), false);
	if (args[0] == '=')
		return (export_error(bash, args), false);
	if (!ft_isalpha(args[0]) && args[0] != '_')
		return (export_error(bash, args), false);
	i = 0;
	while (args[i] && args[i] != '=')
	{
		if (!ft_isalnum(args[i]) && args[i] != '_')
			return (export_error(bash, args), false);
		i++;
	}
	return (true);
}

static bool	update_existing_variable(t_minibash *bash, char *name, char *value)
{
	t_env	*env;

	env = bash->env;
	while (env)
	{
		if (!ft_strcmp(env->name, name))
		{
			if (value)
			{
				free(env->value);
				env->value = ft_strdup(value);
			}
			return (true);
		}
		env = env->next;
	}
	return (false);
}

static void	export_env_variable(t_minibash *bash, t_cmd *cmd)
{
	char	*name;
	char	*value;
	int		u;

	u = -1;
	while (cmd->argument[++u])
	{
		if (!is_valide_env_identifier(bash, cmd->argument[u]))
			continue ;
		name = extract_env_name(cmd->argument[u]);
		value = extract_env_value(cmd->argument[u]);
		if (!name)
		{
			free(value);
			continue ;
		}
		if (!update_existing_variable(bash, name, value))
			add_node_to_env(&bash->env, create_env_node(cmd->argument[u]));
		free(name);
		free(value);
	}
}

void	export(t_minibash *bash, t_cmd *cmd)
{
	if (!cmd->argument || !cmd->argument[0] || cmd->argument[0][0] == '#')
		display_exported_variable(bash);
	else 
		export_env_variable(bash, cmd);
}
