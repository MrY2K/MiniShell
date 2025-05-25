/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-mora <rel-mora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 02:12:25 by rel-mora          #+#    #+#             */
/*   Updated: 2024/09/23 16:30:07 by rel-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	size_t	i;
	char	*src;
	size_t	total_size;

	total_size = count * size;
	src = malloc(total_size);
	if (src == NULL)
		return (NULL);
	i = 0;
	while (i < total_size)
	{
		src[i] = '\0';
		i++;
	}
	return (src);
}
