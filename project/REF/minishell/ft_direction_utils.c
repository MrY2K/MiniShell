/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_direction_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-mora <rel-mora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 13:58:33 by rel-mora          #+#    #+#             */
/*   Updated: 2024/09/24 14:38:07 by rel-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_redirect	*ft_new_redir(void *content, t_token type, int is_amb)
{
	t_redirect	*new_node;

	new_node = NULL;
	new_node = malloc(sizeof(t_redirect));
	if (!new_node)
		return (NULL);
	new_node->store = content;
	new_node->type = type;
	new_node->is_amb = is_amb;
	new_node->next = NULL;
	return (new_node);
}

void	ft_add_redir(t_redirect **lst, t_redirect *new)
{
	t_redirect	*last;

	if (!lst || !new)
		return ;
	if (*lst == NULL)
		*lst = new;
	else
	{
		last = ft_last_redir(*lst);
		last->next = new;
	}
}

t_redirect	*ft_last_redir(t_redirect *lst)
{
	t_redirect	*last;

	last = lst;
	if (!lst)
		return (NULL);
	while (last->next != NULL)
		last = last->next;
	return (last);
}
