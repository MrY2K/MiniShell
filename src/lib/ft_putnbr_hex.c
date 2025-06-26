/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_hex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achoukri <achoukri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 19:27:16 by achoukri          #+#    #+#             */
/*   Updated: 2025/04/24 10:22:53 by achoukri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putnbr_hex(unsigned long nbr, char format)
{
	unsigned long	nbr_l;
	char			*base;
	int				count;

	nbr_l = (unsigned long)nbr;
	count = 0;
	if (format == 'x')
	{
		base = "0123456789abcdef";
	}
	else if (format == 'X')
	{
		base = "0123456789ABCDEF";
	}
	if (nbr_l >= 16)
	{
		count += ft_putnbr_hex(nbr_l / 16, format);
		count += ft_putnbr_hex(nbr_l % 16, format);
	}
	else
		count += ft_putchar(base[nbr_l]);
	return (count);
}
// #include <stdio.h>
// #include <limits.h>
// int main()
// {
// 	unsigned int gg = 4294967295876543;
// 	int m = ft_putnbr_hex(gg, 'x');
// 	printf("\n");
// 	int o = printf("%x", gg);
// 	printf("\n\n%d  %d \n\n", m, o);
// }