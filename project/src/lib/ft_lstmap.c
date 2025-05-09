/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achoukri <achoukri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 17:29:20 by achoukri          #+#    #+#             */
/*   Updated: 2025/04/24 10:24:03 by achoukri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_list;
	t_list	*new_node;
	void	*content;

	if (!lst || !f || !del)
		return (NULL);
	new_list = NULL;
	while (lst)
	{
		content = f(lst->content);
		new_node = ft_lstnew(content);
		if (!new_node)
		{
			del(content);
			ft_lstclear(&new_list, del);
			return (NULL);
		}
		ft_lstadd_back(&new_list, new_node);
		lst = lst ->next;
	}
	return (new_list);
}
/*
void	del(void *x)
{
	free(x);
}
void	*make_upper(void *s) 
{
	char *str = ft_strdup(s);
	int i = 0;
	while (str[i])
	{
		str[i] = ft_toupper(str[i]);
		i++;
	}
	return (str);
}

#include <stdio.h>
int main()
{
	// make a list
	t_list	*node1 = ft_lstnew("First");
	t_list	*node2 = ft_lstnew("Second");
	t_list	*node3 = ft_lstnew("Thiiiird!!!!!");

	node1->next = node2;
	node2->next = node3;

	t_list	*head = node1;

	//print it
	// while (head)
	// {
	// 	printf("%s\n", head->content);
	// 	head = head->next;
	// }

	//make a new list based on the old with the Make_upper func
	t_list	*new_list = ft_lstmap(head, make_upper, del);

	//print it
	while (new_list)
	{
		printf("%s\n", (char *)new_list->content);
		new_list = new_list->next;
	}

	//Clear
	//ft_lstclear(&head, del);
	ft_lstclear(&new_list, del);
}
*/