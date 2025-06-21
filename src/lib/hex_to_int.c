/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hex_to_int.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achoukri <achoukri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 02:03:45 by achoukri          #+#    #+#             */
/*   Updated: 2025/04/24 10:20:48 by achoukri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	hex_to_int(const char *hex)
{
	if (!hex || !*hex)
		ft_error_msg("Empty hex string");
	if (hex[0] == '0' && (hex[1] == 'x' || hex[1] == 'X'))
		hex += 2;
	return (ft_atoi_base(hex, 16));
}
