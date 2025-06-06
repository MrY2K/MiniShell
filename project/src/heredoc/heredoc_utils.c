/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajelloul <ajelloul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 10:59:30 by ajelloul          #+#    #+#             */
/*   Updated: 2025/06/03 09:45:21 by ajelloul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	num_of_herdoc(t_cmd *cmd)
{
	t_cmd		*tmp;
	t_heredoc	*herdoc;
	int			i;

	if (!cmd)
		return (0);
	tmp = cmd;
	i = 0;
	while (tmp)
	{
		herdoc = tmp->heredoc;
		if (herdoc)
		{
			while (herdoc)
			{
				if (herdoc->delimiter)
					i++;
				herdoc = herdoc->next;
			}
			tmp = tmp->next;
		}
		else
			tmp = tmp->next;
	}
	return (i);
}

bool	has_herdoc(t_cmd *cmd)
{
	t_cmd	*cur;
	int		i;

	if (!cmd)
		return (false);
	cur = cmd;
	i = num_of_herdoc(cur);
	if (i)
		return (true);
	else
		return (false);
}

char	*ft_strjoin_with_null(char *s1, char *s2)
{
	char	*joined;
	size_t	len1;
	size_t	len2;

	if (!s2)
		return (NULL);
	if (!s1)
	{
		s1 = ft_calloc(1, sizeof(char));
		if (!s1)
			return (NULL);
	}
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	joined = malloc(len1 + len2 + 1);
	if (!joined)
		return (NULL);
	ft_memcpy(joined, s1, len1);
	ft_memcpy(joined + len1, s2, len2);
	joined[len1 + len2] = '\0';
	return (joined);
}
