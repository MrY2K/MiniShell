/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achoukri <achoukri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 19:02:43 by achoukri          #+#    #+#             */
/*   Updated: 2025/04/24 10:23:26 by achoukri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*ptr;

	i = 0;
	ptr = s;
	while (i < n)
	{
		ptr[i] = (unsigned char)c;
		i++;
	}
	return (s);
}
/*
int main()
{
	char *s = (char *)malloc(8);
	
	ft_memset(s, 48, 5);

	int i = 0; 
	while (i < 7)
	{
		printf("%c", s[i]);
		i++;
	}
	printf("\n");

	free(s);

	return 0;
}
*/