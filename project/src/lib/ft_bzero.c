/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achoukri <achoukri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 19:02:14 by achoukri          #+#    #+#             */
/*   Updated: 2025/04/24 10:26:23 by achoukri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	size_t			i;
	unsigned char	*ptr;

	ptr = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		ptr[i] = 0;
		i++;
	}
}

/*
int main(void)
{
	char s[] = "Hellow";
	
	printf("BEFORE:\n");
	for (int i = 0; i < 7; i++) {
		printf("%c", s[i]);
	}
	printf("\n");

	ft_bzero(s, 7);

	printf("AFTER:\n");
	for (int i = 0; i < 7; i++) {
		printf("%c", s[i]);
	}
	printf("\n");

	char s2[] = "Hellow";

	printf("EXPECTED - BEFORE:\n");
	for (int i = 0; i < 7; i++) {
		printf("%c", s2[i]);
	}
	printf("\n");

	bzero(s2, 7);

	printf("EXPEXTED - AFTER:\n");
	for (int i = 0; i < 7; i++) {
		printf("%c", s2[i]);
	}
	printf("\n");

	return 0;
}
*/