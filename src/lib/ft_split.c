/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achoukri <achoukri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 17:50:24 by achoukri          #+#    #+#             */
/*   Updated: 2025/04/24 10:22:29 by achoukri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	word_counter(const char *str, char c);
static char	*malloc_and_copy_a_word(const char *s, char c);
static char	**malloc_and_copy_final(const char *s, char c, size_t words_of_s);
static void	*free_all(char **to_free, size_t j);

char	**ft_split(char const *s, char c)
{
	char	**final;
	size_t	words_of_s;

	if (s == NULL)
		return (final = NULL);
	words_of_s = word_counter(s, c);
	final = malloc_and_copy_final(s, c, words_of_s);
	return (final);
}

static int	word_counter(const char *s, char c)
{
	int	words;
	int	in_word_flag;

	words = 0;
	in_word_flag = 0;
	while (*s)
	{
		if (*s != c)
		{
			if (in_word_flag == 0)
			{
				in_word_flag = 1;
				words++;
			}
		}
		else
			in_word_flag = 0;
		s++;
	}
	return (words);
}

static char	*malloc_and_copy_a_word(const char *s, char c)
{
	char	*word;
	size_t	i;
	size_t	len;

	len = 0;
	while (s[len] && s[len] != c)
		len++;
	word = malloc(sizeof(char) * (len + 1));
	if (!word)
		return (NULL);
	i = 0;
	while (i < len)
	{
		word[i] = s[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

static char	**malloc_and_copy_final(const char *s, char c, size_t words_of_s)
{
	char	**final;
	size_t	i;
	size_t	j;

	final = (char **)malloc(sizeof(char *) * (words_of_s + 1));
	if (final == NULL)
		return (NULL);
	j = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] == c && s[i])
			i++;
		if (s[i] != c && s[i])
		{
			final[j] = malloc_and_copy_a_word(&s[i], c);
			if (final[j] == NULL)
				return (free_all(final, j));
			while (s[i] != c && s[i])
				i++;
			j++;
		}
	}
	final[j] = NULL;
	return (final);
}

static void	*free_all(char **to_free, size_t j)
{
	while (j > 0)
	{
		free(to_free[j - 1]);
		j--;
	}
	free(to_free);
	return (NULL);
}

// int	main (void)
// {
//     char **result = ft_split(",Hellow,,42,World,1337", ',');

// 	for (size_t i = 0; result[i] != NULL; i++)
// 	{
// 		printf("[%lu] ", i);
// 		printf("%s\n", result[i]);
// 		free(result[i]);
// 	}
// 	free(result);
// 	return 0;
// }
