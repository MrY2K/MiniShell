/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enums.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achoukri <achoukri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 09:56:20 by ajelloul          #+#    #+#             */
/*   Updated: 2025/06/12 23:46:57 by achoukri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENUMS_H
# define ENUMS_H


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
	Normal , // G
	Single, // S
	Double, // D
	NUL,
}	t_state;





// typedef enum e_token
// {
// 	nothing = 0,
// 	WORD = -1,
// 	WHITE_SPACE = ' ',
// 	NEW_LINE = '\n',
// 	QOUTE = '\'',
// 	DOUBLE_QUOTE = '\"',
// 	ENV = '$',
// 	PIPE_LINE = '|',
// 	REDIR_IN = '<',
// 	REDIR_OUT = '>',
// 	HERE_DOC,
// 	DREDIR_OUT,
// }						t_token;



typedef enum e_token_type 
{
    TOKEN_WORD = -1,         // command olla argument olla chi filename
	TOKEN_SPACE = ' ',
    TOKEN_PIPE = '|',         // |
	TOKEN_ENV = '$',
    TOKEN_REDIR_IN = '<',     // <
    TOKEN_REDIR_OUT = '>',    // >
    TOKEN_REDIR_APPEND, // >>  //       DREDIR_OUT 🆘
    TOKEN_HEREDOC,      // << 
    TOKEN_NEWLINE = '\n',      // Potentially for internal use or if line ends unexpectedly
    TOKEN_EOF,           // End of input 
	TOKEN_WHITE_SPACE = 32,
	TOKEN_SINGLE_QUOTE = '\'',
	TOKEN_DOUBLE_QUOTE = '\"'
} t_token_type;

#endif
