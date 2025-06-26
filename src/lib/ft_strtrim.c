/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achoukri <achoukri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 18:25:24 by achoukri          #+#    #+#             */
/*   Updated: 2025/04/24 10:21:25 by achoukri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	in_set(char c, char const *set);

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*new;
	size_t	i;
	size_t	j;

	if (s1 == NULL || set == NULL)
		return (NULL);
	i = 0;
	j = ft_strlen(s1);
	if (j == 0)
		return (ft_strdup(""));
	j--;
	while (in_set(s1[i], set) == 1)
		i++;
	while (j > i && in_set(s1[j], set) == 1)
		j--;
	if (j < i)
		return (ft_strdup(""));
	new = ft_calloc((j - i) + 2, sizeof(char));
	if (new == NULL)
		return (NULL);
	ft_memcpy(new, &s1[i], (j - i) + 1);
	return (new);
}

static int	in_set(char c, char const *set)
{
	size_t	i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}
/*
int main()
{
	char *s1 = "-+-+-+-Hellow+-+-+-";
	char *set = "-+";


	char *res = ft_strtrim(s1, set);
	
	printf("\nS1:            ::%s::\n", s1);
	printf("S2:            ::%s::\n", set);
	printf("RESAULT        ::%s::\n\n", res);
	
	free(res);
	return 0;
}
*/