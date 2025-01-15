# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: go-donne <go-donne@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/14 17:52:51 by go-donne          #+#    #+#              #
#    Updated: 2025/01/15 17:52:14 by go-donne         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#	⭐	⭐	⭐	⭐	⭐	⭐	⭐
#	PROGRAM CONFIGURATION		#
#	⭐	⭐	⭐	⭐	⭐	⭐	⭐

# Name of the executable
NAME = pipex

# Directory structure
SRC_DIR = src
OBJ_DIR = obj
INC_DIR = includes
LIBFT_DIR = libft


#	⭐	⭐	⭐	⭐	⭐	⭐	⭐
#	COMPILER CONFIGURATION		#
#	⭐	⭐	⭐	⭐	⭐	⭐	⭐

# Clang compiler
CC = cc

# Compilation flags
CFLAGS = -Wall -Wextra -Werror

# Debug flags
DEBUG_FLAGS = -g3 -DDEBUG
DEBUG_FLAGS += -fno-omit-frame-pointer

# Add includes/ directory and libft includes
INCLUDES = -I includes -I libft


#	⭐	⭐	⭐	⭐	⭐	⭐	⭐
#			SOURCE FILES		#
#	⭐	⭐	⭐	⭐	⭐	⭐	⭐

# Core functionality
SRC_FILES = pipex.c parse.c execute.c

# Utility functions
SRC_FILES += utils.c utils_system_calls.c

# Generate full paths
SRCS = $(addprefix $(SRC_DIR)/, $(SRC_FILES))
# Creates a list of paths. If SRC_DIR is "src", then:
#	SRC_FILES is: pipex.c parse.c execute.c...
#	SRCS becomes: src/pipex.c src/parse.c src/execute.c...
# This tells make where to find source files

# Object files
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
# uses pattern substitution to create obj/.o from src/.c

# Libft external library
LIBFT = $(LIBFT_DIR)/libft.a


#	⭐	⭐	⭐	⭐	⭐	⭐	⭐
#			BUILD RULES			#
#	⭐	⭐	⭐	⭐	⭐	⭐	⭐

# Default target
all: $(OBJ_DIR) $(NAME)

# Create object directory first
$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)
	@echo "$(BLUE)Created object directory$(CLR_RMV)"

# Program compilation - depends on object directory
$(NAME): $(LIBFT) $(OBJS)
	@echo "$(YELLOW)Linking $(BOLD)$(NAME)$(CLR_RMV)"
	@$(CC) $(CFLAGS) $(OBJS) -L$(LIBFT_DIR) -lft -o $(NAME)
	@echo "$(GREEN)$(BOLD)$(NAME) successfully compiled!$(CLR_RMV)"

# Object file compilation - explicit dependency on headers
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c includes/pipex.h | $(OBJ_DIR)
	@echo "$(CYAN)Compiling $(ITALIC)$<$(CLR_RMV)"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Compile libft
$(LIBFT):
	@echo "$(YELLOW)Compiling libft...$(CLR_RMV)"
	@make -C $(LIBFT_DIR)
	@echo "$(GREEN)libft compilation complete!$(CLR_RMV)"


#	⭐	⭐	⭐	⭐	⭐	⭐	⭐
#		CLEANUP RULES			#
#	⭐	⭐	⭐	⭐	⭐	⭐	⭐

clean:
	@echo "$(RED)Cleaning object files...$(CLR_RMV)"
	@rm -rf $(OBJ_DIR)
	@make -C $(LIBFT_DIR) clean
	@echo "$(GREEN)Object files cleaned!$(CLR_RMV)"

fclean: clean
	@echo "$(RED)Removing executable...$(CLR_RMV)"
	@rm -f $(NAME)
	@make -C $(LIBFT_DIR) fclean
	@echo "$(GREEN)All generated files cleaned!$(CLR_RMV)"

re:
	@echo "$(YELLOW)Rebuilding...$(CLR_RMV)"
	@$(MAKE) fclean
	@$(MAKE) all


#	⭐	⭐	⭐	⭐	⭐	⭐	⭐
#		SPECIAL RULES			#
#	⭐	⭐	⭐	⭐	⭐	⭐	⭐

# Declare phony targets (targets that don't create files)
.PHONY: all clean fclean re

# Build with debug information
debug: CFLAGS += -g
debug: re
	@echo "Debug build complete!"


#	⭐	⭐	⭐	⭐	⭐	⭐	⭐
#	COLOURED OUTPUT CONFIG		#
#	⭐	⭐	⭐	⭐	⭐	⭐	⭐

# Terminal output colors
RED := $(shell tput setaf 1)
GREEN := $(shell tput setaf 2)
YELLOW := $(shell tput setaf 3)
BLUE := $(shell tput setaf 4)
CYAN := $(shell tput setaf 6)
RESET := $(shell tput sgr0)
BOLD := $(shell tput bold)


#	⭐	⭐	⭐	⭐	⭐	⭐	⭐
#		BUILD GUIDE				#
#	⭐	⭐	⭐	⭐	⭐	⭐	⭐

# Available build commands:

# make			: Regular build with standard error checking
# make debug	: Build with debug symbols for GDB/LLDB
# make dev		: Development build with extra warnings



#	⭐	⭐	⭐	⭐	⭐	⭐	⭐
#		INFO ON THIS MAKEFILE	#
#	⭐	⭐	⭐	⭐	⭐	⭐	⭐

# OUTPUT:

# Colour scheme:

# Blue for directory creation
# Cyan for file compilation
# Yellow for process starts
# Green for success messages
# Red for cleaning operations


# Text: informative messages, not actual commands (which are suppressed with initial @)
