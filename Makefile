# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: go-donne <go-donne@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/14 17:52:51 by go-donne          #+#    #+#              #
#    Updated: 2025/01/26 10:39:25 by go-donne         ###   ########.fr        #
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

# Source files
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
#	COMPILER CONFIGURATION		#
#	⭐	⭐	⭐	⭐	⭐	⭐	⭐

# Clang
CC = cc

# Compilation flags as required by subject
CFLAGS = -Wall -Wextra -Werror

# Include path flags for header file resolution:
INCLUDES = -I $(INC_DIR) -I libft
# -I: Search path flag for preprocessor header lookups
#	- $(INC_DIR): Project's local header directory
#	- libft: Custom C library headers

# Debug configuration
DEBUG_FLAGS ?=

#	⭐	⭐	⭐	⭐	⭐	⭐	⭐
#			BUILD RULES			#
#	⭐	⭐	⭐	⭐	⭐	⭐	⭐

# Default target
all: $(OBJ_DIR) $(NAME)

# Create obj directory if it doesn't exist
$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)
	@echo "$(BLUE)Created object directory$(RESET)"

# Main program: regular / release build
$(NAME): $(LIBFT) $(OBJS)
	@echo "$(YELLOW)Linking $(NAME)$(RESET)"
	@$(CC) $(CFLAGS) $(OBJS) -L$(LIBFT_DIR) -lft -o $(NAME)
	@echo "$(GREEN)Build complete!$(RESET)"

# Regular object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(INC_DIR)/pipex.h | $(OBJ_DIR)
	@echo "$(CYAN)Compiling $<$(RESET)"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Debug build
debug: CFLAGS += $(DEBUG_FLAGS)
debug: $(OBJ_DIR) $(NAME_DEBUG)

# Debug program
$(NAME_DEBUG): $(LIBFT) $(OBJS)
	@echo "$(YELLOW)Linking debug build with flags: $(DEBUG_FLAGS)$(RESET)"
	@$(CC) $(CFLAGS) $(OBJS) -L$(LIBFT_DIR) -lft -o $(NAME_DEBUG)
	@echo "$(GREEN)Debug build complete!$(RESET)"

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

fclean: clean
	@echo "$(RED)Removing executable...$(RESET)"
	@rm -f $(NAME) $(NAME_DEBUG)
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
