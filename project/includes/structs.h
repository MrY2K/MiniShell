/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achoukri <achoukri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 09:25:15 by ajelloul          #+#    #+#             */
/*   Updated: 2025/05/17 19:51:52 by achoukri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

// # include "minishell.h"

typedef struct s_cmd
{
	char	*main_cmd;
	char	**argument;
}	t_cmd;

typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_minibash
{
	t_env	*env;
	int		exit_status;
}	t_minibash;

#endif
