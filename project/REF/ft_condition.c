/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_condition.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-mora <rel-mora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 15:03:03 by rel-mora          #+#    #+#             */
/*   Updated: 2024/09/26 15:05:22 by rel-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_condition(t_splitor *start)
{
	if ((start->type != ' ' && start->type != -1 && start->type != '$'
			&& start->type != '\'' && start->type != '\"'
			&& start->type != HERE_DOC))
		return (1);
	return (0);
}

int	redirection(t_splitor *start)
{
	if ((start)->type == '<' || (start)->type == '>'
		|| (start)->type == DREDIR_OUT || (start)->type == HERE_DOC)
		return (1);
	return (0);
}

int	quotes(t_splitor *start)
{
	if ((start)->type == '\"' || (start)->type == '\'')
		return (1);
	return (0);
}
