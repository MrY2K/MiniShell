# todo NOT FINISHED : ADD THE LIB AND INCLUDE_DIR TO THE RULE SO I WONT RELINK AND CHECK FOR RELINKING
# it compiles lib without relink

################################################ MANDATORY #############################################



################################################
#             COMPILER SETTINGS                #
################################################

CC           = cc

CFLAGS       = -Wall -Wextra -Werror -I$(INCLUDE_DIR) # -Ofast -fsanitize=address -Wunreachable-code



################################################
# OS DETECTION && CLONING OUTSIDE DEPENDENCICY #
################################################

# UNAME_S := $(shell uname -s)
# ifeq ($(UNAME_S),Darwin)
# 	os_msg = "$(GREEN)OS DETECTED: MacOS$(RESET)"

# else ifeq ($(UNAME_S),Linux)
# 	os_msg = "$(GREEN)OS DETECTED: Linux$(RESET)"
# endif



################################################
#                 DIRECTORIES                  #
################################################

SRC_DIR      = src

BUILD_DIR    = $(SRC_DIR)/build

HELPER_DIR   = $(SRC_DIR)/helpers

INCLUDE_DIR  = $(SRC_DIR)/include

INCLUDE      = $(INCLUDE_DIR)/minishell.h



################################################
#                  FILES                       #
################################################

# Define the executable name
NAME         = minishell

# Define source files and their dependencies
SRCS         = $(SRC_DIR)/main.c \
				# $(HELPER_DIR)/helper1.c \
				# $(HELPER_DIR)/helper2.c \
				# Add more source files as needed

# OBJS         = $(SRCS:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o) # OLD
OBJS         = $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRCS)) #NEW

DEPS         = $(OBJS:.o=.d)



################################################
#                   RULES                      #
################################################

all: $(BUILD_DIR) $(NAME)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)
	echo "$(GREEN)Created build directory$(RESET)"



# Must Make Lib First
################################################
#                  libft                       #
################################################

# making libft.a
LIB_DIR    = $(SRC_DIR)/lib

LIB        = $(LIB_DIR)/libft.a

LIB_HDR    = $(LIB_DIR)/libft.h

LIB_SRC    = $(LIB_DIR)/ft_isalpha.c $(LIB_DIR)/ft_isdigit.c $(LIB_DIR)/ft_isalnum.c $(LIB_DIR)/ft_isascii.c \
		$(LIB_DIR)/ft_isprint.c $(LIB_DIR)/ft_strlen.c $(LIB_DIR)/ft_memset.c $(LIB_DIR)/ft_bzero.c \
		$(LIB_DIR)/ft_memcpy.c $(LIB_DIR)/ft_memmove.c $(LIB_DIR)/ft_strlcpy.c $(LIB_DIR)/ft_strlcat.c \
		$(LIB_DIR)/ft_calloc.c $(LIB_DIR)/ft_strdup.c $(LIB_DIR)/ft_toupper.c $(LIB_DIR)/ft_tolower.c \
		$(LIB_DIR)/ft_strchr.c $(LIB_DIR)/ft_strncmp.c $(LIB_DIR)/ft_memchr.c $(LIB_DIR)/ft_memcmp.c \
		$(LIB_DIR)/ft_strnstr.c $(LIB_DIR)/ft_atoi.c $(LIB_DIR)/ft_strrchr.c $(LIB_DIR)/ft_substr.c \
		$(LIB_DIR)/ft_strjoin.c $(LIB_DIR)/ft_strtrim.c $(LIB_DIR)/ft_split.c $(LIB_DIR)/ft_itoa.c \
		$(LIB_DIR)/ft_strmapi.c $(LIB_DIR)/ft_striteri.c $(LIB_DIR)/ft_putchar_fd.c \
		$(LIB_DIR)/ft_putstr_fd.c $(LIB_DIR)/ft_putendl_fd.c $(LIB_DIR)/ft_putnbr_fd.c \
		$(LIB_DIR)/ft_lstnew.c $(LIB_DIR)/ft_lstadd_front.c \
		$(LIB_DIR)/ft_lstsize.c $(LIB_DIR)/ft_lstlast.c \
		$(LIB_DIR)/ft_lstadd_back.c $(LIB_DIR)/ft_lstdelone.c \
		$(LIB_DIR)/ft_lstclear.c $(LIB_DIR)/ft_lstiter.c \
		$(LIB_DIR)/ft_lstmap.c \
		$(LIB_DIR)/ft_perror.c $(LIB_DIR)/ft_error.c $(LIB_DIR)/ft_error_msg.c\
		$(LIB_DIR)/get_next_line_nl.c $(LIB_DIR)/get_next_line_no_nl.c \
		$(LIB_DIR)/is_int.c \
		$(LIB_DIR)/ft_printf.c $(LIB_DIR)/ft_putadd.c $(LIB_DIR)/ft_putchar.c $(LIB_DIR)/ft_putnbr_hex.c $(LIB_DIR)/ft_putnbr_unsigned.c $(LIB_DIR)/ft_putnbr.c $(LIB_DIR)/ft_putstr.c \
		$(LIB_DIR)/ft_swap.c \
		$(LIB_DIR)/hex_to_int.c $(LIB_DIR)/sort_int_tab.c \
		$(LIB_DIR)/ft_atoi_base.c \
	
$(LIB): $(LIB_SRC) $(LIB_HDR)
	@mkdir -p $(LIB_DIR)/build
	@$(MAKE) -C $(LIB_DIR)
	@echo "$(GREEN)Made $(LIB)$(RESET)"



# Linking
$(NAME): $(OBJS) $(LIB)
	$(CC) $(CFLAGS) $(OBJS) $(LIB) -o $(NAME)
	echo "$(GREEN)Built $(NAME)$(RESET)"



# Compiling into object files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c $(INCLUDE)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@



################################################
#                 CLEANING                     #
################################################

clean:
	rm -rf $(BUILD_DIR)
	echo "$(RED)Cleaned build directory$(RESET)"

fclean: clean
	rm -f $(NAME)
	echo "$(RED)Removed executable$(RESET)"

re: fclean all

libclean:
	@$(MAKE) clean -C $(LIB_DIR)
	@echo "$(RED)Cleaned $(LIB_DIR)$(RESET)"

libfclean:
	@$(MAKE) fclean -C $(LIB_DIR)
	@echo "$(RED)Full Cleaned $(LIB_DIR)$(RESET)"



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



################################################
#                   HELP                       #
################################################

help:	



################################################
#             create man pages                 #
################################################


