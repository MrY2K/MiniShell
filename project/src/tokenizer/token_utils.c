/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achoukri <achoukri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 11:03:47 by ajelloul          #+#    #+#             */
/*   Updated: 2025/06/21 02:31:48 by achoukri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_isspace(int c)
{
	return (c == 32 || (c >= 9 && c <= 13));
}

int	ft_isprint(int c)
{
	return (c == 9 || (c >= 32 && c <= 126));
}

int	is_metachar(char c)
{
	if (c == '|' || c == '<' || c == '>'
		|| c == '$' || c == '\'' || c == '\"'
		|| ft_isspace(c))
		return (1);
	return (0);
}

t_token	*ft_lstnew_token(char *value, int len, t_token_type type, t_state state)
{
	t_token	*new_node;

	new_node = (t_token *)malloc(sizeof(t_token));
	if (!new_node)
		return (NULL);
	new_node->value = value;
	new_node->type = type;
	new_node->state = state;
	new_node->len = len;
	new_node->next = NULL;
	return (new_node);
}

void	ft_lstadd_back_token(t_token **lst, t_token *new_node)
{
	t_token	*current;

	if (!new_node || !lst)
		return ;
	if (!*lst)
	{
		*lst = new_node;
		return ;
	}
	current = *lst;
	while (current->next)
		current = current->next;
	current->next = new_node;
}
