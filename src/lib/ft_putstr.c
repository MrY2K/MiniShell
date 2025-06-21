/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achoukri <achoukri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 21:45:41 by achoukri          #+#    #+#             */
/*   Updated: 2025/04/24 10:22:34 by achoukri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putstr(char *s)
{
	int	count;

	if (!s)
		return (write(1, "(null)", 6));
	count = 0;
	while (*s)
		count += write(1, s++, 1);
	return (count);
}
// int main()
// {
// 	//char *s = "";
// 	ft_putstr_fd(NULL, 0);
// }