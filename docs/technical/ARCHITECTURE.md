# Pipex Architecture Specification
Version 1.0.0


## 1. System Overview
Pipex implements Unix pipe functionality, replicating the behavior of:
`< file1 cmd1 | cmd2 > file2`

### 1.1 Trust Boundaries
- User input (command arguments, file paths)
- System environment (PATH, file permissions)
- Child process isolation

### 1.2 Data Flow
```ascii
+----------+     +----------+     +----------+     +----------+
|  infile  | --> |  cmd1    | --> |  pipe    | --> |  cmd2    | --> | outfile |
+----------+     +----------+     +----------+     +----------+






2. Core Components


2.1 Process Management

Parent process: orchestrates execution flow
Child processes: isolated command execution
IPC mechanism: unidirectional pipe



2.2 Memory Model

Heap allocations: command parsing, path resolution
File descriptors: managed with RAII-style cleanup
Process address space isolation



2.3 Security Controls

Command injection mitigation through proper parsing
File descriptor isolation
Resource cleanup guarantees




3. Critical Paths

3.1 Command Processing
[Critical code snippet from your parse_commands function]


3.2 Process Creation
[Critical code snippet from your fork handling]




4. Error Handling Model

Hierarchical cleanup
Resource tracking
Error propagation paths




5. Known Limitations

Single pipe limitation
No support for complex shell features
Limited quoting support








## Command Processing Architecture

### Command Structure
- Raw command storage
- Argument parsing and storage
- Path resolution
- Error handling strategy

### Design Decisions
1. Two-phase parsing:
   - Initial command structure initialization
   - Full command parsing with validation

2. Robust Path Resolution:
   - Handle missing PATH variable
   - Preserve original command for error reporting
   - Allow for command-not-found scenarios

3. Error Handling Strategy:
   - Continue execution even if one command fails
   - Match shell behavior for command failures
   - Preserve error states for parent process



4. Error Handling Model
4.1 Command Execution Errors
The system implements a hierarchical error handling strategy:

Error Classification

File existence (ENOENT)
Permission issues (EACCES)
Resource constraints (ENOMEM)
Directory execution attempts (EISDIR)
Generic system errors


Error Response Patterns

First command: Return and continue pipeline
Second command: Exit with appropriate code
Parent process: Status code preservation


Error Reporting

Shell-compatible error messages
Appropriate output streams (stderr)
Context-aware error details
Command name inclusion in messages



4.2 Pipeline Error Architecture
Error handling differs between pipeline stages:

First Stage (cmd1)

Non-fatal error handling
Status code return
Pipeline continuation
Error state preservation


Second Stage (cmd2)

Fatal error handling
Immediate process termination
Direct error reporting
Clean process shutdown


Error Propagation

Up to parent process
Through exit codes
Via error messages
With context preservation
