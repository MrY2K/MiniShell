/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-mora <rel-mora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 17:32:34 by rel-mora          #+#    #+#             */
/*   Updated: 2024/01/10 18:01:12 by rel-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*src;
	unsigned char	d;
	size_t			i;

	d = (unsigned char ) c;
	i = 0;
	src = (unsigned char *) s;
	while (i < n)
	{
		if (src[i] == d)
			return ((void *)src + i);
		i++;
	}
	return (NULL);
}
