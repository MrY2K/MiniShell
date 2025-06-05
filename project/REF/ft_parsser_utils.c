/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsser_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-mora <rel-mora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 21:25:06 by rel-mora          #+#    #+#             */
/*   Updated: 2024/09/24 13:52:34 by rel-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_add_command(t_command **lst, t_command *new)
{
	t_command	*last;

	if (!lst || !new)
		return ;
	if (*lst == NULL)
		*lst = new;
	else
	{
		last = ft_last_command(*lst);
		last->next = new;
	}
}

t_command	*ft_last_command(t_command *lst)
{
	t_command	*last;

	last = lst;
	if (!lst)
		return (NULL);
	while (last->next != NULL)
		last = last->next;
	return (last);
}

t_command	*ft_new_command(t_splitor **tmp_x, t_environment *my_env)
{
	t_command	*new_node;

	new_node = malloc(sizeof(t_command));
	new_node->arg = NULL;
	new_node->content = NULL;
	new_node->len = 0;
	new_node->is_pipe = 0;
	new_node->doc = NULL;
	new_node->her = NULL;
	new_node->ar_env = NULL;
	if (((*tmp_x) != NULL && ((*tmp_x)->type == '|' && (*tmp_x)->state == G)))
	{
		ft_join_arr(&(new_node->arg), (*tmp_x)->in);
		new_node->is_pipe = 1;
		(*tmp_x) = (*tmp_x)->next;
	}
	else if ((*tmp_x) != NULL)
		ft_not_pipe(&new_node, tmp_x, my_env);
	if (new_node->arg != NULL && new_node->arg[0] != NULL)
		new_node->content = new_node->arg[0];
	new_node->next = NULL;
	return (new_node);
}
