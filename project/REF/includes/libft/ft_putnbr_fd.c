/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-mora <rel-mora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/24 18:31:26 by rel-mora          #+#    #+#             */
/*   Updated: 2024/01/10 18:01:27 by rel-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	long	long_number;

	long_number = n;
	if (long_number < 0)
	{
		ft_putchar_fd('-', fd);
		long_number = -long_number;
	}
	if (long_number >= 10)
	{
		ft_putnbr_fd(long_number / 10, fd);
		ft_putnbr_fd(long_number % 10, fd);
	}
	if (long_number <= 9)
		ft_putchar_fd((long_number + '0'), fd);
}
