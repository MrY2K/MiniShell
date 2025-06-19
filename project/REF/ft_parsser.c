
#include "minishell.h"
#include "structures.h"




void	ft_neuter_cmd(t_command **new_node, t_splitor **tmp_x,
		t_environment *my_env, char ***arr_join);

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

void	ft_join_arr(char ***arr_join, char *in)
{
	int		len_of_arr;
	char	*str;

	len_of_arr = ft_len_arg(*arr_join);
	if (in == NULL)
		return ;
	if (len_of_arr == 0)
	{
		*arr_join = NULL;
		*arr_join = malloc((1 + 1) * sizeof(char *));
		(*arr_join)[0] = ft_strdup(in);
		(*arr_join)[1] = NULL;
	}
	else
	{
		str = ft_strdup(in);
		len_of_arr--;
		(*arr_join)[len_of_arr] = ft_strjoin((*arr_join)[len_of_arr], str);
		free(str);
	}
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

void	ft_join_next(char ***arr_join, t_splitor **tmp_x, t_environment *my_env,
		int j)
{
	char	*s;

	s = NULL;
	while ((*tmp_x) != NULL && (*tmp_x)->state == G && ((*tmp_x)->type == -1
			|| (*tmp_x)->type == '$'))
	{
		if ((*tmp_x)->type == '$' && (*tmp_x)->state == G && j == 1)
		{
			s = ft_expand((*tmp_x)->in, &my_env);
			ft_split_expand(arr_join, s);
		}
		else
		{
			ft_join_arr(arr_join, (*tmp_x)->in);
		}
		(*tmp_x) = (*tmp_x)->next;
	}
}

void	ft_join_double(char ***arr_join, t_splitor **tmp_x,
		t_environment *my_env, int j)
{
	char	*s;

	s = NULL;
	if ((*tmp_x) != NULL && ((*tmp_x)->state != S && (*tmp_x)->type == '$')
		&& j == 1)
	{
		if ((*tmp_x)->type == '$' && (*tmp_x)->state == G && j == 1)
		{
			s = ft_expand((*tmp_x)->in, &my_env);
			ft_split_expand(arr_join, s);
		}
		else if ((*tmp_x)->type == '$' && (*tmp_x)->state == D && j == 1)
		{
			s = ft_expand((*tmp_x)->in, &my_env);
			ft_join_arr(arr_join, s);
			free(s);
		}
		(*tmp_x) = (*tmp_x)->next;
	}
	ft_join_words(arr_join, tmp_x, my_env, 1);
	ft_join_next(arr_join, tmp_x, my_env, 1);
}

char	**ft_double_and_sigle(t_splitor **tmp_x, t_environment *my_env, int j,
		char ***arr_join)
{
	char	*s;

	s = NULL;
	while (((*tmp_x) != NULL) && !(redirection(*tmp_x) && (*tmp_x)->state == G)
		&& ((*tmp_x)->state == D || (*tmp_x)->state == S
			|| (*tmp_x)->type == '\"' || (*tmp_x)->type == '\''))
	{
		if ((*tmp_x) != NULL && ((*tmp_x)->state == D && (*tmp_x)->type == '$')
			&& j == 1)
		{
			s = ft_expand((*tmp_x)->in, &my_env);
			ft_split_expand(arr_join, s);
		}
		else if ((*tmp_x) != NULL && ((*tmp_x)->state == D
				|| (*tmp_x)->state == S))
			ft_join_arr(arr_join, (*tmp_x)->in);
		else if ((*tmp_x) != NULL && (((*tmp_x)->type == '$')
				|| (*tmp_x)->type == -1))
			ft_join_arr(arr_join, (*tmp_x)->in);
		(*tmp_x) = (*tmp_x)->next;
		ft_join_double(arr_join, tmp_x, my_env, j);
	}
	return (*arr_join);
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

//FREE
void	ft_free_argment(char **arg)
{
	int	i;

	i = 0;
	if (arg == NULL)
		return ;
	while (arg[i] != NULL)
	{
		free(arg[i]);
		arg[i] = NULL;
		i++;
	}
	free(arg);
	arg = NULL;
}


//UTILS

char	**ft_join_arg(char **arg, char **join)
{
	t_ps	ps;

	ps.idx = 0;
	ps.j = 0;
	ps.len_of_arg = ft_len_arg(arg);
	ps.len_of_join = ft_len_arg(join);
	ps.new_arg = malloc(((ps.len_of_arg + ps.len_of_join) + 1)
			* sizeof(char *));
	ps.new_arg[0] = NULL;
	if (arg != NULL)
	{
		while (arg[ps.idx] != NULL)
		{
			ps.new_arg[ps.j] = ft_strdup(arg[ps.idx]);
			ps.j++;
			ps.idx++;
		}
	}
	ps.idx = 0;
	while (join[ps.idx])
		ps.new_arg[ps.j++] = ft_strdup(join[ps.idx++]);
	ps.new_arg[ps.j] = NULL;
	ft_free_argment(arg);
	return (ps.new_arg);
}



void	ft_skip_not_word(t_splitor **tmp_x, t_environment *my_env)
{
	char	**str;

	str = NULL;
	while ((*tmp_x) != NULL && ((*tmp_x)->type == '<' || (*tmp_x)->type == '>'
			|| (*tmp_x)->type == DREDIR_OUT || (*tmp_x)->type == HERE_DOC))
	{
		(*tmp_x) = (*tmp_x)->next;
		ft_skip_spaces(tmp_x);
		while ((*tmp_x) != NULL && (*tmp_x)->state == G
			&& ((*tmp_x)->type == '\"' || (*tmp_x)->type == '\''))
			(*tmp_x) = (*tmp_x)->next;
		if ((*tmp_x) != NULL && (*tmp_x)->state == G && (*tmp_x)->type != '\"'
			&& (*tmp_x)->type != '\'' && (*tmp_x)->type != '|')
			ft_word(tmp_x, my_env, 0, &str);
		else if ((*tmp_x) != NULL && ((*tmp_x)->state == D
				|| (*tmp_x)->state == S))
			ft_double_and_sigle(tmp_x, my_env, 0, &str);
	}
	free_args(str);
}


void	ft_join_double_2(char ***arr_join, t_splitor **tmp_x,
		t_environment *my_env, int j)
{
	char	*s;

	s = NULL;
	while ((*tmp_x) != NULL && ((*tmp_x)->state == D || (*tmp_x)->state == S))
	{
		if ((*tmp_x) != NULL && (*tmp_x)->state != S && (*tmp_x)->type == '$'
			&& j == 1)
		{
			if ((*tmp_x)->type == '$' && (*tmp_x)->state == G && j == 1)
			{
				s = ft_expand((*tmp_x)->in, &my_env);
				ft_split_expand(arr_join, s);
			}
			else if ((*tmp_x)->type == '$' && (*tmp_x)->state == D && j == 1)
			{
				s = ft_expand((*tmp_x)->in, &my_env);
				ft_join_arr(arr_join, s);
				free(s);
			}
		}
		else if ((*tmp_x) != NULL)
			ft_join_arr(arr_join, (*tmp_x)->in);
		(*tmp_x) = (*tmp_x)->next;
	}
}

void	ft_join_word_2(char ***arr_join, t_splitor **tmp_x,
		t_environment *my_env, int j)
{
	char	*s;

	s = NULL;
	if ((*tmp_x) != NULL && (*tmp_x)->state != S && (*tmp_x)->type == '$'
		&& j == 1)
	{
		if ((*tmp_x)->type == '$' && (*tmp_x)->state == G && j == 1)
		{
			s = ft_expand((*tmp_x)->in, &my_env);
			ft_split_expand(arr_join, s);
		}
		else if ((*tmp_x)->type == '$' && (*tmp_x)->state == D && j == 1)
		{
			s = ft_expand((*tmp_x)->in, &my_env);
			ft_join_arr(arr_join, s);
			free(s);
		}
	}
	else if ((*tmp_x) != NULL && ((*tmp_x)->state == G && (*tmp_x)->type == -1))
		ft_join_arr(arr_join, (*tmp_x)->in);
	else if ((*tmp_x) != NULL && ((*tmp_x)->state == D || (*tmp_x)->state == S))
		ft_join_arr(arr_join, (*tmp_x)->in);
	if ((*tmp_x) != NULL && (*tmp_x)->type != ' ' && !(redirection(*tmp_x)
			&& (*tmp_x)->state == G))
		(*tmp_x) = (*tmp_x)->next;
}


void	ft_join_words(char ***arr_join, t_splitor **tmp_x,
		t_environment *my_env, int j)
{
	while ((*tmp_x) != NULL && (*tmp_x)->state == G && ((*tmp_x)->type == '\"'
			|| (*tmp_x)->type == '\''))
	{
		if (((*tmp_x) != NULL && (*tmp_x)->state == G)
			&& ((*tmp_x)->type == '\"' || (*tmp_x)->type == '\''))
			(*tmp_x) = (*tmp_x)->next;
		ft_join_double_2(arr_join, tmp_x, my_env, j);
		ft_join_word_2(arr_join, tmp_x, my_env, j);
	}
}

char	**ft_word(t_splitor **tmp_x, t_environment *my_env, int j,
		char ***arr_join)
{
	char	*s;

	s = NULL;
	while ((*tmp_x) != NULL && ((*tmp_x)->state == G && (*tmp_x)->type != ' '
			&& (*tmp_x)->type != '|' && (!redirection(*tmp_x) && !quotes(*tmp_x)
				&& (*tmp_x)->state == G)))
	{
		if ((*tmp_x)->type == '$' && (*tmp_x)->state == G && j == 1)
		{
			s = ft_expand((*tmp_x)->in, &my_env);
			ft_split_expand(arr_join, s);
		}
		else if ((*tmp_x)->type == '$' && (*tmp_x)->state == D && j == 1)
		{
			s = ft_expand((*tmp_x)->in, &my_env);
			ft_split_expand(arr_join, s);
		}
		else
			ft_join_arr(arr_join, (*tmp_x)->in);
		(*tmp_x) = (*tmp_x)->next;
		ft_join_words(arr_join, tmp_x, my_env, j);
	}
	return (*arr_join);
}

int	redirection(t_splitor *start)
{
	if ((start)->type == '<' || (start)->type == '>'
		|| (start)->type == DREDIR_OUT || (start)->type == HERE_DOC)
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