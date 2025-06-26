/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achoukri <achoukri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 19:48:41 by achoukri          #+#    #+#             */
/*   Updated: 2025/04/24 12:10:27 by achoukri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *_new)
{
	t_list	*last;

	if (lst == NULL || _new == NULL)
		return ;
	if (*lst == NULL)
	{
		*lst = _new;
	}
	else
	{
		last = ft_lstlast(*lst);
		last->next = _new;
	}
}
