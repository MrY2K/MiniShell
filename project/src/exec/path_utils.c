/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajelloul <ajelloul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 11:13:02 by ajelloul          #+#    #+#             */
/*   Updated: 2025/06/16 13:56:17 by ajelloul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_env_variable(char *name, char **env)
{
	int		i;
	int		name_len;
	char	*equal_pos;

	if (!name || !env)
		return (NULL);
	name_len = ft_strlen(name);
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], name, name_len) == 0)
		{
			equal_pos = ft_strchr(env[i], '=');
			if (equal_pos && env[i][name_len] == '=')
				return (equal_pos + 1);
		}
		i++;
	}
	return (NULL);
}
