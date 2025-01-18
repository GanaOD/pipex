# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: go-donne <go-donne@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/14 17:52:51 by go-donne          #+#    #+#              #
#    Updated: 2025/01/18 11:15:41 by go-donne         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#	⭐	⭐	⭐	⭐	⭐	⭐	⭐
#	PROGRAM CONFIGURATION		#
#	⭐	⭐	⭐	⭐	⭐	⭐	⭐

# Name of the executable
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

# Clang compiler
CC = cc

# Compilation flags as given in subject
CFLAGS = -Wall -Wextra -Werror


# Extra debug flags
DEBUG_FLAGS = -g3 -DDEBUG -fno-omit-frame-pointer -fsanitize=address
# 3:		specifies max debug info (all compiler debug info, allows macro expansion debugging, allows seeing variables, line numbers, source code...)
# -DDEBUG:	defines preprocessor macro, enables conditional compilation using #ifdef DEBUG
# -fno...:	preserves frame pointer register
# ASan


# Add inc/ directory and libft includes
INCLUDES = -I $(INC_DIR) -I libft



#	⭐	⭐	⭐	⭐	⭐	⭐	⭐
#			SOURCE FILES		#
#	⭐	⭐	⭐	⭐	⭐	⭐	⭐

# Core functionality
SRC_FILES = pipex.c parse.c child.c execute.c \
			utils_error_handling.c utils_cleanup.c utils_system_calls.c


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

# Debug program
$(NAME_DEBUG): $(LIBFT) $(OBJS_DEBUG)
	@echo "$(YELLOW)Linking debug build$(RESET)"
	@$(CC) $(CFLAGS) $(DEBUG_FLAGS) $(OBJS_DEBUG) -L$(LIBFT_DIR) -lft -o $(NAME_DEBUG)
	@echo "$(GREEN)Debug build complete!$(RESET)"

# Debug objects (with _debug suffix)
$(OBJ_DIR)/%_debug.o: $(SRC_DIR)/%.c $(INC_DIR)/pipex.h | $(OBJ_DIR)
	@echo "$(CYAN)Compiling $< (debug)$(RESET)"
	@$(CC) $(CFLAGS) $(DEBUG_FLAGS) $(INCLUDES) -c $< -o $@

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
	@rm -f $(NAME) $(NAME)_debug
	@make -C $(LIBFT_DIR) fclean
	@echo "$(GREEN)All generated files cleaned!$(RESET)"

re:
	@echo "$(YELLOW)Rebuilding...$(RESET)"
	@$(MAKE) fclean
	@$(MAKE) all


# Declare phony targets (that don't create files)
.PHONY: all clean fclean re debug




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

# Available build commands as defined in .PHONY

# make or make all:	Default build
# make debug:			Build with debug flags
# make clean:			Remove object files
# make fclean:		Remove objects and executables (full clean)
# make re:			Rebuild from scratch (runs fclean then all)
