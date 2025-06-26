/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajelloul <ajelloul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 22:12:52 by achoukri          #+#    #+#             */
/*   Updated: 2025/06/21 22:22:56 by ajelloul         ###   ########.fr       */
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

/*	 directory state	*/

# include <sys/stat.h>

# include "enums.h"
# include "structs.h"
# include "prototypes.h"
# include "../src/lib/libft.h"

#endif