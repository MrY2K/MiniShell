/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enums.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajelloul <ajelloul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 09:56:20 by ajelloul          #+#    #+#             */
/*   Updated: 2025/05/11 09:59:07 by ajelloul         ###   ########.fr       */
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

#endif
