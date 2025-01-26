Security hardening guidelines




# Runtime Analysis & Hardening




## Memory Analysis with Valgrind

valgrind flags and additional useful combinations:


test these with different scenarios:
Valid commands
Invalid/nonexistent commands (like your test case)
Invalid input files
Permission denied cases
Empty files


**Basic Memory Checking Flags**:

```bash
--leak-check=full       # Detailed info about memory leaks
--show-leak-kinds=all   # Show all types (definite, indirect, possible, reachable)
--track-origins=yes     # Show where uninitialized values came from
--verbose              # Extra information about leaks, suppressions
-s                     # Same as --verbose

```

**Memcheck Tool** (default tool):

```bash
--tool=memcheck        # Explicitly select memory checker
```

Additional useful memcheck flags:

```bash
--track-fds=yes       # Track open file descriptors
--trace-children=yes  # Also check child processes
--num-callers=N      # Show N levels of function call stack (default 12)
--error-limit=no     # Don't limit number of errors reported
```

**Cachegrind** (Cache and branch prediction profiler):

```bash

--tool=cachegrind

```

Useful cachegrind flags:

```bash
--cache-sim=yes      # Simulate cache behavior
--branch-sim=yes     # Simulate branch predictor
--cachegrind-out-file=<file>  # Specify output file

```

**Massif** (Heap profiler):

```bash
--tool=massif        # Heap memory profiler

```

Useful massif flags:

```bash
--heap=yes          # Profile heap memory
--stacks=yes       # Include stack memory in profile
--detailed-freq=10 # Detailed snapshot frequency
--max-snapshots=100 # Maximum number of snapshots

```

**Other Useful Tools**:

Callgrind (Call-graph generator):

```bash
--tool=callgrind    # Profile function calls
--separate-threads=yes  # Separate thread data

```

Helgrind (Thread error detector):

```bash
--tool=helgrind     # Thread error detector
--history-level=full # Maximum history for race detection

```

DRD (Another thread error detector):

```bash
--tool=drd         # Alternative thread checker
--segment-merging=no # Don't merge segments

```

### Common Combinations for Different Purposes:

**Thorough Memory Check**:

```bash

valgrind --tool=memcheck \
         --leak-check=full \
         --show-leak-kinds=all \
         --track-origins=yes \
         --verbose \
         --error-limit=no \
         --track-fds=yes

```

**Performance Analysis**:

```bash

valgrind --tool=cachegrind \
         --branch-sim=yes \
         --cache-sim=yes

```

**Memory Usage Over Time**:

```bash

valgrind --tool=massif \
         --heap=yes \
         --stacks=yes \
         --detailed-freq=10 \
         --time-unit=B

```

**Thread Safety Check**:

```bash

valgrind --tool=helgrind \
         --history-level=full \
         --conflict-cache-size=10000000

```
