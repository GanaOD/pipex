# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: go-donne <go-donne@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/14 17:52:51 by go-donne          #+#    #+#              #
#    Updated: 2025/01/22 11:44:26 by go-donne         ###   ########.fr        #
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

# Extra debug flags
DEBUG_FLAGS = -g3 -DDEBUG -fno-omit-frame-pointer -fsanitize=address

# -g3:		Maximum debug level. Includes:
#			- All compiler debug information
#			- Macro definitions and expansion
#			- Full symbol information for debuggers (variables, functions, line numbers)
#			- Maximum source code correlation
# -DDEBUG:	Defines DEBUG macro for preprocessor
#			- Enables code wrapped in #ifdef DEBUG conditional blocks
# -fno-omit-frame-pointer:
# 			- Maintains stack frame pointers in registers
#			- Improves debugger stack traces and profiling accuracy
# -fsanitize=address:
#			- Enables AddressSanitizer (ASan)


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
# Path and dependency resolution:
#	- SRCS:	Constructs full source paths by prefixing SRC_DIR to each file
#		Creates compilation unit list for build system
#	- OBJS:	Maps .c source files to corresponding .o object files
#		Preserves directory structure in build artifacts
#		Each object file becomes a dependency node in build graph
#	- OBJS_DEBUG:	Similar to OBJS but generates separate debug objects
#			Allows parallel existence of debug and release builds
#			Prevents object file collision between build types

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

clean_debug:
	@rm -rf $(OBJ_DIR)/*_debug.o
	@echo "$(GREEN)Debug objects cleaned!$(RESET)"

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
