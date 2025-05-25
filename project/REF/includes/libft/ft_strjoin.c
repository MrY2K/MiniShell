/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-mora <rel-mora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 18:48:18 by rel-mora          #+#    #+#             */
/*   Updated: 2024/09/25 12:15:00 by rel-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_allocation_null(char **s1, char **s2)
{
	if (!*s1)
	{
		*s1 = ft_calloc(1, sizeof(char));
		*s1[0] = '\0';
	}
	if (!*s2)
	{
		*s2 = ft_calloc(1, sizeof(char));
		*s2[0] = '\0';
	}
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*str_final;
	int		i;
	int		j;

	i = 0;
	j = 0;
	ft_allocation_null(&s1, &s2);
	if (!s2 || !s1)
		return (NULL);
	str_final = ft_calloc((ft_strlen(s1) + ft_strlen(s2)) + 1, sizeof(char));
	if (str_final == NULL)
		return (NULL);
	while (s1[j])
		str_final[i++] = s1[j++];
	j = 0;
	while (s2[j])
		str_final[i++] = s2[j++];
	str_final[i] = '\0';
	free(s1);
	s1 = NULL;
	return (str_final);
}
