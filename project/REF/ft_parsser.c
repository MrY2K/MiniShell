/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achoukri <achoukri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 18:00:47 by rel-mora          #+#    #+#             */
/*   Updated: 2025/05/29 20:32:48 by achoukri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_command(t_splitor **x, t_command **cmd, t_environment *my_env)
{
	t_splitor	*tmp_x;
	t_command	**tmp_cmd;

	tmp_cmd = cmd;
	tmp_x = *x;
	while (tmp_x != NULL)
		ft_add_command(cmd, ft_new_command(&tmp_x, my_env));
	ft_fill_red(tmp_cmd, x, my_env);
}

// ? appends new_command to the end of the command linked list
void	ft_add_command(t_command **lst, t_command *new)
{
	t_command	*last;

	if (!lst || !new)
		return ;
	if (*lst == NULL)
		*lst = new;
	else
	{
		last = ft_last_command(*lst);
		last->next = new;
	}
}

// ? Find the last node in the linked list
t_command	*ft_last_command(t_command *lst)
{
	t_command	*last;

	last = lst;
	if (!lst)
		return (NULL);
	while (last->next != NULL)
		last = last->next;
	return (last);
}

// ? Creates a command node   //     echo "Hi" | echo 'Bye'

t_command	*ft_new_command(t_splitor **tmp_x, t_environment *my_env)
{
	t_command	*new_node;

	new_node = malloc(sizeof(t_command));
	
	new_node->arg = NULL;
	new_node->content = NULL;
	new_node->len = 0;
	new_node->is_pipe = 0;
	new_node->doc = NULL;
	new_node->her = NULL;
	new_node->ar_env = NULL;
	
	// ? Found a Pipe
	if (((*tmp_x) != NULL && ((*tmp_x)->type == '|' && (*tmp_x)->state == G)))
	{
		ft_join_arr(&(new_node->arg), (*tmp_x)->in);
		new_node->is_pipe = 1;
		(*tmp_x) = (*tmp_x)->next;
	}
	
	else if ((*tmp_x) != NULL)
		ft_not_pipe(&new_node, tmp_x, my_env);
	
	if (new_node->arg != NULL && new_node->arg[0] != NULL)
		new_node->content = new_node->arg[0];
	
	new_node->next = NULL;
	
	return (new_node);
}

int	ft_check_null(char ***arr_join, t_command **new_node, t_splitor **tmp_x)
{
	if (((*tmp_x) != NULL && (*tmp_x)->next != NULL && ((*tmp_x)->state == G
				&& (*tmp_x)->next->state == G)) && (((*tmp_x)->type == '\"'
				&& (*tmp_x)->next->type == '\"') || ((*tmp_x)->type == '\''
				&& (*tmp_x)->next->type == '\'')))
	{
		(*tmp_x) = (*tmp_x)->next;
		(*tmp_x) = (*tmp_x)->next;
		ft_join_arr(arr_join, "");
		if ((*arr_join)[0] != NULL)
		{
			(*new_node)->arg = ft_join_arg((*new_node)->arg, (*arr_join));
			ft_free_argment(*arr_join);
			*arr_join = NULL;
		}
		(*new_node)->next = NULL;
		return (1);
	}
	return (0);
}

int	ft_ckeck_repeate_quote(char ***arr_join, t_command **new_node,
		t_splitor **tmp_x)
{
	while (((*tmp_x) != NULL && (*tmp_x)->next != NULL && ((*tmp_x)->state == G
				&& (*tmp_x)->next->state == G)) && (((*tmp_x)->type == '\"'
				&& (*tmp_x)->next->type == '\"') || ((*tmp_x)->type == '\''
				&& (*tmp_x)->next->type == '\''))
		&& ((*tmp_x)->next->next != NULL
			&& (redirection((*tmp_x)->next->next) != 1
				&& (*tmp_x)->next->next->type != 32)))
	{
		(*tmp_x) = (*tmp_x)->next;
		(*tmp_x) = (*tmp_x)->next;
	}
	if (ft_check_null(arr_join, new_node, tmp_x))
		return (1);
	return (0);
}

int	ft_check_gene_quote(t_command **new_node, t_splitor **tmp_x,
		t_environment *my_env, char ***arr_join)
{
	if ((*tmp_x) != NULL && (*tmp_x)->state == G && (*tmp_x)->type != '\"'
		&& (*tmp_x)->type != '\'' && (*tmp_x)->type != '|')
	{
		ft_word(tmp_x, my_env, 1, arr_join);
		if ((*arr_join) != NULL && (*arr_join)[0] != NULL)
		{
			(*new_node)->arg = ft_join_arg((*new_node)->arg, (*arr_join));
			ft_free_argment(*arr_join);
			*arr_join = NULL;
		}
		return (1);
	}
	else if ((*tmp_x) != NULL && ((*tmp_x)->state == D || (*tmp_x)->state == S))
	{
		ft_double_and_sigle(tmp_x, my_env, 1, arr_join);
		if ((*arr_join) != NULL && (*arr_join)[0] != NULL)
		{
			(*new_node)->arg = ft_join_arg((*new_node)->arg, (*arr_join));
			ft_free_argment(*arr_join);
			*arr_join = NULL;
		}
		return (1);
	}
	return (0);
}

void	ft_neuter_cmd(t_command **new_node, t_splitor **tmp_x,
		t_environment *my_env, char ***arr_join)
{
	if (ft_ckeck_repeate_quote(arr_join, new_node, tmp_x))
		return ;
	if (ft_check_gene_quote(new_node, tmp_x, my_env, arr_join))
		return ;
	else if ((*tmp_x) != NULL && (*tmp_x)->type != '|')
		(*tmp_x) = (*tmp_x)->next;
}

void	ft_not_pipe(t_command **new_node, t_splitor **tmp_x,
		t_environment *my_env)
{
	char	**join;

	join = NULL;
	while ((*tmp_x) != NULL && !((*tmp_x)->type == '|' && (*tmp_x)->state == G))
	{
		if ((*tmp_x) != NULL && (*tmp_x)->state == G && ((*tmp_x)->type != -1
				&& (*tmp_x)->type != '$'))
			ft_skip_not_word(tmp_x, my_env);
		if ((*tmp_x) != NULL && !((*tmp_x)->type == ' ' && (*tmp_x)->state == G))
			ft_neuter_cmd(new_node, tmp_x, my_env, &join);
		if ((*tmp_x) != NULL && ((*tmp_x)->type == ' ' && (*tmp_x)->state == G))
			ft_skip_spaces(tmp_x);
	}
}
