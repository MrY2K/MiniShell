/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-mora <rel-mora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/24 21:18:25 by rel-mora          #+#    #+#             */
/*   Updated: 2024/09/25 12:15:05 by rel-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_splitor	*ft_lstnew(void *content, int len, t_token type, t_state state)
{
	t_splitor	*new_node;

	new_node = malloc(sizeof(t_splitor));
	if (!new_node)
		return (NULL);
	new_node->in = content;
	new_node->len = len;
	new_node->type = type;
	new_node->state = state;
	new_node->next = NULL;
	new_node->prev = NULL;
	return (new_node);
}
