/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achoukri <achoukri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 02:15:33 by achoukri          #+#    #+#             */
/*   Updated: 2025/06/21 02:15:34 by achoukri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	skip_nonword_tokens(t_token **tok_ptr, t_env *env)
{
	char	**arr;

	arr = NULL;
	while ((*tok_ptr) && (((*tok_ptr)->type == '<')
			|| ((*tok_ptr)->type == '>')
			|| ((*tok_ptr)->type == TOKEN_REDIR_APPEND)
			|| ((*tok_ptr)->type == TOKEN_HEREDOC)))
	{
		*tok_ptr = (*tok_ptr)->next;
		skip_whitespace(tok_ptr);
		while ((*tok_ptr) && (*tok_ptr)->state == N
			&& (((*tok_ptr)->type == '\"') || ((*tok_ptr)->type == '\'')))
			*tok_ptr = (*tok_ptr)->next;
		if ((*tok_ptr) && (*tok_ptr)->state == N
			&& ((*tok_ptr)->type != '\"') && ((*tok_ptr)->type != '\'')
			&& ((*tok_ptr)->type != '|'))
			process_word(tok_ptr, env, 0, &arr);
		else if ((*tok_ptr) && (((*tok_ptr)->state == D)
				|| ((*tok_ptr)->state == S)))
			process_quoted(tok_ptr, env, 0, &arr);
	}
	free_argument_array(arr);
}
