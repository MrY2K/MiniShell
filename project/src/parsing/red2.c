#include "../../includes/minishell.h"


// char	*ft_fill_final(char **s)
// {
// 	int		i;
// 	char	*final;

// 	final = NULL;
// 	i = 0;
// 	while (s[i] != NULL)
// 	{
// 		final = ft_strjoin(final, s[i]);
// 		if (s[i + 1] != NULL)
// 			final = ft_strjoin(final, " ");
// 		i++;
// 	}
// 	return (final);
// }

// int	ft_check_ambiguous(t_token *tmp_t, t_env *env, t_minibash b)
// {
// 	char	*s;
// 	char	**str;

// 	s = NULL;
// 	while ((tmp_t) != NULL)
// 	{
// 		if ((tmp_t)->state == Normal && (is_redirection(tmp_t) || tmp_t->type == '|'
// 				|| tmp_t->type == ' '))
// 			break ;
// 		if ((tmp_t) != NULL && tmp_t->type == '$' && tmp_t->state == Normal)
// 		{
// 			s = ft_expand(tmp_t->value, &env, b);
// 			if (s == NULL || (s != NULL && (s[0] == ' ' || s[0] == '\0')))
// 				return (free(s), 1);
// 			str = ft_split(s, ' ');
// 			if (ft_len_arg(str) > 1)
// 				return (free(s), free_argument_array(str), 1);
// 			free(s);
// 			free_argument_array(str);
// 		}
// 		if ((tmp_t) != NULL)
// 			tmp_t = tmp_t->next;
// 	}
// 	return (0);
// }

// int	ft_check_quote(t_token **tmp_t, char **final)
// {
// 	while (((*tmp_t) != NULL && (*tmp_t)->next != NULL && ((*tmp_t)->state == Normal
// 				&& (*tmp_t)->next->state == Normal)) && (((*tmp_t)->type == '\"'
// 				&& (*tmp_t)->next->type == '\"') || ((*tmp_t)->type == '\''
// 				&& (*tmp_t)->next->type == '\''))
// 		&& ((*tmp_t)->next->next != NULL
// 			&& (redirection((*tmp_t)->next->next) != 1
// 				&& (*tmp_t)->next->next->type != 32
// 				&& (*tmp_t)->next->next->type == '$')))
// 	{
// 		(*tmp_t) = (*tmp_t)->next;
// 		(*tmp_t) = (*tmp_t)->next;
// 		return (1);
// 	}
// 	if (((*tmp_t) != NULL && (*tmp_t)->next != NULL && ((*tmp_t)->state == Normal
// 				&& (*tmp_t)->next->state == Normal)) && (((*tmp_t)->type == '\"'
// 				&& (*tmp_t)->next->type == '\"') || ((*tmp_t)->type == '\''
// 				&& (*tmp_t)->next->type == '\'')))
// 	{
// 		(*tmp_t) = (*tmp_t)->next;
// 		(*tmp_t) = (*tmp_t)->next;
// 		*final = ft_strdup("");
// 		return (1);
// 	}
// 	return (0);
// }

// char	*ft_skip_direction(t_token **tmp_t, t_env *env,
// 		int *is_amb, int her)
// {
// 	t_dir	id;

// 	id.str = NULL;
// 	id.final = NULL;
// 	if (ft_check_quote(tmp_t, &id.final))
// 		;
// 	else if ((*tmp_t) != NULL && (*tmp_t)->state == Normal && ((*tmp_t)->type == '\"'
// 			|| (*tmp_t)->type == '\''))
// 	{
// 		*is_amb = ft_check_ambiguous((*tmp_t), env);
// 		if (*is_amb == 1 && her == 1)
// 			return (NULL);
// 		ft_double_and_sigle(tmp_t, env, her, &id.str);
// 	}
// 	else if ((*tmp_t) != NULL && (*tmp_t)->state == Normal)
// 	{
// 		*is_amb = ft_check_ambiguous((*tmp_t), env);
// 		if (*is_amb == 1 && her == 1)
// 			return (NULL);
// 		ft_word(tmp_t, env, her, &id.str);
// 	}
// 	if (id.str != NULL)
// 		id.final = ft_fill_final(id.str);
// 	return (free_args(id.str), id.final);
// }


