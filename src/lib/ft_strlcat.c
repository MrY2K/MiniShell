/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achoukri <achoukri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 15:27:16 by achoukri          #+#    #+#             */
/*   Updated: 2025/04/24 10:22:05 by achoukri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	src_len;
	size_t	dst_len;

	i = 0;
	src_len = ft_strlen(src);
	if (dst == NULL && dstsize == 0)
		return (src_len);
	dst_len = ft_strlen(dst);
	if (dstsize <= dst_len)
		return (dstsize + src_len);
	while (i < src_len && (dst_len + i) < (dstsize - 1))
	{
		dst[dst_len + i] = src[i];
		i++;
	}
	dst[dst_len + i] = '\0';
	return (dst_len + src_len);
}
/*
int main(void)
{

	char *src = "hi";
	char dest[20] = "ho";
	size_t dest_size = 5;

	//strlcat(NULL, "abc", 10);

	//printf("\nOG     :%lu\n", strlcat(dest, src, 2));
	
	//printf("\nOG      :%lu\n", strlcat(dest, src, dest_size));
	printf("\nMINE    :%lu\n", ft_strlcat(dest, src, dest_size));

		printf("\n%s", dest);

	
	//strlcat(NULL, NULL, 0);

	//printf("%s", dest);


	// char *src2 = "";
	// char dest2[6] = "";
	
	//ft_strlcat(NULL, "string", 0);
	//ft_strlcat(dest2, src2, 2);

	//printf("\nMINE   :%lu\n", ft_strlcat(NULL, "string", 0));
	//ft_strlcat(NULL, "string", 0);
	//printf("%s", dest2);
	return 0;
}
*/