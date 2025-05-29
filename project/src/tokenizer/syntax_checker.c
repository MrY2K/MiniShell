/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_checker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajelloul <ajelloul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 11:04:27 by ajelloul          #+#    #+#             */
/*   Updated: 2025/05/28 11:42:17 by ajelloul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	is_pipe_at_start(t_token *start)
{
	return (start->type == '|');
}

static int	is_invalid_single_token(t_token *start)
{
	return (start->next == NULL
		&& start->type != ' '
		&& start->type != -1
		&& start->type != '$');
}

static int	is_unclosed_quote(t_token *start)
{
	return ((start->type == '\'' || start->type == '\"')
		&& start->next == NULL);
}

// static int	print_syntax_error(t_token *start)
// {
// 	if (is_pipe_at_start(start))
// 		ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", 2);
// 	else if (is_unclosed_quote(start)) // ' "  CTL + D
// 	{
// 		ft_putstr_fd("minishell: unexpected EOF while looking for matching `", 2);
// 		ft_putchar_fd(start->type, 2);
// 		ft_putstr_fd("'\n", 2);
// 	}
// 	else if (is_invalid_single_token(start))//  < >
// 	{
// 		if (start->type == '\n')
// 			ft_putstr_fd("minishell: syntax error near unexpected token `newline'\n", 2);
// 		else  // ;
// 		{
// 			ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
// 			ft_putchar_fd(start->type, 2);
// 			ft_putstr_fd("'\n", 2);
// 		}
// 	}
// 	return (1);
// }

int	has_syntax_error_at_start(t_token **start)
{
	if (start == NULL || *start == NULL)
		return (0);
	
	if (is_pipe_at_start(*start) || is_invalid_single_token(*start)
		|| is_unclosed_quote(*start))
		return (1);
	return (0);
}
