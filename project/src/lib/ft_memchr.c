/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achoukri <achoukri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 17:58:16 by achoukri          #+#    #+#             */
/*   Updated: 2025/04/24 10:23:52 by achoukri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*p_s;

	p_s = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		if (p_s[i] == (unsigned char)c)
			return (&p_s[i]);
		i++;
	}
	return (NULL);
}
/*
int main() {

	char data[] = "Helleow";
	char target = 'e';

	char *result = (char *)memchr(data, target, 3);

	if (result != NULL) 
		printf("OG:   Character '%c' found at position: %ld\n",
			 target, result - data);
	else 
		printf("OG:   Character '%c' not found\n", target);

	char data2[] = "Hellow";
	char target2 = 'e';

	char *result2 = (char *)ft_memchr(data2, target2, 3);

	if (result2 != NULL) 
		printf("MINE: Character '%c' found at position: %ld\n", 
			target2, result2 - data2);
	else 
		printf("MINE: Character '%c' not found\n", target2);

	return 0;
}
*/