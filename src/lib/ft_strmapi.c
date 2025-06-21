/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achoukri <achoukri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 21:15:05 by achoukri          #+#    #+#             */
/*   Updated: 2025/06/21 04:23:38 by achoukri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	char			*final;
	size_t			len;

	if (s == NULL || f == NULL)
		return (NULL);
	len = ft_strlen(s);
	final = malloc((len + 1) * (sizeof(char)));
	if (final == NULL)
		return (NULL);
	i = 0;
	while (i < len)
	{
		final[i] = f(i, s[i]);
		i++;
	}
	final[i] = '\0';
	return (final);
}
/*
char	func(unsigned int i, char c)
{
	(void)i;
	return(ft_toupper(c));
}
int main()
{
	char *s = "abc ayoub aabbaabbabab yeah";
	char * res = ft_strmapi(s, func);
	printf("Original           :%s\n", s);
	printf("New Modifide string:%s\n", res);
}
*/