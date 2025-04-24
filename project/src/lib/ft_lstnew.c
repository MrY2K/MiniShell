/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achoukri <achoukri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 18:11:36 by achoukri          #+#    #+#             */
/*   Updated: 2025/04/24 10:24:00 by achoukri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*new_node;

	new_node = malloc(sizeof(t_list));
	if (!new_node)
		return (NULL);
	new_node -> content = content;
	new_node -> next = NULL;
	return (new_node);
}
/*
int main()
{
// int main()
// {
// 	int content = 42;
// 	t_list	*node1 = ft_lstnew(&content);

// 	printf("%d \n", *(int *)node1->content);
	int content1 = 1, content2 = 2, content3 = 3;

	t_list	*node1 = ft_lstnew(&content1);
	t_list	*node2 = ft_lstnew(&content2);
	t_list	*node3 = ft_lstnew(&content3);
	node1->next = node2;
	node2->next = node3;
	node3->next = NULL;
	t_list	*tmp = node1;
	while (tmp)
	{
		printf("Content:   %d\n", *(int *)tmp->content);
		tmp = tmp->next;
	}
	free(node1);
	free(node2);
	free(node3);
}
*/