
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

# include "enums.h"
# include "structs.h"
# include "prototypes.h"
# include "macros.h"
# include "../src/lib/libft.h"

#endif