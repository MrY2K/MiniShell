/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achoukri <achoukri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 17:13:44 by achoukri          #+#    #+#             */
/*   Updated: 2025/04/24 10:22:24 by achoukri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	size_t	i;
	char	tmp;

	tmp = (char)c;
	i = 0;
	while (s[i])
	{
		if (s[i] == tmp)
		{
			return ((char *)&s[i]);
		}
		i++;
	}
	if (s[i] == tmp)
		return ((char *)&s[i]);
	return (NULL);
}
/*
int main()
{
	char *s1 = "HelWlow";
	// char *s2 = "HelWlo";	
	// char *s3 = "W";
	// char *s4 = "WaassW";
	// char *s5 = "";
	// char *s6 = "Wasawasa";
	
	char c = 'W';
	
	//printf(":    %s\n\n", ft_strchr(s1, c));

	printf("Expect: %s\nGot:    %s\n\n", strchr(s1, c), ft_strchr(s1, c));
// 	printf("Expect: %s\nGot:    %s\n\n", strchr(s2, c), ft_strchr(s2, c));
// 	printf("Expect: %s\nGot:    %s\n\n", strchr(s3, c), ft_strchr(s3, c));
// 	printf("Expect: %s\nGot:    %s\n\n", strchr(s4, c), ft_strchr(s4, c));
// 	printf("Expect: %s\nGot:    %s\n\n", strchr(s5, c), ft_strchr(s5, c));
// 	printf("Expect: %s\nGot:    %s\n\n", strchr(s6, c), ft_strchr(s6, c));

	return 0;
}
*/