/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_utils_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achoukri <achoukri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 02:15:40 by achoukri          #+#    #+#             */
/*   Updated: 2025/06/21 02:16:00 by achoukri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_str_join(char *s1, char *s2)
{
	char	*str_final;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!s1)
	{
		s1 = ft_calloc(1, sizeof(char));
		s1[0] = '\0';
	}
	if (!s2 || !s1)
		return (NULL);
	str_final = ft_calloc((ft_strlen(s1) + ft_strlen(s2)) + 1, sizeof(char));
	if (str_final == NULL)
		return (NULL);
	while (s1[j])
		str_final[i++] = s1[j++];
	j = 0;
	while (s2[j])
		str_final[i++] = s2[j++];
	str_final[i] = '\0';
	return (str_final);
}

t_heredoc	*new_node_her(char *file, int fd, int tokens, int is_expand)
{
	t_heredoc	*elem;
	char		*tmp_line;
	char		*path_file;
	char		*it;

	it = ft_itoa(tokens);
	elem = (t_heredoc *)malloc(sizeof(t_heredoc));
	if (!elem)
		return (NULL);
	tmp_line = ft_str_join(file, it);
	path_file = ft_str_join("/tmp/herdoc", tmp_line);
	free(tmp_line);
	free(it);
	elem->delimiter = file;
	elem->fd = fd;
	elem->index = tokens;
	elem->expand = is_expand;
	elem->her_file = (path_file);
	elem->next = NULL;
	return (elem);
}

char	*ft_fill_final(char **s)
{
	int		i;
	char	*final;
	char	*temp;

	if (!s || !s[0])
		return (NULL);
	final = ft_strdup("");
	i = 0;
	while (s[i] != NULL)
	{
		temp = final;
		final = ft_strjoin(final, s[i]);
		free(temp);
		if (s[i + 1] != NULL)
		{
			temp = final;
			final = ft_strjoin(final, " ");
			free(temp);
		}
		i++;
	}
	return (final);
}

void	ft_skip_spaces(t_token **tpm_t)
{
	while ((*tpm_t) != NULL && (*tpm_t)->type == ' ')
		(*tpm_t) = (*tpm_t)->next;
}
