/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achoukri <achoukri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 19:02:21 by achoukri          #+#    #+#             */
/*   Updated: 2025/04/24 10:24:44 by achoukri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isascii(int c)
{
	if (c >= 0 && c <= 127)
		return (1);
	return (0);
}
/*
int main(void)
{
	char c = 0;
	
	if (ft_isascii((unsigned char) c))
	{
		printf("Your input is an ascii char.\n");
	}
	else
	{
		printf("Your input is not an ascii char.\n");
	}

	return 0;
}
*/