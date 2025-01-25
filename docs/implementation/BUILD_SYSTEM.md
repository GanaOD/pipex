# Build System Documentation

## Directory Structure

The build system is organized around several key directories:
- `src/`: Source files
- `obj/`: Compiled object files
- `inc/`: Header files
- `libft/`: Custom C library

## Compiler Configuration

### Base Configuration
The project uses Clang (`cc`) with standard warning flags:
- `-Wall`: Enable all common warnings
- `-Wextra`: Enable extra warning flags
- `-Werror`: Treat warnings as errors

### Debug Configuration
Debug builds include enhanced debugging capabilities:

#### Debug Flags
- `-g3`: Maximum debug level
  - Includes all compiler debug information
  - Includes macro definitions and expansion
  - Provides full symbol information for debuggers (variables, functions, line numbers)
  - Enables maximum source code correlation

- `-DDEBUG`: Defines DEBUG macro for preprocessor
  - Enables code wrapped in #ifdef DEBUG conditional blocks

- `-fno-omit-frame-pointer`:
  - Maintains stack frame pointers in registers
  - Improves debugger stack traces and profiling accuracy

### Sanitizer Configurations

#### Address Sanitizer (ASan)
Used for detecting:
- Buffer overflows
- Use-after-free errors
- Memory leaks
- Double-free errors

Flags include:
```bash
-fsanitize=address
-fsanitize=undefined
-fno-sanitize-recover=all
-fsanitize=float-divide-by-zero
-fsanitize=float-cast-overflow
-fno-sanitize=null
-fno-sanitize=alignment




Memory Sanitizer (MSan)
Used for detecting:

Uninitialized memory reads

Flag: -fsanitize=memory
Note: Cannot be combined with Address Sanitizer
Build Artifacts
Object Files
The build system creates separate object files for different build types:

Regular build: obj/*.o
Debug build with ASan: obj/*_debug.o
Debug build with MSan: obj/*_debug_msan.o

This separation allows:

Parallel existence of debug and release builds
Prevention of object file collision between build types
Clear distinction between different sanitizer configurations

Header Resolution
Include paths are configured for proper header file resolution:

-I $(INC_DIR): Project's local header directory
-I libft: Custom C library headers






Make Targets
Main Targets

all: Default build
debug: Debug build with Address Sanitizer
debug_msan: Debug build with Memory Sanitizer
clean: Remove object files
fclean: Remove all generated files
re: Complete rebuild

Specialized Clean Targets

clean_debug: Clean debug build objects
clean_debug_msan: Clean MSan debug objects





#	⭐	⭐	⭐	⭐	⭐	⭐	⭐
#		BUILD GUIDE				#
#	⭐	⭐	⭐	⭐	⭐	⭐	⭐

# Available build commands as defined in .PHONY

# make or make all:	Default build
# make debug:			Build with debug flags
# make debug_msan

# make clean:			Remove object files
# make fclean:		Remove objects and executables (full clean)
# make re:			Rebuild from scratch (runs fclean then all)







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






## Runtime Analysis Tools

### Valgrind
For detailed instructions on using Valgrind for runtime analysis,
see [Runtime Analysis & Hardening](HARDENING.md#memory-analysis-with-valgrind)

### Sanitizers
[As documented above in Sanitizer Configurations section...]






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
