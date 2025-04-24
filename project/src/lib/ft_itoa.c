/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achoukri <achoukri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 01:44:24 by achoukri          #+#    #+#             */
/*   Updated: 2025/04/24 10:24:35 by achoukri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	digit_counter(long n);

char	*ft_itoa(int n)
{
	int		digit_count;
	char	*tmp;
	long	nbr;

	nbr = n;
	if (nbr == 0) 
		return (ft_strdup("0"));
	digit_count = digit_counter(nbr);
	tmp = ft_calloc(digit_count + 1, sizeof(char));
	if (tmp == NULL)
		return (NULL);
	if (nbr < 0)
	{
		tmp[0] = '-';
		nbr = -nbr;
	}
	while (nbr > 0)
	{
		tmp[digit_count - 1] = (nbr % 10) + 48;
		nbr = nbr / 10;
		digit_count--;
	}
	return (tmp);
}

static int	digit_counter(long n)
{
	unsigned int	count;
	long			tmp_n;

	count = 0;
	tmp_n = n;
	if (tmp_n == 0)
		count++;
	if (tmp_n < 0)
	{
		count++;
		tmp_n = -tmp_n;
	}
	while (tmp_n > 0)
	{
		tmp_n = tmp_n / 10;
		count++;
	}
	return (count);
}

/*
int main(void)
{
	int n = -2147483648;
	int n2 = 2147483647;
	int n3 = 0;

	char *res = ft_itoa(n);
	char *res2 = ft_itoa(n2);
	char *res3 = ft_itoa(n3);

	printf("\nEXPECTING :%d \n", n);
	printf("\nGOT       :%s\n\n", res);
	printf("\nEXPECTING :%d \n", n2);
	printf("\nGOT       :%s\n\n", res2);
	printf("\nEXPECTING :%d \n", n3);
	printf("\nGOT       :%s\n\n", res3);

	free(res);
	free(res2);
	free(res3);
	return 0;
}
*/