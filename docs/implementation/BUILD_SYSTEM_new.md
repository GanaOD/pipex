Integrate this with BUILD_SYSTEM.md

# Build System Documentation

This document describes the build system for the pipex project, including various debugging and analysis configurations.

## Basic Usage

### Standard Build
```bash
make
```
Builds the project with standard optimization and all warnings enabled (-Wall -Wextra -Werror).

### Clean Build
```bash
make re
```
Completely rebuilds the project by removing all generated files and rebuilding from scratch.

## Debugging Configurations

The build system supports various debugging configurations through a flexible debug target:
```bash
make debug DEBUG_FLAGS="[flags]"
```

### Available Debug Configurations

#### Basic Debug (for Valgrind)
```bash
make debug DEBUG_FLAGS="-g"
```
- Adds debug symbols
- Minimal overhead
- Ideal for use with Valgrind

#### Address Sanitizer (ASan)
```bash
make debug DEBUG_FLAGS="-fsanitize=address -g3 -DDEBUG -fno-omit-frame-pointer \
    -fsanitize=undefined \
    -fno-sanitize-recover=all \
    -fsanitize=float-divide-by-zero \
    -fsanitize=float-cast-overflow \
    -fno-sanitize=null \
    -fno-sanitize=alignment"
```
Detects:
- Use-after-free
- Heap buffer overflow
- Stack buffer overflow
- Global buffer overflow
- Use-after-return
- Use-after-scope
- Initialization order bugs
- Memory leaks

#### Memory Sanitizer (MSan)
```bash
make debug DEBUG_FLAGS="-fsanitize=memory -g3 -DDEBUG -fno-omit-frame-pointer"
```
Detects:
- Uninitialized memory reads
- Memory leaks
- Use of uninitialized values

Note: MSan and ASan cannot be used simultaneously.

## Analysis Tools

### Running with Valgrind

Basic memory check:
```bash
valgrind ./pipex_debug [args]
```

Detailed memory analysis:
```bash
valgrind --leak-check=full \
         --show-leak-kinds=all \
         --track-origins=yes \
         --verbose \
         ./pipex_debug [args]
```

Cache and branch prediction analysis:
```bash
valgrind --tool=cachegrind \
         --branch-sim=yes \
         --cache-sim=yes \
         ./pipex_debug [args]
```

## Common Debug Flags Explained

| Flag | Purpose |
|------|---------|
| `-g` | Basic debug symbols for GDB/LLDB |
| `-g3` | Maximum debug information |
| `-DDEBUG` | Enables DEBUG macro for conditional compilation |
| `-fno-omit-frame-pointer` | Keeps frame pointer for better backtraces |
| `-fsanitize=address` | Enables Address Sanitizer |
| `-fsanitize=memory` | Enables Memory Sanitizer |
| `-fsanitize=undefined` | Catches undefined behavior |
| `-fno-sanitize-recover=all` | Halts on first error |
| `-fsanitize=float-divide-by-zero` | Catches floating-point division by zero |
| `-fsanitize=float-cast-overflow` | Catches floating-point cast overflows |

## Notes

1. Debug builds will be slower and use more memory than release builds
2. Sanitizers can significantly impact performance
3. Different analysis tools may be incompatible with each other
4. Always use the appropriate debug configuration for your specific debugging needs

## Examples

### Finding Memory Leaks
```bash
# Build with ASan
make debug DEBUG_FLAGS="-fsanitize=address -g3"
# Run
./pipex_debug infile "cmd1" "cmd2" outfile
```

### Analyzing Cache Performance
```bash
# Build with basic debug info
make debug DEBUG_FLAGS="-g"
# Run with Cachegrind
valgrind --tool=cachegrind --branch-sim=yes ./pipex_debug infile "cmd1" "cmd2" outfile
```





# **************************************************************************** #
#                               HELPER TARGETS                                  #
# **************************************************************************** #

# Common debug configurations (for reference)
help:
	@echo "Available targets:"
	@echo "  make all          : Build program"
	@echo "  make clean        : Remove object files"
	@echo "  make fclean       : Remove all generated files"
	@echo "  make re          : Rebuild program"
	@echo "  make debug       : Build debug version with specified flags"
	@echo ""
	@echo "Debug examples:"
	@echo "  make debug DEBUG_FLAGS=\"-g\"                     : For valgrind"
	@echo "  make debug DEBUG_FLAGS=\"-fsanitize=address -g3\" : For ASan"
	@echo "  make debug DEBUG_FLAGS=\"-fsanitize=memory -g3\"  : For MSan"
