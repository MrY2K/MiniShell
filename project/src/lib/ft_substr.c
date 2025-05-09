/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achoukri <achoukri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 16:54:20 by achoukri          #+#    #+#             */
/*   Updated: 2025/04/24 11:48:36 by achoukri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	real_len;
	char	*sub;

	if (s == NULL)
		return (NULL);
	if (start >= ft_strlen(s))
		return (ft_strdup(""));
	real_len = ft_strlen(s + start);
	if (real_len > len)
		real_len = len;
	sub = (char *)malloc(real_len + 1);
	if (sub == NULL)
		return (NULL);
	i = 0;
	while (i < real_len && s[start + i])
	{
		sub[i] = s[start + i];
		i++;
	}
	sub[i] = '\0';
	return (sub);
}
/*
int main()
{
	char *s = "0123456789";
	unsigned int start = 5;
	size_t len = 3;
	
	printf("S:        :   %s\n", s);
	printf("S_LEN     :   %lu\n", ft_strlen(s));
	printf("LEN TO SUB:   %lu\n", len);

	char *res = ft_substr(s,  start, len);
	printf("\nRESAULT   :  %s\n\n", res);

	return 0;
}
*/