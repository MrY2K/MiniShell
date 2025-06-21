/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_int.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achoukri <achoukri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 09:27:25 by achoukri          #+#    #+#             */
/*   Updated: 2025/04/24 10:20:35 by achoukri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	is_int(char *arg)
{
	char	*limit;
	int		len;
	int		sign;

	len = num_len(arg, &sign);
	if (*arg == '-' || *arg == '+')
		arg++;
	while (*arg == '0')
		arg++;
	if (len < 10)
		return (1);
	else if (len > 10)
		return (0);
	else
	{
		if (sign == -1)
			limit = "2147483648";
		else
			limit = "2147483647";
		if (ft_strncmp(arg, limit, 10) <= 0)
			return (1);
		else
			return (0);
	}
}

int	num_len(char *num, int *sign)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	*sign = 1;
	if (num[i] == '-' || num[i] == '+')
	{
		if (num[i] == '-')
			*sign = -1;
		i++;
	}
	while (num[i] == '0')
		i++;
	while (num[i] && num[i] >= '0' && num[i] <= '9')
	{
		len++;
		i++;
	}
	return (len);
}
