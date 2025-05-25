/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-mora <rel-mora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 20:51:21 by rel-mora          #+#    #+#             */
/*   Updated: 2024/01/10 18:01:59 by rel-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	length_needle;

	i = 0;
	if (needle[i] == '\0')
		return ((char *)haystack);
	if (len <= 0 || haystack[i] == '\0')
		return (NULL);
	length_needle = ft_strlen(needle);
	while (haystack[i] && (i + length_needle) <= len)
	{
		if (ft_strncmp((haystack + i), needle, length_needle) == 0)
			return ((char *)(haystack + i));
		i++;
	}
	return (0);
}
