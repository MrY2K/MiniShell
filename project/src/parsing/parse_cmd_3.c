/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd_3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achoukri <achoukri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 02:13:26 by achoukri          #+#    #+#             */
/*   Updated: 2025/06/21 02:21:33 by achoukri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_expand(char *arg, t_env **env)
{
	t_expand_heredoc	id;

	id.i = 0;
	id.s = NULL;
	while (env != NULL && arg[id.i])
	{
		if (ft_search("$\"\"", arg))
			return (id.s = ft_strdup(""), id.s);
		else if (arg[id.i] == '$')
		{
			if (arg[id.i + 1] == '?')
				return (id.s = ft_itoa((*env)->exit_status), id.s);
			id.i++;
			if (arg[id.i] == '\0')
				return (id.s = ft_strdup("$"), id.s);
			if (arg[id.i] == '\"' || arg[id.i] == '\'')
				return (id.s = ft_strdup(""), id.s);
			if (!ft_isalnum(arg[id.i]) || ft_isdigit(arg[id.i]))
				return (id.s);
			ft_go_to_env(&id.s, arg, &id.i, env);
		}
		id.i++;
	}
	return (id.s);
}

char	**process_word(t_token **tok_ptr, t_env *env, int flag, char ***arg_arr)
{
	char	*s;

	s = NULL;
	while ((*tok_ptr) != NULL
		&& (*tok_ptr)->state == N
		&& (*tok_ptr)->type != ' '
		&& (*tok_ptr)->type != '|'
		&& !is_redirection(*tok_ptr)
		&& !is_quote(*tok_ptr))
	{
		if ((*tok_ptr)->type == '$' && flag == 1)
		{
			s = ft_expand((*tok_ptr)->value, &env);
			ft_split_expand(arg_arr, s);
		}
		else
			ft_join_arr(arg_arr, (*tok_ptr)->value);
		*tok_ptr = (*tok_ptr)->next;
		ft_join_words(arg_arr, tok_ptr, env, flag);
	}
	return (*arg_arr);
}
