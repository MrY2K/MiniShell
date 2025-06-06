/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achoukri <achoukri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 10:16:33 by ajelloul          #+#    #+#             */
/*   Updated: 2025/06/06 16:47:12 by achoukri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	env(t_minibash *bash)
{
	t_env	*_env;

	if (!bash || !bash->env)
		return ;
	_env = bash->env;
	while (_env)
	{
		if (_env->name && _env->value)
			printf("%s=%s\n", _env->name, _env->value);
		_env = _env->next;
	}
	bash->exit_status = 0;
}
