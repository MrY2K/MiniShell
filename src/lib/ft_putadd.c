/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putadd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achoukri <achoukri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 22:44:00 by achoukri          #+#    #+#             */
/*   Updated: 2025/04/24 10:23:14 by achoukri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putadd(void *add)
{
	unsigned long	nbr_l;
	int				count;

	nbr_l = (unsigned long)add;
	count = 0;
	count += ft_putstr("0x");
	count += ft_putnbr_hex(nbr_l, 'x');
	return (count);
}

// #include <stdio.h>
// int main()
// {
// 	void *ptr;
// 	int m = ft_putadd(ptr);
// 	printf("\n\n");
// 	int o = printf("%p", ptr);
// 	printf("\n\n%d  %d \n\n", m, o);
// }
