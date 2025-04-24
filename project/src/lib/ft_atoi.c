/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achoukri <achoukri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 02:47:53 by achoukri          #+#    #+#             */
/*   Updated: 2025/04/24 10:26:28 by achoukri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int			sign;
	long long	r;

	sign = 1;
	r = 0;
	while (*str == ' ' || *str == '\t' || *str == '\n'
		|| *str == '\v' || *str == '\f' || *str == '\r')
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str++ == '-')
			sign = sign * -1;
	}
	while (*str >= '0' && *str <= '9')
	{
		if (r > (LONG_MAX - *str - '0') / 10)
		{
			if (sign == 1)
				return (-1);
			else
				return (0);
		}
		r = r * 10 + *str++ - '0';
	}
	return (r * sign);
}
/*
int main(void)
{
    char *str1 = "9999999999999999999999";
    int match1 = atoi(str1);
    int ogmatch1 = ft_atoi(str1);
	printf("MINE :%d\n", ogmatch1);
	printf("OG   :%d\n\n", match1);

    char *str  = "-9999999999999999999999";
    int match  = atoi(str);
    int ogmatch  = ft_atoi(str);
	printf("MINE :%d\n", ogmatch);
	printf("OG   :%d\n\n", match);

	char *str2 = "0";
    int match2 = atoi(str2);
    int ogmatch2 = ft_atoi(str2);
	printf("OG   :%d\n", match2);
	printf("MINE :%d\n\n", ogmatch2);

	char *str3 = "2147483647";
    int match3 = atoi(str3);
    int ogmatch3 = ft_atoi(str3);
	printf("OG   :%d\n", match3);
	printf("MINE :%d\n\n", ogmatch3);

	char *str4 = "-2147483648";
    int match4 = atoi(str4);
    int ogmatch4 = ft_atoi(str4);
	printf("OG   :%d\n", match4);
	printf("MINE :%d\n\n", ogmatch4);

	char *str5 = "-42";
    int match5 = atoi(str5);
    int ogmatch5 = ft_atoi(str5);
	printf("OG   :%d\n", match5);
	printf("MINE :%d\n\n", ogmatch5);
}
*/