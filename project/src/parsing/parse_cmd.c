#include "../../includes/minishell.h"

void	push_command(t_cmd **list, t_cmd *new_cmd)
{
	t_cmd	*last;

	if (!list || !new_cmd)
		return ;
	if (!*list)
	{
		*list = new_cmd;
	}
	else
	{
		last = *list;
		while (last->next)
			last = last->next;
		last->next = new_cmd;
	}
}

t_cmd	*parse_new_command(t_token **token, t_env *env)
{
	(void) env;
	(void) token;
	t_cmd	*new;

	new = (t_cmd *) malloc (sizeof(t_cmd));
	if (!new)
		return (NULL);
	new->main_cmd = NULL;
	new->argument = NULL;
	new->env_arr = NULL;
	new->has_ambiguous = 0;
	new->pipe = 0;
	new->needs_expansion = 0;
	new->arg_len = 0;
	new->heredoc = NULL;
	new->redirections = NULL;
	new->next = NULL;
	
	// hand pipes


	return (NULL);
}

void	parse_command(t_token **token, t_cmd **cmd, t_env *env)
{
	t_token	*tmp_token;
	t_cmd	**tmp_cmd;
	
	(void)env;
	
	tmp_cmd = cmd;
	tmp_token = *token;
	while (tmp_token)
	{
		push_command(tmp_cmd, parse_new_command(&tmp_token, env));
	}

}
