/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achoukri <achoukri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 11:14:54 by ajelloul          #+#    #+#             */
/*   Updated: 2025/06/21 02:31:39 by achoukri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token_type	get_token_type(char c)
{
	if (c == '$')
		return (TOKEN_ENV);
	else if (c == '|')
		return (TOKEN_PIPE);
	else if (c == '\n')
		return (TOKEN_NEWLINE);
	else if (c == '\'')
		return (TOKEN_SINGLE_QUOTE);
	else if (c == '\"')
		return (TOKEN_DOUBLE_QUOTE);
	else if (c == '>')
		return (TOKEN_REDIR_OUT);
	else if (c == '<')
		return (TOKEN_REDIR_IN);
	else if (c == ' ' || c == '\t' || c == '\n')
		return (TOKEN_WHITE_SPACE);
	return (0);
}
