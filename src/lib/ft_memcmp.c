/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achoukri <achoukri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 00:12:48 by achoukri          #+#    #+#             */
/*   Updated: 2025/04/24 10:23:47 by achoukri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t				i;
	const unsigned char	*p_s1;
	const unsigned char	*p_s2;

	p_s1 = (const unsigned char *)s1;
	p_s2 = (const unsigned char *)s2;
	i = 0;
	while (i < n)
	{
		if (p_s1[i] != p_s2[i])
			return (p_s1[i] - p_s2[i]);
		i++;
	}
	return (0);
}
/*
int main()
{
	int s1[] = {1, 2, 3, 9, 5};
	int s2[] = {1, 2, 3, 4, 5};
	int n = sizeof(int)*5;
	int res = ft_memcmp(s1, s2, n);
	int res2 = memcmp(s1, s2, n);
	printf("\nMINE: %d\n", res);
	printf("\nOG  : %d\n\n", res2);
	return 0;
}
*/