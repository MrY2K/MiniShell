/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   funct_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bouhammo <bouhammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 17:33:07 by bouhammo          #+#    #+#             */
/*   Updated: 2024/09/28 12:28:18 by bouhammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*git_type_redir(t_redirect *redir)
{
	if (redir == NULL)
		return (NULL);
	else
	{
		if (redir->type == REDIR_OUT)
			return (">");
		else if (redir->type == REDIR_IN)
			return ("<");
		else if (redir->type == DREDIR_OUT)
			return (">>");
		else if (redir->type == HERE_DOC)
			return ("<<");
		return (NULL);
	}
}

int	test_redir(t_command *list)
{
	t_redirect	*tmp;

	if (list == NULL)
		return (0);
	tmp = list->doc;
	while (tmp != NULL)
	{
		if (tmp->type == DREDIR_OUT || tmp->type == REDIR_OUT
			|| tmp->type == REDIR_IN)
		{
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}
