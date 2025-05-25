/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_direction.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-mora <rel-mora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 07:24:52 by rel-mora          #+#    #+#             */
/*   Updated: 2024/10/02 12:46:10 by rel-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_next(t_splitor **tmp_x, t_command **tmp_cmd)
{
	if ((*tmp_x) != NULL && (*tmp_x)->type == '|')
		(*tmp_x) = (*tmp_x)->next;
	if ((*tmp_cmd) != NULL)
		(*tmp_cmd) = (*tmp_cmd)->next;
	if ((*tmp_cmd) != NULL && (*tmp_x) != NULL)
		(*tmp_cmd) = (*tmp_cmd)->next;
}

void	ft_fill_redirection(t_pre *id, t_environment *my_env, char *final)
{
	if (id->tmp_x != NULL && id->tmp_x->type == '>' && id->tmp_x->state == G)
	{
		id->tmp_x = id->tmp_x->next;
		ft_skip_spaces(&id->tmp_x);
		final = ft_skip_direction(&id->tmp_x, my_env, &id->is_amb, 1);
		ft_add_redir(&(id->tmp_cmd->doc), ft_new_redir(final, '>', id->is_amb));
	}
	else if (id->tmp_x != NULL && id->tmp_x->type == '<'
		&& id->tmp_x->state == G)
	{
		id->tmp_x = id->tmp_x->next;
		ft_skip_spaces(&id->tmp_x);
		final = ft_skip_direction(&id->tmp_x, my_env, &id->is_amb, 1);
		ft_add_redir(&(id->tmp_cmd->doc), ft_new_redir(final, '<', id->is_amb));
	}
	else if (id->tmp_x != NULL && id->tmp_x->type == DREDIR_OUT
		&& id->tmp_x->state == G)
	{
		id->tmp_x = id->tmp_x->next;
		ft_skip_spaces(&id->tmp_x);
		final = ft_skip_direction(&id->tmp_x, my_env, &id->is_amb, 1);
		ft_add_redir(&(id->tmp_cmd->doc), ft_new_redir(final, DREDIR_OUT,
				id->is_amb));
	}
}

void	ft_fill_her(t_pre *id, t_environment *my_env, char *final)
{
	while ((id->tmp_x != NULL && id->tmp_x->type == HERE_DOC
			&& id->tmp_x->state == G))
	{
		id->tmp_x = id->tmp_x->next;
		ft_skip_spaces(&id->tmp_x);
		if ((id->tmp_x != NULL && id->tmp_x->state == G)
			&& ((id->tmp_x->next != NULL && id->tmp_x->next->type == ' ')
				|| (id->tmp_x->next == NULL)))
			id->is_expand = 1;
		final = ft_skip_direction(&id->tmp_x, my_env, &id->is_amb, 0);
		add_back_node_her(&(id->tmp_cmd->her), new_node_her(final, -1, id->j,
				id->is_expand));
		id->j++;
	}
}

void	ft_check_redirection(t_pre *id, t_environment *my_env)
{
	char	*final;

	final = NULL;
	while ((id->tmp_x) != NULL && (redirection(id->tmp_x)
			&& id->tmp_x->state == G))
	{
		if (id->tmp_x != NULL && (redirection(id->tmp_x)
				&& id->tmp_x->type != HERE_DOC))
			ft_fill_redirection(id, my_env, final);
		else if ((id->tmp_x != NULL && id->tmp_x->type == HERE_DOC
				&& id->tmp_x->state == G))
			ft_fill_her(id, my_env, final);
	}
	if (id->tmp_x != NULL && !(id->tmp_x->type == '|' && id->tmp_x->state == G))
		id->tmp_x = id->tmp_x->next;
}

void	ft_fill_red(t_command **cmd, t_splitor **x, t_environment *my_env)
{
	t_pre	id;

	if (cmd == NULL || x == NULL)
		return ;
	id.is_expand = 0;
	id.is_amb = 0;
	id.j = 0;
	id.i = 0;
	id.tmp_cmd = *cmd;
	id.tmp_x = *x;
	while (id.tmp_cmd != NULL && id.tmp_x != NULL)
	{
		id.tmp_cmd->doc = NULL;
		id.i = 0;
		while ((id.tmp_cmd != NULL && id.tmp_x != NULL)
			&& !(id.tmp_x->state == G && id.tmp_x->type == '|'))
		{
			ft_check_redirection(&id, my_env);
			id.i++;
		}
		ft_next(&id.tmp_x, &id.tmp_cmd);
	}
}
