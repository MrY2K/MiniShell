/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achoukri <achoukri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 11:08:12 by ajelloul          #+#    #+#             */
/*   Updated: 2025/06/21 02:31:31 by achoukri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
	An ambiguous redirect occurs when the shell cannot determine exactly 
	which file the redirection should target, 
		typically due to variable expansion issues

		echo hello > $VAR

	Variable expands to multiple words:
	
		$ FILES="file1.txt file2.txt"
		$ echo hello > $FILES

	Variable expands to empty/nothing 

		$ EMPTY=""
		$ echo hello > $EMPTY
		
	Variable expands to filename with spaces

	$ SPACED="my file.txt"
	$ echo hello > $SPACED

*/

void	handle_append_redirect(t_minibash *bash, char *file, int is_ambig)
{
	int	fd;

	if (is_ambig)
		display_ambiguous_errno(bash, 1);
	if (!file || !file[0])
		display_syntax_error(bash);
	fd = open(file, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fd < 0)
	{
		perror("minishell");
		bash->exit_status = 1;
		exit(1);
	}
	if (dup2(fd, 1) < 0)
	{
		perror("dup2");
		bash->exit_status = 1;
		exit(1);
	}
	close(fd);
}

void	handle_output_redirect(t_minibash *bash, char *file, int is_ambig)
{
	int	fd;

	if (is_ambig)
		display_ambiguous_errno(bash, 1);
	if (!file || !file[0])
		display_syntax_error(bash);
	fd = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
	{
		perror("minishell");
		bash->exit_status = 1;
		exit(1);
	}
	if (dup2(fd, 1) < 0)
	{
		perror("dup2");
		bash->exit_status = 1;
		exit(1);
	}
	close(fd);
}

void	handle_input_redirect(t_minibash *bash, char *file, int is_ambig)
{
	int	fd;

	if (is_ambig)
		display_ambiguous_errno(bash, 1);
	if (!file || !file[0])
		display_syntax_error(bash);
	fd = open(file, O_RDONLY, 0644);
	if (fd < 0)
	{
		perror("minishell");
		bash->exit_status = 1;
		exit(1);
	}
	if (dup2(fd, STDOUT_FILENO) < 0)
	{
		perror("dup2");
		bash->exit_status = 1;
		exit(1);
	}
	close(fd);
}

void	handle_redirections(t_minibash *bash, t_cmd *cmd)
{
	t_redirect	*red;

	red = cmd->red;
	while (red)
	{
		if (red->type == TOKEN_REDIR_OUT)
			handle_output_redirect(bash, red->file_path, red->is_ambig);
		else if (red->type == TOKEN_REDIR_IN)
			handle_input_redirect(bash, red->file_path, red->is_ambig);
		else if (red->type == TOKEN_REDIR_APPEND)
			handle_append_redirect(bash, red->file_path, red->is_ambig);
		red = red->next;
	}
}

int	validate_redirection_file(t_cmd *list)
{
	t_cmd	*cmd;
	int		fd;

	if (list == NULL)
		return (0);
	cmd = list;
	while (cmd->red)
	{
		fd = -1;
		if (cmd->red->type == TOKEN_REDIR_APPEND)
			fd = open(cmd->red->file_path,
					O_CREAT | O_WRONLY | O_APPEND, 0644);
		else if (cmd->red->type == TOKEN_REDIR_OUT)
			fd = open(cmd->red->file_path,
					O_CREAT | O_WRONLY | O_TRUNC, 0644);
		else if (cmd->red->type == TOKEN_REDIR_IN)
			fd = open(cmd->red->file_path, O_RDONLY, 0644);
		if (fd < 0)
			return (1);
		close(fd);
		cmd->red = cmd->red->next;
	}
	return (0);
}
