/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-mora <rel-mora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/24 19:28:32 by rel-mora          #+#    #+#             */
/*   Updated: 2024/01/11 11:22:49 by rel-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_len_int(int n)
{
	int		count;
	long	long_number;

	count = 0;
	long_number = n;
	if (long_number < 0)
	{
		long_number = -long_number;
		count++;
	}
	if (long_number == 0)
		return (++count);
	while (long_number)
	{
		long_number = long_number / 10;
		count++;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		i;
	long	long_number;

	long_number = n;
	i = ft_len_int(n);
	str = malloc(sizeof(char) * (i + 1));
	if (!str)
		return (NULL);
	str[i--] = '\0';
	if (long_number == 0)
		str[0] = '0';
	if (long_number < 0)
	{
		str[0] = '-';
		long_number = -long_number;
	}
	while (long_number)
	{
		str[i--] = (long_number % 10) + '0';
		long_number = long_number / 10;
	}
	return (str);
}
