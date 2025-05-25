/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enums.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajelloul <ajelloul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 09:56:20 by ajelloul          #+#    #+#             */
/*   Updated: 2025/05/25 14:03:00 by ajelloul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENUMS_H
# define ENUMS_H

typedef enum e_status
{
	STATUS_OK,
	STATUS_ERROR,
	STATUS_INVALID_ARGUMENT,
	STATUS_MEMORY_FAILURE,
	STATUS_COMMAND_NOT_FOUND,
	STATUS_PERMISSION_DENIED,
	STATUS_EXECUTION_FAILURE
}	t_status;

typedef enum e_env_type
{
	ENV_NAME,
	ENV_VALUE,
	ENV_OLDPWD,
	ENV_PWD,
	ENV_PATH,
	ENV_EXEC,
	CMD_SIMPLE,
	CMD_COMPLEX,
	REDIRECT,
	HEREDOC,
	ALLOC_TYPE,
	ERROR_TYPE,
	CLEANUP,
	BUILTIN,
	CHILD_PROC,
	PARENT_PROC
}	t_env_type;

/*		Parsing	*/
typedef enum e_state
{
	Normal,
	Single,
	Double,
	NUL,
}	t_state;

typedef enum e_token_type 
{
    TOKEN_WORD,         // command olla argument olla chi filename
    TOKEN_PIPE,         // |
    TOKEN_REDIR_IN,     // <
    TOKEN_REDIR_OUT,    // >
    TOKEN_REDIR_APPEND, // >> 
    TOKEN_HEREDOC,      // << 
    TOKEN_NEWLINE,      // Potentially for internal use or if line ends unexpectedly
    TOKEN_EOF           // End of input 
} t_token_type;

#endif
