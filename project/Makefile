# todo NOT FINISHED : ADD THE LIB AND INCLUDE_DIR TO THE RULE SO I WONT RELINK AND CHECK FOR RELINKING

################################################ MANDATORY #############################################

################################################
#                 DIRECTORIES                  #
################################################

SRC_DIR      = src
HELPER_DIR   = $(SRC_DIR)/helpers
LIB_DIR      = lib # Improved Libft folder
BUILD_DIR    = build
INCLUDE_DIR  = include

################################################
#                  FILES                       #
################################################

# Define the executable name
NAME         = my_program

# Define source files and their dependencies
SRCS         = $(SRC_DIR)/main.c \
				$(HELPER_DIR)/helper1.c \
				$(HELPER_DIR)/helper2.c \
				# Add more source files as needed

OBJS         = $(SRCS:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)

DEPS         = $(OBJS:.o=.d)

################################################
#             COMPILER SETTINGS                #
################################################

CC           = cc
CFLAGS       = -Wall -Wextra -Werror # -Ofast -fsanitize=address -Wunreachable-code

################################################
# OS DETECTION && CLONING OUTSIDE DEPENDENCICY #
################################################

# UNAME_S := $(shell uname -s)
# ifeq ($(UNAME_S),Darwin)
# 	os_msg = "$(GREEN)OS DETECTED: MacOS$(RESET)"

# else ifeq ($(UNAME_S),Linux)
# 	os_msg = "$(GREEN)OS DETECTED: Linux$(RESET)"
# endif

# MLX_BIN:
# 	if [ ! -d "MLX" ]; then \
# 		git clone https://github.com/MrY2K/MLX.git; \
# 	fi

################################################
#                   RULES                      #
################################################

all: $(BUILD_DIR) $(NAME)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)
	echo "$(GREEN)Created build directory$(RESET)"

# Linking
$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	echo "$(GREEN)Built $(NAME)$(RESET)"

# Compiling into object files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

################################################ BONUS ################################################

# Define bonus-specific directories, files, and rules as needed

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


