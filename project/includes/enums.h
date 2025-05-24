/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enums.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achoukri <achoukri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 09:56:20 by ajelloul          #+#    #+#             */
/*   Updated: 2025/05/24 16:40:28 by achoukri         ###   ########.fr       */
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

#endif
