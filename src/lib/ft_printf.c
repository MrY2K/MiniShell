/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achoukri <achoukri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 00:03:08 by achoukri          #+#    #+#             */
/*   Updated: 2025/06/21 04:23:52 by achoukri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	flag_dispatcher(const char format, va_list args)
{
	int	count;

	count = 0;
	if (format == 'c')
		count = ft_putchar(va_arg(args, int));
	else if (format == 's')
		count = ft_putstr(va_arg(args, char *));
	else if (format == 'p')
		count = ft_putadd(va_arg(args, void *));
	else if (format == 'd' || format == 'i')
		count = ft_putnbr(va_arg(args, int));
	else if (format == 'u')
		count = ft_putnbr_unsigned(va_arg(args, unsigned int));
	else if (format == 'x' || format == 'X')
		count = ft_putnbr_hex(va_arg(args, unsigned int), format);
	else
		count += ft_putchar(format);
	return (count);
}

int	ft_printf(const char *str, ...)
{
	va_list	args;
	int		count;
	int		i;

	if (write(1, "", 0) == -1)
		return (-1);
	va_start(args, str);
	count = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '%')
		{
			if (str[i + 1])
			{
				i++;
				count += flag_dispatcher(str[i], args);
			}
		}
		else
			count += ft_putchar(str[i]);
		i++;
	}
	va_end(args);
	return (count);
}
