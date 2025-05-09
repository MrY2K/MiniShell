/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achoukri <achoukri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 22:19:18 by achoukri          #+#    #+#             */
/*   Updated: 2025/04/24 10:24:11 by achoukri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	if (!lst || !f)
		return ;
	while (lst)
	{
		f(lst->content);
		lst = lst->next;
	}
}
/*
void print_content(void *content)
{
	printf("%s\n", (char *)content);
}
int main()
{
	t_list *list = NULL;

	// Create a list
	list = ft_lstnew(ft_strdup("First"));
	ft_lstadd_back(&list, ft_lstnew(ft_strdup("Second")));
	ft_lstadd_back(&list, ft_lstnew(ft_strdup("Third")));
	
	// iterate
	ft_lstiter(list, print_content);
	
	// wa clear it al3awed 
	ft_lstclear(&list, free);
	return (0);
}
*/