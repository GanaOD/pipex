TEST DOCUMENTATION

Test suite: basic functionality to compare my pipex program with bash's piping functionality


🌌 /infiles
🌌 commands.txt





🌌	infiles

Content:
Savitri, Sri Auro Bindo

Infiles with reduced permissions not submitted




🌌	commands.txt

Structure of file:

⭐	Main test categories

🔥	Subcategories

# Test case description

🔥🔥🔥	Specific test

🌿	Bash command syntax
(General: < infile cmd1 | cmd2 > outfile)

🐚	: bash behaviour that must be emulated

⚡	: My pipex program: command, explanation...










Missing test cases:
- in addition to un-used tests in commands.txt
- for v2 of project


Command Syntax & Structure


Commands with multiple spaces/tabs between arguments
Commands with quotes within quotes (nested quotes)
Unbalanced quotes
Commands with escaped characters
Commands with environment variables ($PATH, $HOME, etc.)
Commands with relative paths (./command, ../command)
Commands with absolute paths (/bin/cat, /usr/bin/wc)



Input/Output File Edge Cases


Missing: Files with special characters in names
Missing: Symbolic links
Missing: Hard links
Missing: Named pipes (FIFOs)
Missing: Directories as input (should error gracefully)
Missing: Files that are opened by other processes (locked files)



Permission Cases


Missing: Files owned by different users
Missing: Files with ACLs
Missing: Sticky bit scenarios
Missing: SUID/SGID files
Missing: Output file exists but no write permission (should truncate file)



Error Cases


Missing: Command is a directory
Missing: Command exists but isn't executable
Missing: Command with invalid #! interpreter path
Missing: Too many arguments to commands
Missing: Commands that exit with different status codes
Missing: Commands that write to stderr while also writing to stdout



Resource Edge Cases


Missing: Commands that use all available file descriptors
Missing: Commands that consume excessive memory
Missing: Very long command strings (near system limits)
Missing: Race conditions with file access
