/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajelloul <ajelloul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 11:08:12 by ajelloul          #+#    #+#             */
/*   Updated: 2025/06/05 12:10:31 by ajelloul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


/*
	An ambiguous redirect occurs when the shell cannot determine exactly 
	which file the redirection should target, typically due to variable expansion issues

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
	{
		ft_putendl_fd("minishell: syntax error near unexpected token `newline'", 2);
		bash->exit_status = 1;
		exit(1);
	}
	fd = open(file, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fd < 0)
	{
		perror("minishell");
		bash->exit_status = 1;
		exit(1);
	}
	if (dup2(fd, 1) < 0)
	{
		perror ("dup2");
		bash->exit_status = 1;
		exit (1);
	}
	close(fd);
}

void	handle_output_redirect(t_minibash *bash, char *file, int is_ambig)
{
	int	fd;

	if (is_ambig)
		display_ambiguous_errno(bash, 1);
	if (!file || !file[0])
	{
		ft_putendl_fd("minishell: syntax error near unexpected token `newline'", 2);
		bash->exit_status = 1;
		exit(1);
	}
	fd = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
	{
		perror("minishell");
		bash->exit_status = 1;
		exit(1);
	}
	if (dup2(fd, 1) < 0)
	{
		perror ("dup2");
		bash->exit_status = 1;
		exit (1);
	}
	close(fd);
}

void	handle_input_redirect(t_minibash *bash, char *file, int is_ambig)
{
	int	fd;

	if (is_ambig)
		display_ambiguous_errno(bash, 1);
	if (!file || !file[0])
	{
		ft_putendl_fd("minishell: syntax error near unexpected token `newline'", 2);
		bash->exit_status = 1;
		exit(1);
	}
	fd = open(file, O_RDONLY, 0644);
	if (fd < 0)
	{
		perror("minishell");
		bash->exit_status = 1;
		exit(1);
	}
	if (dup2(fd, 1) < 0)
	{
		perror ("dup2");
		bash->exit_status = 1;
		exit (1);
	}
	close(fd);
}

void	handle_redirections(t_minibash *bash, t_cmd *cmd)
{
	t_redirect *red;

	red = cmd->redirections;
	while (red)
	{
		if (red->type == TOKEN_REDIR_OUT)
		{
			handle_output_redirect(bash, red->file_path, red->is_ambig);
		}
		if (red->type == TOKEN_REDIR_IN)
		{
			handle_input_redirect(bash, red->file_path, red->is_ambig);
		}
		if (red->type == TOKEN_REDIR_APPEND)
		{
			handle_append_redirect(bash, red->file_path, red->is_ambig);
		}
		red = red->next;
	}
}
