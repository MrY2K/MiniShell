/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajelloul <ajelloul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 10:16:33 by ajelloul          #+#    #+#             */
/*   Updated: 2025/06/26 17:03:05 by ajelloul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	builtin_env(t_minibash *bash, t_env **env)
{
	t_env	*_env;

	if (!bash || !env)
		return ;
	_env = *env;
	while (_env)
	{
		if (_env->value && !_env->value[0])
			printf("%s=\n", _env->name);
		else if (_env->value)
			printf("%s=%s\n", _env->name, _env->value);
		_env = _env->next;
	}
	bash->exit_status = 0;
}
