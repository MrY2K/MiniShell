/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-mora <reduno96@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/24 19:40:57 by rel-mora          #+#    #+#             */
/*   Updated: 2024/08/12 21:13:33 by rel-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isset(char const *set, char c)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	if (!s1 || !set)
		return (NULL);
	while (s1[i] && ft_isset(set, s1[i]))
		i++;
	j = ft_strlen(s1) - 1;
	while (j > i && ft_isset(set, s1[j]))
		j--;
	k = j - i + 1;
	return (ft_substr(s1, i, k));
}
