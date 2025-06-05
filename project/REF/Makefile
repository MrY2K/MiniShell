SRC= minishell.c \
	lexer_utils.c \
	lexer.c \
	lexer_utils_2.c \
	ft_handle_synx.c \
	ft_nodes_env.c \
	ft_free.c \
	ft_parsser.c\
	ft_parsser_utils_2.c \
	ft_parsser_utils.c \
	ft_direction.c \
	ft_direction_utils.c \
	skip_redirection.c \
	ft_skip.c \
	ft_join.c \
	ft_join_general.c \
	utils.c \
	ft_condition.c \
	ft_execut_cmd/execute.c ft_execut_cmd/functions.c ft_execut_cmd/ft_cd.c   ft_execut_cmd/ft_pwd.c \
    ft_execut_cmd/ft_export.c ft_execut_cmd/ft_env.c    ft_execut_cmd/ft_unset.c ft_execut_cmd/ft_echo.c  ft_execut_cmd/redirectons.c ft_execut_cmd/execut_pipe.c \
	ft_execut_cmd/execut_pipe_1.c ft_execut_cmd/funct_redir.c ft_execut_cmd/ft_exit.c   ft_execut_cmd/ft_herdoc.c ft_execut_cmd/utilis_herdoc.c  ft_execut_cmd/envarement.c\
	ft_execut_cmd/execute_1.c ft_execut_cmd/execute_2.c  ft_execut_cmd/ft_execute_3.c   ft_execut_cmd/signal.c   ft_execut_cmd/ft_export_2.c ft_execut_cmd/ft_export_1.c      ft_execut_cmd/ft_herdoc_1.c \

OBJ = ${SRC:.c=.o}

CFLAGS = -Wall -Wextra -Werror 

CC = cc


NAME = minishell

LIBFT = ./includes/libft/libft.a
FLDLIBFT= ./includes/libft

#include readLine in MacOS
READLINE_DIR := $(shell brew --prefix readline)
INRL = -I$(READLINE_DIR)/include
LNRL = -L$(READLINE_DIR)/lib -lreadline -lhistory -lncurses


all : ${LIBFT} ${NAME}

%.o: %.c minishell.h structures.h
	${CC} ${CFLAGS} $(INRL) -c  $< -o $@

${NAME} : minishell.h structures.h ${OBJ}
		${CC} ${CFLAGS} ${OBJ} ${LIBFT}  ${INRL} ${LNRL}   -o ${NAME}

${LIBFT}:
	make -C ${FLDLIBFT}
	make bonus -C ${FLDLIBFT}

clean:
	make fclean -C ./includes/libft
	@rm -rf ${OBJ}
	@echo "\033[34mminishell is clean from object files\033[0m"

fclean: clean
	@rm -rf ${NAME}
	@echo "\033[34mminishell is clean from program file\033[0m"

re : fclean all

.PHONY: all clean fclean re