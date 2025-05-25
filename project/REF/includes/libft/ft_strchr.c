/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-mora <rel-mora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 11:50:54 by rel-mora          #+#    #+#             */
/*   Updated: 2024/01/10 18:01:34 by rel-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	d;
	int		i;

	d = (char) c;
	i = 0;
	while (s[i])
	{
		if (s[i] == d)
			return ((char *) s + i);
		i++;
	}
	if (d == '\0')
		return ((char *) s + i);
	return (NULL);
}
