Overview
The pipex program implements shell-style pipe behavior, connecting two commands via a pipe and handling file redirections. The program flow is split into distinct phases:


1. Initialization

Validate input arguments
Initialize data structures
Set up initial state


2. Command Processing

Parse command strings
Validate commands
Resolve command paths


3. Pipeline Execution

Create pipe
Fork processes
Set up redirections
Execute commands


4. Cleanup & Exit

Wait for child processes
Clean up resources
Return appropriate exit status






3. Pipeline Execution
3.1 First Child Process (cmd1)
The first child process handles the input file and initial command execution:

File Setup

Opens input file in read-only mode
Handles file access errors with appropriate messaging
Continues execution even if file open fails (matching shell behavior)


Stream Redirection

Redirects standard input from input file (if successfully opened)
Redirects standard output to pipe write end
Closes unused pipe read end
Validates all redirections


Command Execution

Executes first command with error handling
Reports command failures appropriately
Exits with shell-compatible status codes



3.2 Second Child Process (cmd2)
The second child process handles output file and final command execution:

File Setup

Creates/opens output file with truncation
Sets appropriate permissions (0644)
Exits on file access errors


Stream Redirection

Redirects standard input from pipe read end
Redirects standard output to output file
Closes unused pipe write end
Validates all redirections


Command Execution

Executes second command
Handles execution errors
Exits with appropriate status codes



3.3 Error Handling
Both child processes implement consistent error handling:

File Operations

Permission denied errors
No such file errors
Other system errors


Command Execution

Command not found (127)
Permission denied (126)
Memory allocation failures
Other execution errors



3.4 Resource Management
Each child process follows strict resource cleanup:

File Descriptors

Closes unused pipe ends
Closes input/output files after redirection
Handles cleanup failures


Process Termination

Exits with appropriate status codes
Ensures all resources are released
Propagates error states to parent



3.5 Command Execution Flow
The execution phase implements different strategies for each command:

First Command (cmd1)

Continues execution on failure
Returns error codes to parent
Maintains pipeline functionality even if command fails
Matches shell behavior for error propagation


Second Command (cmd2)

Exits on failure
Terminal command in pipeline
Direct error reporting
No return flow as it's the end of pipeline



3.6 Exit Code Handling
Exit codes are carefully managed to match shell behavior:

Command not found: 127
Permission denied: 126
Memory allocation failures: 1
Other execution errors: 1
