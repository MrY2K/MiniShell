/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achoukri <achoukri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 19:02:47 by achoukri          #+#    #+#             */
/*   Updated: 2025/04/24 10:21:53 by achoukri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}
/*
int main(void)
{
	char *str = "NULL";

	printf("EXPECTING:\n");
	printf("%lu\n\n", strlen(str));

	printf("GOT:\n");
	printf("%zu\n", ft_strlen(str));

	return 0;
}
*/