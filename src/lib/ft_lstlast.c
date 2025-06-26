/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achoukri <achoukri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 19:27:36 by achoukri          #+#    #+#             */
/*   Updated: 2025/04/24 10:24:07 by achoukri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst -> next;
	return (lst);
}
/*
#include "libft.h"

int	main()
{
	// Create nodes
	t_list	*node1 = ft_lstnew((void *)42);
	t_list	*node2 = ft_lstnew((void *)66);
	t_list	*node3 = ft_lstnew((void *)13);
	t_list	*node4 = ft_lstnew((void *)37);
	
	//link the nodes:
	node1->next = node2;
	node2->next = node3;
	node3->next = node4;

	//linst size (ft_lstsize)
	t_list *p = ft_lstlast(node1);
	printf("List Last Is: %p\n", p->next);

	
	//freeeeee
    free(node1);
    free(node2);
    free(node3);
    free(node4);
}
*/