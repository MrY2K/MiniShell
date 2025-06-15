/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-mora <reduno96@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 11:50:53 by rel-mora          #+#    #+#             */
/*   Updated: 2024/08/06 17:30:36 by rel-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_splitor *lst, void (*f)(void *))
{
	t_splitor	*node;

	if (!lst || !f)
		return ;
	node = lst;
	while (node != NULL)
	{
		f(node->in);
		node = node->next;
	}
}
