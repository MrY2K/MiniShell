/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-mora <rel-mora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 19:41:28 by rel-mora          #+#    #+#             */
/*   Updated: 2024/01/10 18:01:17 by rel-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*s_one;
	unsigned char	*s_two;
	size_t			i;

	s_one = (unsigned char *) s1;
	s_two = (unsigned char *) s2;
	i = 0;
	if (n == 0)
		return (0);
	while (i < n - 1)
	{
		if (s_one[i] == s_two[i])
			i++;
		else
			break ;
	}
	return (s_one[i] - s_two[i]);
}
