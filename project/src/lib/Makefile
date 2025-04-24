################################################
#                 DIRECTORIES                  #
################################################

BUILD_DIR    = build

################################################
#                  FILES                       #
################################################

NAME = libft.a

SRC = ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c \
		ft_isprint.c ft_strlen.c ft_memset.c ft_bzero.c \
		ft_memcpy.c ft_memmove.c ft_strlcpy.c ft_strlcat.c \
		ft_calloc.c ft_strdup.c ft_toupper.c ft_tolower.c \
		ft_strchr.c ft_strncmp.c ft_memchr.c ft_memcmp.c \
		ft_strnstr.c ft_atoi.c ft_strrchr.c ft_substr.c \
		ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c \
		ft_strmapi.c ft_striteri.c ft_putchar_fd.c \
		ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
		ft_lstnew.c ft_lstadd_front.c \
		ft_lstsize.c ft_lstlast.c \
		ft_lstadd_back.c ft_lstdelone.c \
		ft_lstclear.c ft_lstiter.c \
		ft_lstmap.c \
		ft_perror.c ft_error.c ft_error_msg.c\
		get_next_line_nl.c get_next_line_no_nl.c \
		is_int.c \
		ft_printf.c ft_putadd.c ft_putchar.c ft_putnbr_hex.c ft_putnbr_unsigned.c ft_putnbr.c ft_putstr.c \
		ft_swap.c \
		hex_to_int.c sort_int_tab.c \
		ft_atoi_base.c \

OBJ = $(SRC:%.c=$(BUILD_DIR)/%.o)

################################################
#             COMPILER SETTINGS                #
################################################

CC           = cc
CFLAGS       = -Wall -Wextra -Werror # -Ofast -fsanitize=address -Wunreachable-code

################################################
#                   RULES                      #
################################################

all: $(BUILD_DIR) $(NAME) 

$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)
	@echo "$(GREEN)Created build directory$(RESET)"

# Making the lib
$(NAME): $(OBJ)
	@ar rcs $(NAME) $(OBJ)
	@echo "$(GREEN)Archived! $(RESET)"

# Compiling into object files
$(BUILD_DIR)/%.o: %.c libft.h
	$(CC) $(CFLAGS) -c $< -o $@

################################################
#                 CLEANING                     #
################################################

clean:
	@rm -rf $(OBJ)
	@echo "$(RED)Cleaned obj files! $(RESET)"

fclean: clean
	@rm -f $(NAME) $(OBJ)
	@echo "$(RED)Removed lib! $(RESET)"

re: fclean all

################################################
#                 .PHONY                       #
################################################

.PHONY: clean

################################################
#                 COLORS                       #
################################################

GREEN = \033[0;32m
RED   = \033[0;31m
RESET = \033[0m