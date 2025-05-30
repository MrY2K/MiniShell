// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   unset.c                                            :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: ajelloul <ajelloul@student.42.fr>          +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2025/05/17 10:22:36 by ajelloul          #+#    #+#             */
// /*   Updated: 2025/05/19 07:39:15 by ajelloul         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "../../includes/minishell.h"

// /**
//  * Check if a character is valid for a variable name
//  * In bash, variable names can contain letters, numbers, and underscores
//  * The first character must be a letter or an underscore
//  */
// static bool	is_valid_shell_variable(char c, bool st_char)
// {
// 	if (st_char)
// 		return (ft_isalpha(c) || c == '_');
// 	return (ft_isalnum(c) || c == '_');
// }

// /**
//  * Check if a variable name is valid for unset
//  * According to bash, a valid identifier  of letters, digits, and underscores
//  * and cannot begin with a digit.
//  * The special variable '_' is handled differently - bash allows it to be unset
//  * but it doesn't actually remove it.
//  */
// static bool	is_valid_var_name(t_minibash *bash, char *variable)
// {
// 	int	i;

// 	i = 1;
// 	while (variable[i])
// 	{
// 		if (!is_valid_shell_variable(variable[i], false))
// 		{
// 			bash->exit_status = 1;
// 			ft_putstr_fd("minishell: unset: `", 2);
// 			ft_putstr_fd(variable, 2);
// 			ft_putendl_fd("': not a valid identifier", 2);
// 			return (false);
// 		}
// 		i++;
// 	}
// 	return (true);
// }

// static bool	is_valid_unset_variable(t_minibash *bash, char *variable)
// {
// 	if (!variable || !variable[0])
// 	{
// 		bash->exit_status = 1;
// 		ft_putendl_fd("minishell: unset: `': not a valid identifier", 2);
// 		return (false);
// 	}
// 	if (!is_valid_shell_variable(variable[0], true))
// 	{
// 		bash->exit_status = 1;
// 		ft_putstr_fd("minishell: unset: `", 2);
// 		ft_putstr_fd(variable, 2);
// 		ft_putendl_fd("': not a valid identifier", 2);
// 		return (false);
// 	}
// 	return (is_valid_var_name(bash, variable));
// }

// /* Special handling for exactly '_' variable */

// void	unset(t_minibash *bash, char **args)
// {
// 	int	i;

// 	i = 0;
// 	while (args[i++])
// 	{
// 		if (!ft_strcmp(args[i], "_"))
// 			continue ;
// 		if (!is_valid_unset_variable(bash, args[i]))
// 			continue ;
// 		remove_env_variable(&bash->env, args[i]);
// 		i++;
// 	}
// 	bash->exit_status = 0;
// }
