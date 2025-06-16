#include "../../includes/minishell.h"
#include "../../includes/structs.h"


// char	**ft_double_and_sigle(t_token **tmp_t, t_env *env, int flag,
// 		char ***arr_join)


int	redirection(t_token *start)
{
	if ((start)->type == '<' || (start)->type == '>'
		|| (start)->type == TOKEN_REDIR_APPEND || (start)->type == TOKEN_HEREDOC)
		return (1);
	return (0);
}
int	ft_len_arg(char **arg)
{
	int	i;

	i = 0;
	if (arg == NULL || arg[0] == NULL)
		return (0);
	while (arg[i] != NULL)
	{
		i++;
	}
	return (i);
}

int	ft_search(char *s, char *d)
{
	int	i;
	int	j;
	int	len;

	i = 0;
	j = 0;
	len = ft_strlen(s);
	while (s[i] && s[i])
	{
		if (s[i] == d[j])
			j++;
		if (len == j && s[i + 1] == d[j])
			return (1);
		i++;
	}
	return (0);
}

void	ft_go_to_env(char **s, char *arg, int *i, t_env **env)
{
	t_env	*tmp_env;

	*s = NULL;
	tmp_env = *env;
	while (tmp_env != NULL)
	{
		if (ft_search(tmp_env->name, arg + (*i)))
		{
			*s = ft_strdup(tmp_env->value);
			break ;
		}
		else
			*s = NULL;
		tmp_env = tmp_env->next;
	}
}

char	*ft_expand(char *arg, t_env **env, t_minibash b)
{
	t_expand_heredoc	id;

	id.index = 0;
	id.str = NULL;
	while (env != NULL && arg[id.index])
	{
		if (ft_search("$\"\"", arg))
			return (id.str = ft_strdup(""), id.str);
		else if (arg[id.index] == '$')
		{
			if (arg[id.index + 1] == '?')
				return (id.expanded_line = ft_itoa(b.exit_status), id.str = ft_strdup(id.expanded_line), free(id.expanded_line), id.str);
			id.index++;
			if (arg[id.index] == '\0')
				return (id.str = ft_strdup("$"), id.str);
			if (arg[id.index] == '\"' || arg[id.index] == '\'')
				return (id.str = ft_strdup(""), id.str);
			if (!ft_isalnum(arg[id.index]) || ft_isdigit(arg[id.index]))
				return (id.str);
			ft_go_to_env(&id.str, arg, &id.index, env);
		}
		id.index++;
	}
	return (id.str);
}

char	**ft_join_arg(char **arg, char **join)
{
	t_ps	ps;

	ps.idx = 0;
	ps.j = 0;
	ps.arg_len = ft_len_arg(arg);
	ps.join_len = ft_len_arg(join);
	ps.new_args = malloc(((ps.arg_len + ps.join_len) + 1)
			* sizeof(char *));
	ps.new_args[0] = NULL;
	if (arg != NULL)
	{
		while (arg[ps.idx] != NULL)
		{
			ps.new_args[ps.j] = ft_strdup(arg[ps.idx]);
			ps.j++;
			ps.idx++;
		}
	}
	ps.idx = 0;
	while (join[ps.idx])
		ps.new_args[ps.j++] = ft_strdup(join[ps.idx++]);
	ps.new_args[ps.j] = NULL;
	free_argument_array(arg);
	return (ps.new_args);
}

void	ft_join_arr(char ***arr_join, char *value)
{
	int		len_of_arr;
	char	*str;

	len_of_arr = ft_len_arg(*arr_join);
	if (value == NULL)
		return ;
	if (len_of_arr == 0)
	{
		*arr_join = NULL;
		*arr_join = malloc((1 + 1) * sizeof(char *));
		(*arr_join)[0] = ft_strdup(value);
		(*arr_join)[1] = NULL;
	}
	else
	{
		str = ft_strdup(value);
		len_of_arr--;
		(*arr_join)[len_of_arr] = ft_strjoin((*arr_join)[len_of_arr], str);
		free(str);
	}
}

char	**ft_split_expand(char ***arr_join, char *s)
{
	char	**expand_split;

	expand_split = NULL;
	if (s != NULL)
	{
		expand_split = ft_split(s, ' ');
		if (ft_len_arg(expand_split) > 0)
		{
			if (s[0] == ' ')
				*arr_join = ft_join_arg(*arr_join, expand_split);
			else
			{
				ft_join_arr(arr_join, expand_split[0]);
				*arr_join = ft_join_arg(*arr_join, expand_split + 1);
			}
		}
	}
	else
	{
		if (s == NULL)
			return (*arr_join);
		else if (s[0] == '\0')
			return (ft_join_arr(arr_join, s), *arr_join);
	}
	return (free(s), free_argument_array(expand_split), *arr_join);
}

void	ft_join_qs(char ***arr_join, t_token **tmp_t,
		t_env *env, int j, t_minibash b)
{
	char	*s;

	s = NULL;
	while ((*tmp_t) != NULL && ((*tmp_t)->state == Double || (*tmp_t)->state == Single))
	{
		if ((*tmp_t) != NULL && (*tmp_t)->state != Single && (*tmp_t)->type == '$'
			&& j == 1)
		{
			if ((*tmp_t)->type == '$' && (*tmp_t)->state == Normal && j == 1)
			{
				s = ft_expand((*tmp_t)->value, &env, b);
				ft_split_expand(arr_join, s);
			}
			else if ((*tmp_t)->type == '$' && (*tmp_t)->state == Double && j == 1)
			{
				s = ft_expand((*tmp_t)->value, &env, b);
				ft_join_arr(arr_join, s);
				free(s);
			}
		}
		else if ((*tmp_t) != NULL)
			ft_join_arr(arr_join, (*tmp_t)->value);
		(*tmp_t) = (*tmp_t)->next;
	}
}

void	ft_join_word_part_2(char ***arr_join, t_token **tmp_t,
		t_env *env, int j, t_minibash b)
{
	char	*s;

	s = NULL;
	if ((*tmp_t) != NULL && (*tmp_t)->state != Single && (*tmp_t)->type == '$'
		&& j == 1)
	{
		if ((*tmp_t)->type == '$' && (*tmp_t)->state == Normal && j == 1)
		{
			s = ft_expand((*tmp_t)->value, &env, b);
			ft_split_expand(arr_join, s);
		}
		else if ((*tmp_t)->type == '$' && (*tmp_t)->state == Double && j == 1)
		{
			s = ft_expand((*tmp_t)->value, &env, b);
			ft_join_arr(arr_join, s);
			free(s);
		}
	}
	else if ((*tmp_t) != NULL && ((*tmp_t)->state == Normal && (*tmp_t)->type == -1))
		ft_join_arr(arr_join, (*tmp_t)->value);
	else if ((*tmp_t) != NULL && ((*tmp_t)->state == Double || (*tmp_t)->state == Single))
		ft_join_arr(arr_join, (*tmp_t)->value);
	if ((*tmp_t) != NULL && (*tmp_t)->type != ' ' && !(redirection(*tmp_t)
			&& (*tmp_t)->state == Normal))
		(*tmp_t) = (*tmp_t)->next;
}

void	ft_join_words(char ***arr_join, t_token **tmp_t,
		t_env *env, int j, t_minibash b)
{
	while ((*tmp_t) != NULL && (*tmp_t)->state == Normal && ((*tmp_t)->type == '\"'
			|| (*tmp_t)->type == '\''))
	{
		if (((*tmp_t) != NULL && (*tmp_t)->state == Normal)
			&& ((*tmp_t)->type == '\"' || (*tmp_t)->type == '\''))
			(*tmp_t) = (*tmp_t)->next;
		ft_join_qs(arr_join, tmp_t, env, j, b);
		ft_join_word_part_2(arr_join, tmp_t, env, j, b);
	}
}

void	ft_join_next(char ***arr_join, t_token **tmp_x, t_env *env,
		int j, t_minibash b)
{
	char	*s;

	s = NULL;
	while ((*tmp_x) != NULL && (*tmp_x)->state == Normal && ((*tmp_x)->type == -1
			|| (*tmp_x)->type == '$'))
	{
		if ((*tmp_x)->type == '$' && (*tmp_x)->state == Normal && j == 1)
		{
			s = ft_expand((*tmp_x)->value, &env, b);
			ft_split_expand(arr_join, s);
		}
		else
		{
			ft_join_arr(arr_join, (*tmp_x)->value);
		}
		(*tmp_x) = (*tmp_x)->next;
	}
}

void	ft_join_double(char ***arr_join, t_token **tmp_t, t_env *env, int j, t_minibash b)
{
	char	*s;

	s = NULL;
	if ((*tmp_t) != NULL && ((*tmp_t)->state != Single && (*tmp_t)->type == '$')
		&& j == 1)
	{
		if ((*tmp_t)->type == '$' && (*tmp_t)->state == Normal && j == 1)
		{
			s = ft_expand((*tmp_t)->value, &env, b);
			ft_split_expand(arr_join, s);
		}
		else if ((*tmp_t)->type == '$' && (*tmp_t)->state == Double && j == 1)
		{
			s = ft_expand((*tmp_t)->value, &env, b);
			ft_join_arr(arr_join, s);
			free(s);
		}
		(*tmp_t) = (*tmp_t)->next;
	}
	ft_join_words(arr_join, tmp_t, env, 1, b);
	ft_join_next(arr_join, tmp_t, env, 1, b);
}

void	process_quoted(t_token **tok_ptr, t_env *env, int flag, char ***arg_arr, t_minibash b)
{
	char	*s;

	s = NULL;
	while (((*tok_ptr) != NULL) && !(redirection(*tok_ptr) && (*tok_ptr)->state == Normal) && ((*tok_ptr)->state == Double || (*tok_ptr)->state == Single
			|| (*tok_ptr)->type == '\"' || (*tok_ptr)->type == '\''))
	{
		if ((*tok_ptr) != NULL && ((*tok_ptr)->state == Double && (*tok_ptr)->type == '$')
			&& flag == 1)
		{
			s = ft_expand((*tok_ptr)->value, &env, b);
			ft_split_expand(arg_arr, s);
		}
		else if ((*tok_ptr) != NULL && ((*tok_ptr)->state == Double
				|| (*tok_ptr)->state == Single))
			join_to_arg_array(arg_arr, (*tok_ptr)->value);
		else if ((*tok_ptr) != NULL && (((*tok_ptr)->type == '$')
				|| (*tok_ptr)->type == -1))
			join_to_arg_array(arg_arr, (*tok_ptr)->value);
		(*tok_ptr) = (*tok_ptr)->next;
		ft_join_double(arg_arr, tok_ptr, env, flag, b);
	}
}

int	get_arg_count(char **arr)
{
	int	count;

	count = 0;
	if (!arr)
		return (0);
	while (arr[count])
		count++;
	return (count);
}

void	process_redirections(t_cmd **cmd_list, t_token **tokens, t_env *env)
{
	(void)cmd_list;
	(void)tokens;
	(void)env;
}

// void	ft_fill_redirection(t_pre *id, t_env *env, char *final)
// {
// 	if (id->tmp_t != NULL && id->tmp_t->type == '>' && id->tmp_t->state == Normal)
// 	{
// 		id->tmp_t = id->tmp_t->next;
// 		ft_skip_spaces(&id->tmp_t);
// 		final = ft_skip_direction(&id->tmp_t, env, &id->is_amb, 1);
// 		ft_add_redir(&(id->tmp_cmd->doc), ft_new_redir(final, '>', id->is_amb));
// 	}
// 	else if (id->tmp_t != NULL && id->tmp_t->type == '<'
// 		&& id->tmp_t->state == Normal)
// 	{
// 		id->tmp_t = id->tmp_t->next;
// 		ft_skip_spaces(&id->tmp_t);
// 		final = ft_skip_direction(&id->tmp_t, env, &id->is_amb, 1);
// 		ft_add_redir(&(id->tmp_cmd->doc), ft_new_redir(final, '<', id->is_amb));
// 	}
// 	else if (id->tmp_t != NULL && id->tmp_t->type == DREDIR_OUT
// 		&& id->tmp_t->state == Normal)
// 	{
// 		id->tmp_t = id->tmp_t->next;
// 		ft_skip_spaces(&id->tmp_t);
// 		final = ft_skip_direction(&id->tmp_t, env, &id->is_amb, 1);
// 		ft_add_redir(&(id->tmp_cmd->doc), ft_new_redir(final, DREDIR_OUT,
// 				id->is_amb));
// 	}
// }