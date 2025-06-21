/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achoukri <achoukri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 18:13:15 by achoukri          #+#    #+#             */
/*   Updated: 2025/04/24 10:21:41 by achoukri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	if (little[0] == '\0')
		return ((char *)big);
	i = 0;
	while (i < len && big[i])
	{
		j = 0;
		while (big[i + j] == little[j]
			&& i + j < len && big[i] && little[j])
		{
			j++;
			if (little[j] == 0)
			{
				return ((char *)&big[i]);
			}
		}
		i++;
	}
	return (NULL);
}
/*
int main(void)
{
    char	*big	= "lorem";
    char	*little	= "lorem";
	size_t	look_whithin = 5;

	// use strnstr from string.h !!!
	char *match  = strnstr(big, little, look_whithin);
	printf("OG  :%s\n", match);

	char *match2 = ft_strnstr(big, little, look_whithin);
	printf("MINE:%s\n", match2);
}
*/