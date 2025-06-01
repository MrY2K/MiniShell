/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajelloul <ajelloul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 10:03:12 by ajelloul          #+#    #+#             */
/*   Updated: 2025/06/01 11:48:34 by ajelloul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdbool.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/wait.h>
/*	readline	*/
# include <readline/readline.h>
/* HISTORY*/
# include <readline/history.h>
/*	opendir	*/
# include <dirent.h>

/* errno : cd  */
# include <errno.h>

/*  	HEADERS			*/

# include "enums.h"
# include "structs.h"
# include "prototypes.h"
# include "macros.h"
# include "../src/lib/libft.h"

#endif