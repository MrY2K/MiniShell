/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achoukri <achoukri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 12:30:39 by ajelloul          #+#    #+#             */
/*   Updated: 2025/06/06 19:05:30 by achoukri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_lexer(t_token **token)
{
	t_token	*cur;

	while (*token)
	{
		cur = *token;
		*token = (*token)->next;
		if (cur->value)
		{
			free(cur->value);
			cur->value = NULL;
		}
		free(cur);
		cur = NULL;
	}
}

void	free_minibash(t_minibash **bash) // not finish yet
{
	t_env	*current;
	t_env	*next;

	if (!bash || !*bash)
		return ;
	current = (*bash)->env;
	while (current)
	{
		next = current->next;
		free(current->name);
		free(current->value);
		free(current);
		current = next;
	}
	free(*bash);
	*bash = NULL;
}
