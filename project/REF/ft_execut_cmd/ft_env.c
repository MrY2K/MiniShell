/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bouhammo <bouhammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 19:19:49 by bouhammo          #+#    #+#             */
/*   Updated: 2024/10/04 23:18:37 by bouhammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_env(t_environment **var)
{
	t_environment	*ptr;

	if (var == NULL || *var == NULL)
		return ;
	ptr = *var;
	while (ptr != NULL)
	{
		if (ptr->data != NULL && ptr->data[0] == '\0')
		{
			printf("%s=\n", ptr->var);
		}
		else if (ptr->data != NULL)
		{
			printf("%s=%s\n", ptr->var, ptr->data);
		}
		ptr = ptr->next;
	}
	return ;
}

int	count_herdoc(t_command *tmp)
{
	int			count;
	t_command	*cmd;
	t_here_doc	*her;

	cmd = tmp;
	count = 0;
	if (tmp == NULL)
		return (0);
	while (cmd != NULL)
	{
		her = cmd->her;
		if (her != NULL)
		{
			while (her != NULL)
			{
				if (her->store != NULL)
					count++;
				her = her->next;
			}
			cmd = cmd->next;
		}
		else
			cmd = cmd->next;
	}
	return (count);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	if (!s1 || !s2)
		return (-1);
	i = 0;
	while ((s1[i] && s2[i]) && (s1[i] == s2[i]))
	{
		i++;
	}
	return (s1[i] - s2[i]);
}

char	*ft_getenv(char *path, char **env)
{
	int	i;

	i = 0;
	if (path == NULL || *env == NULL || env == NULL)
		return (NULL);
	while (env[i] != NULL)
	{
		if (ft_strncmp(env[i], path, ft_strlen(path)) == 0
			&& path[ft_strlen(path)] == '\0')
		{
			return (ft_strchr(env[i], '=') + 1);
		}
		i++;
	}
	return (NULL);
}
