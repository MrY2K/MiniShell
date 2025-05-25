/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-mora <rel-mora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 11:51:59 by rel-mora          #+#    #+#             */
/*   Updated: 2024/09/25 12:15:24 by rel-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_splitor **lst, t_splitor *new)
{
	if (new || lst)
	{
		new->next = *lst;
		if (*lst != NULL)
			(*lst)->prev = new;
		*lst = new;
	}
	else
		return ;
}
