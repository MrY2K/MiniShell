/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajelloul <ajelloul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 18:37:51 by ajelloul          #+#    #+#             */
/*   Updated: 2025/06/17 11:28:54 by ajelloul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

long long	ft_atoll(const char *str)
{
	int			sign;
	long long	result;

	sign = 1;
	result = 0;
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
		result = result * 10 + *str++ - '0';
	}
	return (result * sign);
}

/*
	Valid Strings : 
		+42
		0000
		-1337
	
	Invalid Strings :

		""
		" "
		42a
		--42
		4 2
		--1337
*/

static int	is_numeric_string(char *str)
{
	int	i;

	if (!str || !*str)
		return (0);
	i = 0;
	if (str[0] == '+' || str[0] == '-')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

/*
	checks 
	Can I safely convert this number in str into a ll in C without overflow
*/

static int	is_valid_long_range(char *str, int sign, long long result)
{
	int			i;

	if (!str || !*str)
		return (0);
	i = 0;
	if (str[0] == '-' || str[0] == '+')
	{
		if (str[0] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (sign == 1 && result > (LLONG_MAX - (str[i] - '0')) / 10)
			return (0);
		if (sign == -1 && result > (LLONG_MAX / 10))
			return (0);
		if (sign == -1 && result == (LLONG_MAX / 10) && (str[i] - '0') > 8)
			return (0);
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (1);
}

int	is_valid_exit_arg(char *arg)
{
	return (is_numeric_string(arg) && is_valid_long_range(arg, 1, 0));
}
