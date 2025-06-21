/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achoukri <achoukri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 16:41:12 by achoukri          #+#    #+#             */
/*   Updated: 2025/04/24 11:44:09 by achoukri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*allocated_mem;

	if (count == 0 || size == 0)
		return (malloc(0));
	if (count > SIZE_MAX / size)
		return (NULL);
	allocated_mem = malloc(count * size);
	if (!allocated_mem)
		return (NULL);
	ft_memset(allocated_mem, 0, count * size);
	return (allocated_mem);
}
/*
int main(void)
{
	size_t count = 576464564456556;
	size_t size = 4564564564564562;

	char *ptr = ft_calloc(count , size);
	printf("%s", ptr);

	free(ptr);

	return 0;
}
*/