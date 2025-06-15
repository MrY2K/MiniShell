#include "../../includes/minishell.h"
#include "../../includes/structs.h"

void	free_cmd_list(t_cmd **cmd_list)
{
	t_cmd	*tmp;
	int		i;

	while (*cmd_list)
	{
		tmp = (*cmd_list)->next;
		// Free arguments array
		if ((*cmd_list)->argument)
		{
			i = 0;
			while ((*cmd_list)->argument[i])
				free((*cmd_list)->argument[i++]);
			free((*cmd_list)->argument);
		}
		// Free env_arr
		if ((*cmd_list)->env_arr)
		{
			i = 0;
			while ((*cmd_list)->env_arr[i])
				free((*cmd_list)->env_arr[i++]);
			free((*cmd_list)->env_arr);
		}
		free(*cmd_list);
		*cmd_list = tmp;
	}
}

// TODO: free redirections and heredocs if used
// void	free_red(t_cmd **cmd_list)
