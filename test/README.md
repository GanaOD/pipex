# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    README                                       		:+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: go-donne <go-donne@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created by go-donne                               #+#    #+#              #
#    Updated by go-donne         					  ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


TEST DOCUMENTATION

Test suite: basic functionality to compare my pipex program with bash's piping functionality




🌌	infiles

Content:
Savitri, Sri Auro Bindo






🌌	commands.txt


⭐	Main test categories:
Core Functionality: Validates basic requirements
Edge Cases: Tests boundary conditions
Resource Handling: Verifies handling of varying data loads
Permission & Access Control: Tests security boundaries
Error Handling: Validates graceful failure
Memory Management: Ensures resource cleanup
Special files: testing system device interfaces


🔥	Subcategories


# Test case description


🌿	Bash command syntax
(General: < infile cmd1 | cmd2 > outfile)

<	: input redirection operator. Tells bash to use the content of infile as stdin for the following command (like my dup2 in pipex that redirects stdin)


🐚	: bash behaviour that must be emulated


⚡	: My pipex program









Missing test cases:
(for next iteration through project (v2))


Command Syntax & Structure


Missing: Commands with multiple spaces/tabs between arguments
Missing: Commands with quotes within quotes (nested quotes)
Unbalanced quotes
Missing: Commands with escaped characters
Missing: Commands with environment variables ($PATH, $HOME, etc.)
Missing: Commands with relative paths (./command, ../command)
Missing: Commands with absolute paths (/bin/cat, /usr/bin/wc)



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
