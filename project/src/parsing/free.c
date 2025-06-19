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

void	free_argument_array(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return ;
	while (arr[i])
	{
		free(arr[i]);
		arr[i] = NULL;
		i++;
	}
	free(arr);
	arr = NULL;
}

// TODO: free redirections and heredocs if used
// void	free_red(t_cmd **cmd_list)
// void	ft_free_doc(t_redirect **doc)
// {
// 	t_redirect	*tmp;

// 	while (*doc != NULL)
// 	{
// 		tmp = *doc;
// 		*doc = (*doc)->next;
// 		if (tmp->store != NULL)
// 		{
// 			free(tmp->store);
// 			tmp->store = NULL;
// 		}
// 		free(tmp);
// 		tmp = NULL;
// 	}
// }
// TODO FREE HER AND DOC -> adde d
// void	ft_free_her(t_here_doc **her)
// {
// 	t_here_doc	*tmp;

// 	while (*her != NULL)
// 	{
// 		tmp = *her;
// 		*her = (*her)->next;
// 		if (tmp->heredoc_file != NULL)
// 		{
// 			free(tmp->heredoc_file);
// 			tmp->heredoc_file = NULL;
// 		}
// 		if (tmp->store != NULL)
// 		{
// 			free(tmp->store);
// 			tmp->store = NULL;
// 		}
// 		free(tmp);
// 		tmp = NULL;
// 	}
// }


// void	ft_free_command(t_command **cmd)
// {
// 	t_command	*tmp_cmd;
// 	t_command	*next_cmd;

// 	if (cmd == NULL || *cmd == NULL)
// 		return ;
// 	tmp_cmd = *cmd;
// 	while (tmp_cmd)
// 	{
// 		free_args(tmp_cmd->arg);
// 		if (tmp_cmd->doc)
// 			ft_free_doc(&tmp_cmd->doc);
// 		if (tmp_cmd->her)
// 			ft_free_her(&tmp_cmd->her);
// 		if (tmp_cmd->ar_env)
// 			ft_free_argment(tmp_cmd->ar_env);
// 		next_cmd = tmp_cmd->next;
// 		free(tmp_cmd);
// 		tmp_cmd = NULL;
// 		tmp_cmd = next_cmd;
// 	}
// }
