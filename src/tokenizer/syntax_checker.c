/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_checker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achoukri <achoukri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 11:04:27 by ajelloul          #+#    #+#             */
/*   Updated: 2025/06/21 02:31:42 by achoukri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	is_pipe_at_start(t_token *start)
{
	return (start->type == '|');
}

/*
	case : > 
*/

static int	is_invalid_single_token(t_token *start)
{
	return (start->next == NULL
		&& start->type != ' '
		&& start->type != TOKEN_WORD
		&& start->type != '$');
}

static int	is_unclosed_quote(t_token *start)
{
	return ((start->type == '\'' || start->type == '\"')
		&& start->next == NULL);
}

int	has_syntax_error_at_start(t_token **start)
{
	if (start == NULL || *start == NULL)
		return (0);
	if (is_pipe_at_start(*start) || is_invalid_single_token(*start)
		|| is_unclosed_quote(*start))
		return (1);
	return (0);
}

void	skip_spaces(t_token	**cur_node)
{
	while ((*cur_node) && (*cur_node)->type == 32)
	{
		(*cur_node) = (*cur_node)->next;
	}
}
