# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: go-donne <go-donne@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/14 17:52:51 by go-donne          #+#    #+#              #
#    Updated: 2025/01/17 19:47:19 by go-donne         ###   ########.fr        #
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
INC_DIR = inc
LIBFT_DIR = libft


#	⭐	⭐	⭐	⭐	⭐	⭐	⭐
#	COMPILER CONFIGURATION		#
#	⭐	⭐	⭐	⭐	⭐	⭐	⭐

# Clang compiler
CC = cc

# Compilation flags as given in subject
CFLAGS = -Wall -Wextra -Werror


# Extra debug flags
DEBUG_FLAGS = -g3 -DDEBUG
# 3 specifies max debug info (all compiler debug info, allows macro expansion debugging, allows seeing variables, line numbers, source code...)
# -DDEBUG defines preprocessor macro, enables conditional compilation using #ifdef DEBUG

DEBUG_FLAGS += -fno-omit-frame-pointer
# preserves frame pointer register

DEBUG_FLAGS += -fsanitize=address
# ASan


# Add includes/ directory and libft includes
INCLUDES = -I includes -I libft



#	⭐	⭐	⭐	⭐	⭐	⭐	⭐
#			SOURCE FILES		#
#	⭐	⭐	⭐	⭐	⭐	⭐	⭐

# Core functionality
SRC_FILES = pipex.c parse.c child.c execute.c

# Utility functions
SRC_FILES += utils_error_handling.c utils_cleanup.c utils_system_calls.c

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
	@echo "$(BLUE)Created object directory$(RESET)"

# Program compilation - depends on object directory
$(NAME): $(LIBFT) $(OBJS)
	@echo "$(YELLOW)Linking $(BOLD)$(NAME)$(RESET)"
	@$(CC) $(CFLAGS) $(OBJS) -L$(LIBFT_DIR) -lft -o $(NAME)
	@echo "$(GREEN)$(BOLD)$(NAME) successfully compiled!$(RESET)"

# Object file compilation - explicit dependency on headers
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c includes/pipex.h | $(OBJ_DIR)
	@echo "$(CYAN)Compiling $(ITALIC)$<$(RESET)"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Compile libft
$(LIBFT):
	@echo "$(YELLOW)Compiling libft...$(RESET)"
	@make -C $(LIBFT_DIR)
	@echo "$(GREEN)libft compilation complete!$(RESET)"
# -C dir: change to directory, execute commands relative to this dir, change back when done



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
	@rm -f $(NAME)
	@make -C $(LIBFT_DIR) fclean
	@echo "$(GREEN)All generated files cleaned!$(RESET)"

re:
	@echo "$(YELLOW)Rebuilding...$(RESET)"
	@$(MAKE) fclean
	@$(MAKE) all



#	⭐	⭐	⭐	⭐	⭐	⭐	⭐
#		SPECIAL RULES			#
#	⭐	⭐	⭐	⭐	⭐	⭐	⭐

# Declare phony targets (that don't create files)
.PHONY: all clean fclean re

# Build with debug information
debug: CFLAGS += -g
debug: $(OBJS)
	@echo "Debug build complete!"

# Rule to build object files with debug flags
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c includes/pipex.h | $(OBJ_DIR)
    @echo "$(CYAN)Compiling $(ITALIC) $<$(RESET) with debug flags"
    @$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@



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

# tput: terminal control command:
#	setaf n sets the ANSI foreground color (text color)
#	Numbers 1-6 correspond to different colours
#	sgr0 resets all attributes back to default
#	These commands output the actual ANSI escape sequences

# RESET: returns terminal to normal

# Colour scheme:
# Blue:		directory creation
# Cyan:		file compilation
# Yellow:	process starts
# Green:	success messages
# Red:		cleaning operations



#	⭐	⭐	⭐	⭐	⭐	⭐	⭐
#		BUILD GUIDE				#
#	⭐	⭐	⭐	⭐	⭐	⭐	⭐

# Available build commands:

# make			: Regular build with standard error checking
# make debug	: Build with debug symbols for GDB/LLDB
