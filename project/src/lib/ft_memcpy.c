/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achoukri <achoukri@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 19:02:28 by achoukri          #+#    #+#             */
/*   Updated: 2024/10/23 19:02:28 by achoukri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t				i;
	unsigned char		*d;
	unsigned const char	*s;

	if (src == NULL && dest == NULL)
		return (NULL);
	d = (unsigned char *)dest;
	s = (unsigned const char *)src;
	i = 0;
	while (i < n)
	{
		d[i] = s[i];
		i++;
	}
	return (dest);
}

/*
int main(void)
{
	char s[] = "Hellow";
	char d[7];

	printf("\n");
	printf("Before: \n");
	for (int i = 0; s[i]; i++)
	{
		printf("%c", s[i]);
	}
	printf("\n");

	for (int i = 0; d[i] != '\0'; i++)
	{
		printf("%c", d[i]);
	}
	printf("\n");
	printf("------------------------------------ \n");

	memcpy(d, s, 7);

	printf("OG: \n");
	for (int i = 0; s[i] != '\0'; i++)
	{
		printf("%c", s[i]);
	}
	printf("\n");

	for (int i = 0; d[i] != '\0'; i++)
	{
		printf("%c", d[i]);
	}
	printf("\n");
	printf("------------------------------------ \n");

	ft_memcpy(d, s, 7);

	printf("MINE: \n");
	for (int i = 0; s[i] != '\0'; i++)
	{
		printf("%c", s[i]);
	}
	printf("\n");

	for (int i = 0; d[i] != '\0'; i++)
	{
		printf("%c", d[i]);
	}
	printf("\n");
	printf("------------------------------------ \n");

	return 0;
}
*/