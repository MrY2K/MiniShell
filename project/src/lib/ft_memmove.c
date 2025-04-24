/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achoukri <achoukri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 19:02:07 by achoukri          #+#    #+#             */
/*   Updated: 2025/04/24 10:23:33 by achoukri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char		*p_d;
	unsigned const char	*p_s;
	size_t				i;

	if (dst == NULL && src == NULL)
		return (NULL);
	p_s = (unsigned const char *)src;
	p_d = (unsigned char *)dst;
	i = 0;
	if (p_s > p_d)
	{
		while (len > i)
		{
			p_d[i] = p_s[i];
			i++;
		}
	}
	else
	{
		while (len-- > 0)
			p_d[len] = p_s[len];
	}
	return (dst);
}

/*
int main(void)
{
	char s[] = "ABC";
	char *p_s = s;
	char *p_d = s+1;

	printf("\nOG:");
	printf("\n+++++++++++++++BEFORE++++++++++++++++\n");
	printf("|    '%c'    |    '%c'    |    '%c'    |\n", s[0], s[1], s[2]);
	printf("+++++++++++++++++++++++++++++++++++++\n");


	memmove(p_d, p_s, 2);

	printf("\n+++++++++++++++=AFTER=+++++++++++++++\n");
	printf("|    '%c'    |    '%c'    |    '%c'    |\n", s[0], s[1], s[2]);
	printf("+++++++++++++++++++++++++++++++++++++\n");


	char s2[] = "ABC";
	char *p_s2 = s2;
	char *p_d2 = s2+1;

	printf("\nMINE:");
	printf("\n+++++++++++++++BEFORE++++++++++++++++\n");
	printf("|    '%c'    |    '%c'    |    '%c'    |\n", s2[0], s2[1], s2[2]);
	printf("+++++++++++++++++++++++++++++++++++++\n");

	ft_memmove(p_d2, p_s2, 2);

	printf("\n+++++++++++++++=AFTER=+++++++++++++++\n");
	printf("|    '%c'    |    '%c'    |    '%c'    |\n", s2[0], s2[1], s2[2]);
	printf("+++++++++++++++++++++++++++++++++++++\n");

	return 0;
}
*/