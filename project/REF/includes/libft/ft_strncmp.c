/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-mora <rel-mora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 22:25:21 by rel-mora          #+#    #+#             */
/*   Updated: 2024/01/10 18:02:01 by rel-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	*sone;
	unsigned char	*stwo;
	size_t			i;

	sone = (unsigned char *)s1;
	stwo = (unsigned char *)s2;
	i = 0;
	if (i == n)
		return (0);
	while (i < n - 1 && s1[i] && s2[i])
	{
		if (sone[i] == stwo[i])
			i++;
		else
			break ;
	}
	return (sone[i] - stwo[i]);
}
