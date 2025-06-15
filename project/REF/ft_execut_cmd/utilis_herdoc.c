/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilis_herdoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-mora <rel-mora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 19:20:16 by bouhammo          #+#    #+#             */
/*   Updated: 2024/09/22 15:06:35 by rel-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_here_doc	*new_node_her(char *file, int fd, int x, int is_expand)
{
	t_here_doc	*elem;
	char		*tmp_line;
	char		*path_file;
	char		*it;

	it = ft_itoa(x);
	elem = (t_here_doc *)malloc(sizeof(t_here_doc));
	if (!elem)
		return (NULL);
	tmp_line = ft_strjoin_1(file, it);
	path_file = ft_strjoin_1("/tmp/herdoc", tmp_line);
	free(tmp_line);
	free(it);
	elem->store = file;
	elem->fd = fd;
	elem->idx = x;
	elem->expad = is_expand;
	elem->heredoc_file = (path_file);
	elem->next = NULL;
	return (elem);
}

void	add_back_node_her(t_here_doc **her, t_here_doc *new_her)
{
	t_here_doc	*p;

	p = *her;
	if (!her || !new_her)
		return ;
	if (!(*her))
	{
		*her = new_her;
		return ;
	}
	while (p->next)
	{
		p = p->next;
	}
	p->next = new_her;
}
