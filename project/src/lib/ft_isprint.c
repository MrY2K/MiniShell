/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achoukri <achoukri@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 19:02:25 by achoukri          #+#    #+#             */
/*   Updated: 2024/10/29 13:54:00 by achoukri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isprint(int c)
{
	if (c >= 32 && c <= 126)
	{
		return (1);
	}
	else
		return (0);
}
/*
int main(void)
{
	char c = 129;
	
	if (ft_isprint((unsigned char) c))
	{
		printf("Your input is printable.\n");
	}
	else
	{
		printf("Your input is not printable.\n");
	}

	return 0;
}
*/