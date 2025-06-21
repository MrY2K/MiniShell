/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achoukri <achoukri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 22:48:27 by achoukri          #+#    #+#             */
/*   Updated: 2025/06/21 04:23:20 by achoukri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	unsigned int	i;

	if (s == NULL || f == NULL)
		return ;
	i = 0;
	while (s[i])
	{
		f(i, &s[i]);
		i++;
	}
}
/*
void	func(unsigned int i, char *c)
{
	(void)i;
	*c = ft_toupper(*c);
}
int main()
{
	char str[] = "ayoub fjfj wwww llll";
	ft_striteri(str, func);
	printf("Modifade array: %s\n", str);
	return 0;
}
*/