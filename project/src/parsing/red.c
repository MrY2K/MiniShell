#include "../../includes/minishell.h"

void	process_redirections(t_cmd **cmd_list, t_token **tokens, t_env *env)
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