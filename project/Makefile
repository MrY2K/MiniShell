# ANSI Color codes
RESET        = \033[0m
BOLD         = \033[1m
BLACK        = \033[30m
RED          = \033[31m
GREEN        = \033[32m
YELLOW       = \033[33m
BLUE         = \033[34m
MAGENTA      = \033[35m
CYAN         = \033[36m
WHITE        = \033[37m
BGBLACK      = \033[40m
BGRED        = \033[41m
BGGREEN      = \033[42m
BGYELLOW     = \033[43m
BGBLUE       = \033[44m
BGMAGENTA    = \033[45m
BGCYAN       = \033[46m
BGWHITE      = \033[47m


# Define the executable name
NAME         = minishell

# COMPILER SETTINGS

CC           = cc
READLINE_DIR = /goinfre/ajelloul/homebrew/opt/readline

CFLAGS       = -Wall -Wextra -Werror -I$(INCLUDE_DIR) -I$(READLINE_DIR)/include -g
LDFLAGS      = -L$(READLINE_DIR)/lib -lreadline -lncurses


# Uncomment for extra optimization or debug flags
#CFLAGS      += -Ofast
#CFLAGS      += -fsanitize=address -g3
#CFLAGS      += -Wunreachable-code

# DIRECTORIES

SRC_DIR      = src
BUILD_DIR    = .build
INCLUDE_DIR  = includes


# directories
BUILTINS_DIR = $(SRC_DIR)/builtins
ENV_DIR      = $(SRC_DIR)/env
EXEC_DIR     = $(SRC_DIR)/exec
HEREDOC_DIR  = $(SRC_DIR)/heredoc
PARSING_DIR  = $(SRC_DIR)/parsing
REDIR_DIR    = $(SRC_DIR)/redirection
SIGNALS_DIR  = $(SRC_DIR)/signals
TOKEN_DIR    = $(SRC_DIR)/tokenizer
LIB_DIR      = $(SRC_DIR)/lib
ERROR_DIR    = $(SRC_DIR)/error

# HEADERS

HEADERS      = $(wildcard $(INCLUDE_DIR)/*.h)



# Define source files
MAIN_SRC     = $(SRC_DIR)/main.c

# Builtin sources
BUILTINS_SRC = $(wildcard $(BUILTINS_DIR)/*.c)


# Other module sources
ENV_SRC      = $(wildcard $(ENV_DIR)/*.c)
EXEC_SRC     = $(wildcard $(EXEC_DIR)/*.c)
HEREDOC_SRC  = $(wildcard $(HEREDOC_DIR)/*.c)
PARSING_SRC  = $(wildcard $(PARSING_DIR)/*.c)
REDIR_SRC    = $(wildcard $(REDIR_DIR)/*.c)
SIGNALS_SRC  = $(wildcard $(SIGNALS_DIR)/*.c)
TOKEN_SRC    = $(wildcard $(TOKEN_DIR)/*.c)
ERROR_SRC	 = $(wildcard $(ERROR_DIR)/*.c)

# Combine all sources
SRCS         = $(MAIN_SRC) \
               $(BUILTINS_SRC) \
               $(ENV_SRC) \
               $(EXEC_SRC) \
               $(HEREDOC_SRC) \
               $(PARSING_SRC) \
               $(REDIR_SRC) \
               $(SIGNALS_SRC) \
               $(TOKEN_SRC) \
			   $(ERROR_SRC)


# Generate object file paths
OBJS         = $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRCS))
DEPS         = $(OBJS:.o=.d)

# LIBFT

LIB          = $(LIB_DIR)/libft.a
LIB_HDR      = $(LIB_DIR)/libft.h


# RULES

.PHONY: all clean fclean re libclean libfclean debug norm  practice

# Default target
all:  $(NAME)

# Create build directory structure
$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)
	@mkdir -p $(BUILD_DIR)/builtins
	@mkdir -p $(BUILD_DIR)/env
	@mkdir -p $(BUILD_DIR)/exec
	@mkdir -p $(BUILD_DIR)/heredoc
	@mkdir -p $(BUILD_DIR)/parsing
	@mkdir -p $(BUILD_DIR)/redirection
	@mkdir -p $(BUILD_DIR)/signals
	@mkdir -p $(BUILD_DIR)/tokenizer
	@mkdir -p $(BUILD_DIR)/error
	@printf "$(CYAN)$(BOLD)%s$(RESET)\n" "Build directory structure created"


# Compile libft
$(LIB): 
	@printf "$(CYAN)$(BOLD)%s$(RESET)\n" "Building libft..."
	@$(MAKE) -C $(LIB_DIR)
	@printf "$(GREEN)$(BOLD)%s$(RESET)\n" "✓ libft.a ready"

# Compile minishell
$(NAME): $(BUILD_DIR) $(LIB) $(OBJS)
	@printf "$(CYAN)$(BOLD)%s$(RESET)\n" "Linking minishell..."
	@$(CC) $(CFLAGS) $(OBJS) $(LIB) $(LDFLAGS) -o $(NAME)
	@printf "$(GREEN)$(BOLD)%s$(RESET)\n" "✓ $(NAME) successfully built!"
	@printf "$(GREEN)$(BOLD)%s$(RESET)\n" "Run ./minishell to start your shell!"

# Compile source files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c $(HEADERS)
	@printf "$(CYAN)%s$(RESET)\n" "Compiling $<..."
	@$(CC) $(CFLAGS) -MMD -c $< -o $@

# Clean objects
clean:
	@printf "$(YELLOW)%s$(RESET)\n" "Cleaning object files..."
	@rm -rf $(BUILD_DIR)
	@printf "$(RED)%s$(RESET)\n" "✓ Object files removed"

# Clean libft
libclean:
	@printf "$(YELLOW)%s$(RESET)\n" "Cleaning libft..."
	@$(MAKE) clean -C $(LIB_DIR)
	@printf "$(RED)%s$(RESET)\n" "✓ libft cleaned"

# Full clean library
libfclean:
	@printf "$(YELLOW)%s$(RESET)\n" "Full cleaning libft..."
	@$(MAKE) fclean -C $(LIB_DIR)
	@printf "$(RED)%s$(RESET)\n" "✓ libft completely cleaned"

# Full clean
fclean: clean libfclean
	@printf "$(YELLOW)%s$(RESET)\n" "Removing executable..."
	@rm -f $(NAME)
	@printf "$(RED)%s$(RESET)\n" "✓ $(NAME) removed"

# Rebuild
re: fclean all

# Debug mode
debug: CFLAGS += -g3 -fsanitize=address
debug: re
	@printf "$(MAGENTA)%s$(RESET)\n" "Debug mode enabled with -g3 and -fsanitize=address"

# Banner


# Norminette check
norm:
	@printf "$(YELLOW)%s$(RESET)\n" "Running norminette..."
	@norminette $(SRC_DIR)
	@norminette $(INCLUDE_DIR)
	@printf "$(GREEN)%s$(RESET)\n" "✓ Norminette check completed"


practice : all clean
	@clear

