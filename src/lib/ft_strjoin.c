/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achoukri <achoukri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 17:56:08 by achoukri          #+#    #+#             */
/*   Updated: 2025/04/24 10:22:11 by achoukri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	s1_len;
	size_t	s2_len;
	char	*new;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	new = (char *)malloc(s1_len + s2_len + 1);
	if (new == NULL)
		return (NULL);
	ft_memcpy(new, s1, s1_len);
	ft_memcpy(&new[s1_len], s2, s2_len);
	new[s1_len + s2_len] = '\0';
	return (new);
}
/*
int main()
{
	char *s1 = "Hi ";
	char *s2 = "There!";

	printf("S1:            ::%s::\n", s1);
	printf("S2:            ::%s::\n", s2);

	char *res = ft_strjoin(s1, s2);

	printf("\nRESAULT        ::%s::\n\n", res);

	free(res);
	return 0;
}
*/