/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achoukri <achoukri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 19:02:23 by achoukri          #+#    #+#             */
/*   Updated: 2025/04/24 10:24:40 by achoukri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
	{
		return (1);
	}
	else
		return (0);
}
/*
int main(void)
{
	char c = '9';
	
	if (ft_isdigit((unsigned char) c))
	{
		printf("Your input is a Digit.\n");
	}
	else
	{
		printf("Your input is not a Digit.\n");
	}

	return 0;
}
*/