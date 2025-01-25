Security hardening guidelines




# Runtime Analysis & Hardening

## Memory Analysis with Valgrind

### Basic Usage
```bash
valgrind --leak-check=full \
         --show-leak-kinds=all \
         --track-origins=yes \
         --verbose \
         ./pipex infile cmd1 cmd2 outfile


Common Analysis Modes
Memory Error Detection
valgrind --tool=memcheck \
         --leak-check=full \
         --show-leak-kinds=all \
         ./pipex infile cmd1 cmd2 outfile
Cache and Branch Prediction
bashCopyvalgrind --tool=cachegrind ./pipex infile cmd1 cmd2 outfile
Heap Profiling
bashCopyvalgrind --tool=massif ./pipex infile cmd1 cmd2 outfile
Combining with Sanitizers
⚠️ Note: Do not run Valgrind on binaries compiled with AddressSanitizer (ASan)
or MemorySanitizer (MSan). Use either Valgrind OR sanitizers, not both simultaneously.
Recommended Workflow

Regular development: Use sanitizer-enabled debug builds
Pre-release testing: Run Valgrind analysis on non-sanitizer builds
Production: Use hardened release builds
