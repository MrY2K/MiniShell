/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achoukri <achoukri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 22:12:52 by achoukri          #+#    #+#             */
/*   Updated: 2025/06/21 20:18:27 by achoukri         ###   ########.fr       */
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
# include <string.h>

# include <string.h> // bsbah chi errno f cd builtins 

/*  	HEADERS			*/

/*	 directory state	*/

#include <sys/stat.h>

# include "enums.h"
# include "structs.h"
# include "prototypes.h"
# include "macros.h"
# include "../src/lib/libft.h"

#endif