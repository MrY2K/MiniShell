/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajelloul <ajelloul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 10:22:36 by ajelloul          #+#    #+#             */
/*   Updated: 2025/06/17 12:23:19 by ajelloul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
	first character (true)  → must be a letter or underscore

	first character (false)  → can be letter  / digit or underscore
*/

static bool	is_valid_shell_variable(char c, bool first_char)
{
	if (first_char)
		return (ft_isalpha(c) || c == '_');
	return (ft_isalnum(c) || c == '_');
}
/*
	not valid  : VAR!X   VAR$1
*/

static bool	is_valid_var_name(t_minibash *bash, char *variable)
{
	int	i;

	i = 1;
	while (variable[i])
	{
		if (!is_valid_shell_variable(variable[i], false))
		{
			bash->exit_status = 1;
			ft_putstr_fd("minishell: unset: `", 2);
			ft_putstr_fd(variable, 2);
			ft_putendl_fd("': not a valid identifier", 2);
			return (false);
		}
		i++;
	}
	return (true);
}

/*
	CASE 1 :
		unset ""  ,   unset " "
	
	CASE 2 :
		check the first char -> unset  1_var
	
	return : check the midelle

*/

static bool	is_valid_unset_variable(t_minibash *bash, char *variable)
{
	if (!variable || !variable[0])
	{
		bash->exit_status = 1;
		ft_putendl_fd("minishell: unset: `': not a valid identifier", 2);
		return (false);
	}
	if (!is_valid_shell_variable(variable[0], true))
	{
		bash->exit_status = 1;
		ft_putstr_fd("minishell: unset: `", 2);
		ft_putstr_fd(variable, 2);
		ft_putendl_fd("': not a valid identifier", 2);
		return (false);
	}
	return (is_valid_var_name(bash, variable));
}

/* unset is used to remove variables from the environment */

/*
	TEST
		:	unset  _  valid   1_invalid  _  _valid 

	CASE 1 :
		unset _    ->  Skipped

	CASE 2 :
		Show error  ->  Skip removal -> Go to next argument  continue

	CASE 3 :
		It's not _
		It's a valid name
*/

void	builtin_unset(t_minibash *bash, char **args, t_env **env)
{
	int	i;

	i = 1;
	while (args[i])
	{
		if (!ft_strcmp(args[i], "_"))
		{
			i++;
			continue ;
		}
		if (!is_valid_unset_variable(bash, args[i]))
		{
			i++;
			continue ;
		}
		remove_env_variable(env, args[i]);
		i++;
	}
	bash->exit_status = 0;
}
