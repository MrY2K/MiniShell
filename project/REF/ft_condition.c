/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_condition.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achoukri <achoukri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 15:03:03 by rel-mora          #+#    #+#             */
/*   Updated: 2025/06/09 00:57:36 by achoukri         ###   ########.fr       */
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



int	quotes(t_splitor *start)
{
	if ((start)->type == '\"' || (start)->type == '\'')
		return (1);
	return (0);
}
