# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: go-donne <go-donne@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/14 17:52:51 by go-donne          #+#    #+#              #
#    Updated: 2025/01/24 11:31:51 by go-donne         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#	⭐	⭐	⭐	⭐	⭐	⭐	⭐
#	PROGRAM CONFIGURATION		#
#	⭐	⭐	⭐	⭐	⭐	⭐	⭐

# Name of executable
NAME = pipex
NAME_DEBUG = $(NAME)_debug

# Directory structure
SRC_DIR = src
OBJ_DIR = obj
INC_DIR = inc
LIBFT_DIR = libft


#	⭐	⭐	⭐	⭐	⭐	⭐	⭐
#	COMPILER CONFIGURATION		#
#	⭐	⭐	⭐	⭐	⭐	⭐	⭐

# Clang
CC = cc

# Compilation flags as required by subject
CFLAGS = -Wall -Wextra -Werror


# Address Sanitizer (ASan) configuration
ASAN_FLAGS = -fsanitize=address -fsanitize=undefined \
             -fno-sanitize-recover=all \
             -fsanitize=float-divide-by-zero \
             -fsanitize=float-cast-overflow \
             -fno-sanitize=null \
             -fno-sanitize=alignment

# Memory Sanitizer (MSan) configuration
MSAN_FLAGS = -fsanitize=memory


# Debug flags with ASan (default)
DEBUG_FLAGS = -g3 -DDEBUG -fno-omit-frame-pointer $(ASAN_FLAGS)


# Debug flags with MSan (alternative)
DEBUG_MSAN_FLAGS = -g3 -DDEBUG -fno-omit-frame-pointer $(MSAN_FLAGS)



# "SIMPLE" DEBUG BUILD WITH -g ?? e.g. when just using valgrind ???


# Include path flags for header file resolution:
INCLUDES = -I $(INC_DIR) -I libft
# -I: Search path flag for preprocessor header lookups
#	- $(INC_DIR): Project's local header directory
#	- libft: Custom C library headers



#	⭐	⭐	⭐	⭐	⭐	⭐	⭐
#			SOURCE FILES		#
#	⭐	⭐	⭐	⭐	⭐	⭐	⭐

# Core functionality
SRC_FILES = pipex.c parse.c child.c execute.c \
			utils_error_handling.c utils_parsing.c \
			utils_system_calls.c utils_cleanup.c


# Generate full paths
SRCS = $(addprefix $(SRC_DIR)/, $(SRC_FILES))

OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

OBJS_DEBUG = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%_debug.o)

# Libft external library
LIBFT = $(LIBFT_DIR)/libft.a




#	⭐	⭐	⭐	⭐	⭐	⭐	⭐
#			BUILD RULES			#
#	⭐	⭐	⭐	⭐	⭐	⭐	⭐

# Default rule
all: $(OBJ_DIR) $(NAME)

# Create obj directory if it doesn't exist
$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)
	@echo "$(BLUE)Created object directory$(RESET)"

# Regular build
$(NAME): $(LIBFT) $(OBJS)
	@echo "$(YELLOW)Linking $(NAME)$(RESET)"
	@$(CC) $(CFLAGS) $(OBJS) -L$(LIBFT_DIR) -lft -o $(NAME)
	@echo "$(GREEN)Build complete!$(RESET)"

# Regular objects
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(INC_DIR)/pipex.h | $(OBJ_DIR)
	@echo "$(CYAN)Compiling $<$(RESET)"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Debug build
debug: $(OBJ_DIR) $(NAME_DEBUG)

# MSan debug build
debug_msan: $(OBJ_DIR) $(NAME)_debug_msan


# Debug program
$(NAME_DEBUG): $(LIBFT) $(OBJS_DEBUG)
	@echo "$(YELLOW)Linking debug build$(RESET)"
	@$(CC) $(CFLAGS) $(DEBUG_FLAGS) $(OBJS_DEBUG) -L$(LIBFT_DIR) -lft -o $(NAME_DEBUG)
	@echo "$(GREEN)Debug build complete!$(RESET)"

# Debug objects (with _debug suffix)
$(OBJ_DIR)/%_debug.o: $(SRC_DIR)/%.c $(INC_DIR)/pipex.h | $(OBJ_DIR)
	@echo "$(CYAN)Compiling $< (debug)$(RESET)"
	@$(CC) $(CFLAGS) $(DEBUG_FLAGS) $(INCLUDES) -c $< -o $@


# MSan debug program
$(NAME)_debug_msan: $(LIBFT) $(OBJS_DEBUG_MSAN)
	@echo "$(YELLOW)Linking MSan debug build$(RESET)"
	@$(CC) $(CFLAGS) $(DEBUG_MSAN_FLAGS) $(OBJS_DEBUG_MSAN) -L$(LIBFT_DIR) -lft -o $(NAME)_debug_msan
	@echo "$(GREEN)MSan debug build complete!$(RESET)"

# MSan debug objects
$(OBJ_DIR)/%_debug_msan.o: $(SRC_DIR)/%.c $(INC_DIR)/pipex.h | $(OBJ_DIR)
	@echo "$(CYAN)Compiling $< (MSan debug)$(RESET)"
	@$(CC) $(CFLAGS) $(DEBUG_MSAN_FLAGS) $(INCLUDES) -c $< -o $@


# Libft
$(LIBFT):
	@echo "$(YELLOW)Building libft$(RESET)"
	@make -C $(LIBFT_DIR)




#	⭐	⭐	⭐	⭐	⭐	⭐	⭐
#		CLEANUP RULES			#
#	⭐	⭐	⭐	⭐	⭐	⭐	⭐

clean:
	@echo "$(RED)Cleaning object files...$(RESET)"
	@rm -rf $(OBJ_DIR)
	@make -C $(LIBFT_DIR) clean
	@echo "$(GREEN)Object files cleaned!$(RESET)"

clean_debug:
	@rm -rf $(OBJ_DIR)/*_debug.o
	@echo "$(GREEN)Debug objects cleaned!$(RESET)"

clean_debug_msan:
	@rm -rf $(OBJ_DIR)/*_debug_msan.o
	@echo "$(GREEN)MSan debug objects cleaned!$(RESET)"

fclean: clean
	@echo "$(RED)Removing executable...$(RESET)"
	@rm -f $(NAME) $(NAME)_debug $(NAME)_debug_msan
	@make -C $(LIBFT_DIR) fclean
	@echo "$(GREEN)All generated files cleaned!$(RESET)"

re:
	@echo "$(YELLOW)Rebuilding...$(RESET)"
	@$(MAKE) fclean
	@$(MAKE) all


# Declare phony targets (that don't create files)
.PHONY: all \
		clean clean_debug clean_debug_msan \
		fclean \
		re \
		debug debug_msan
