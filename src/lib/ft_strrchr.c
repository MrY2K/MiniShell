/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achoukri <achoukri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 17:13:42 by achoukri          #+#    #+#             */
/*   Updated: 2025/04/24 10:21:37 by achoukri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		len;
	char	tmp;

	tmp = (char)c;
	len = ft_strlen(s);
	while (len >= 0)
	{
		if (s[len] == tmp)
			return ((char *)&s[len]);
		len--;
	}
	return (NULL);
}
/*
int main()
{
	char *s1 = "HelloW";
	char *s2 = "HelWlo";
	char *s3 = "W";
	char *s4 = "WaassW";
	char *s5 = "Wasawasa";
	char *s6 = "";

	char c = 'l';

	printf("Expect: %s\nGot:    %s\n\n", strrchr(s1, c), ft_strrchr(s1, c));
	printf("Expect: %s\nGot:    %s\n\n", strrchr(s2, c), ft_strrchr(s2, c));
	printf("Expect: %s\nGot:    %s\n\n", strrchr(s3, c), ft_strrchr(s3, c));
	printf("Expect: %s\nGot:    %s\n\n", strrchr(s4, c), ft_strrchr(s4, c));
	printf("Expect: %s\nGot:    %s\n\n", strrchr(s5, c), ft_strrchr(s5, c));
	printf("Expect: %s\nGot:    %s\n\n", strrchr(s6, c), ft_strrchr(s6, c));

	return 0;
}
*/