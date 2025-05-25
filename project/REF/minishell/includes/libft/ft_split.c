/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-mora <rel-mora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 18:26:57 by rel-mora          #+#    #+#             */
/*   Updated: 2024/09/24 10:05:56 by rel-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**free_ptrs(char **ptr, int i)
{
	while (i > 0)
	{
		i--;
		free(ptr[i]);
	}
	free(ptr);
	return (0);
}

static int	count_word(char const	*s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i] != c && s[i])
		{
			count++;
			while (s[i] != c && s[i])
				i++;
		}
	}
	return (count);
}

static int	len_word(char const *s, char c)
{
	int	i;

	i = 0;
	while (s[i] != c && s[i])
		i++;
	return (i);
}

static char	**ft_fill(char const *s, char c, char **str)
{
	int	i;
	int	j;

	i = 0;
	while (*s)
	{
		if (*s != c)
		{
			str[i] = malloc ((len_word(s, c) + 1) * sizeof(char));
			if (!str[i])
				return (free_ptrs(str, i));
			j = 0;
			while (*s != c && *s)
			{
				str[i][j++] = *s;
				s++;
			}
			str[i++][j] = '\0';
		}
		while (*s == c && *s)
			s++;
	}
	str[i] = NULL;
	return (str);
}

char	**ft_split(char const *s, char c)
{
	int		count;
	char	**str;

	if (s == NULL)
		return (NULL);
	count = count_word(s, c);
	str = malloc((count + 1) * sizeof(char *));
	if (!str)
		return (NULL);
	str = ft_fill(s, c, str);
	return (str);
}
