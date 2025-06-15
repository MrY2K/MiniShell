#include "../../includes/minishell.h"
#include "../../includes/structs.h"

void	process_quoted(t_token **tok_ptr, t_env *env, int flag, char ***arg_arr)
{
	process_word(tok_ptr, env, flag, arg_arr);
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

// void	ft_fill_redirection(t_pre *id, t_environment *my_env, char *final)
// {
// 	if (id->tmp_x != NULL && id->tmp_x->type == '>' && id->tmp_x->state == G)
// 	{
// 		id->tmp_x = id->tmp_x->next;
// 		ft_skip_spaces(&id->tmp_x);
// 		final = ft_skip_direction(&id->tmp_x, my_env, &id->is_amb, 1);
// 		ft_add_redir(&(id->tmp_cmd->doc), ft_new_redir(final, '>', id->is_amb));
// 	}
// 	else if (id->tmp_x != NULL && id->tmp_x->type == '<'
// 		&& id->tmp_x->state == G)
// 	{
// 		id->tmp_x = id->tmp_x->next;
// 		ft_skip_spaces(&id->tmp_x);
// 		final = ft_skip_direction(&id->tmp_x, my_env, &id->is_amb, 1);
// 		ft_add_redir(&(id->tmp_cmd->doc), ft_new_redir(final, '<', id->is_amb));
// 	}
// 	else if (id->tmp_x != NULL && id->tmp_x->type == DREDIR_OUT
// 		&& id->tmp_x->state == G)
// 	{
// 		id->tmp_x = id->tmp_x->next;
// 		ft_skip_spaces(&id->tmp_x);
// 		final = ft_skip_direction(&id->tmp_x, my_env, &id->is_amb, 1);
// 		ft_add_redir(&(id->tmp_cmd->doc), ft_new_redir(final, DREDIR_OUT,
// 				id->is_amb));
// 	}
// }