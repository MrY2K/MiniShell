/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajelloul <ajelloul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 06:55:52 by ajelloul          #+#    #+#             */
/*   Updated: 2025/06/09 12:50:06 by ajelloul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// /*
// 	* In shell scripting, the export command is used to make 
// 		shell variables available to child processes;
	
// 	* What export Does:
// 		* By default, variables in a shell script are local to the current shell.
// 		* When you export a variable, it becomes an environment variable,
// 			meaning it is inherited by any child processes 

// */

// /*
// 	* the difference between a shell and a subshell :
// 		* A shell is a command-line interface that allows users to interact with
// 			the operating system by executing commands. It interprets user input
// 			and communicates with the kernel to perform tasks.(shells include Bash Zsh).
		
// 		* A subshell is a child process created by the shell to execute commands
// 			in a separate environment. It inherits the environment of the parent shell
// 			but can have its own variables and settings
// */

// /*	In shell syntax, the # symbol starts a comment	*/

// void	display_exported_variable(t_minibash *bash)
// {
// 	t_env	*env;

// 	env = bash->env;
// 	while (env)
// 	{
// 		if (!env->value)
// 			printf("declare -x %s\n", env->name);
// 		else if (env->name && env->value)
// 		{
// 			ft_putstr("declare -x ");
// 			ft_putstr(env->name);
// 			ft_putstr("=\"");
// 			ft_putstr(env->value);
// 			ft_putendl_fd("\"", 1);
// 		}
// 		env = env->next;
// 	}
// 	bash->exit_status = 0;
// }

// static bool	is_valide_env_identifier(t_minibash *bash, char *args)
// {
// 	int	i;

// 	if (!args || !args[0])
// 		return (export_error(bash, ""), false);
// 	if (args[0] == '=')
// 		return (export_error(bash, args), false);
// 	if (!ft_isalpha(args[0]) && args[0] != '_')
// 		return (export_error(bash, args), false);
// 	i = 0;
// 	while (args[i] && args[i] != '=')
// 	{
// 		if (!ft_isalnum(args[i]) && args[i] != '_')
// 			return (export_error(bash, args), false);
// 		i++;
// 	}
// 	return (true);
// }

// static bool	update_existing_variable(t_minibash *bash, char *name, char *value)
// {
// 	t_env	*env;

// 	env = bash->env;
// 	while (env)
// 	{
// 		if (!ft_strcmp(env->name, name))
// 		{
// 			if (value)
// 			{
// 				free(env->value);
// 				env->value = ft_strdup(value);
// 			}
// 			return (true);
// 		}
// 		env = env->next;
// 	}
// 	return (false);
// }

// static void	export_env_variable(t_minibash *bash, t_cmd *cmd)
// {
// 	char	*name;
// 	char	*value;
// 	int		u;

// 	u = -1;
// 	while (cmd->argument[++u])
// 	{
// 		if (!is_valide_env_identifier(bash, cmd->argument[u]))
// 			continue ;
// 		name = extract_env_name(cmd->argument[u]);
// 		value = extract_env_value(cmd->argument[u]);
// 		if (!name)
// 		{
// 			free(value);
// 			continue ;
// 		}
// 		if (!update_existing_variable(bash, name, value))
// 			add_node_to_env(&bash->env, create_env_node(cmd->argument[u]));
// 		free(name);
// 		free(value);
// 	}
// }

// void	export(t_minibash *bash, t_cmd *cmd)
// {
// 	if (!cmd->argument || !cmd->argument[0] || cmd->argument[0][0] == '#')
// 		display_exported_variable(bash);
// 	else 
// 		export_env_variable(bash, cmd);
// }


char	*extract_variable_name(char *str)
{
	char	*var_name;
	int		len;

	len = 0;
	while (str[len] && str[len] != '=')
		len++;
	var_name = (char *)malloc(sizeof(char) * (len + 1)); // ++len len ++ linkedin post
	if (!str)
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

char	**split_var_value_pair(char	*str) // split this export VAR=value
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


int	is_valid_variable_name(t_minibash *bash, char *str) // chaeck is valid 
{
	int	i;

	if (!str)
		return (1);
	i = 0;
	if (str[i] == '=' || ft_isdigit(str[0]) || str[i] == '\0') // =  =VAR  42var 
	{
		export_error(bash, str);
		return (1);
	}
	while (str[i])
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
	if (!cmd->argument[1] || cmd->argument[1][0] == '\0') // export  export ""
	{
		if (cmd->argument[1] != NULL && cmd->argument[1][0] == '\0') // export ""
			export_error(bash, cmd->argument[1]);
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

void	builtin_export(t_minibash *bash, t_env **env, t_cmd *cmd)
{
	int	i;

	if (init_empty_env(bash, env, cmd))
		return ;
	i = 1;
	while (cmd->argument[i]) // export VAR1=hello VAR2=world VAR3=test
	{
		if (is_valid_variable_name(bash, cmd->argument[i])) // ila faild foot  export var1=valid 2var=invalid var3=valid
			i++;

		// else 
		
	}
	
}
