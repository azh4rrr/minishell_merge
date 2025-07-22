# 🐚 Minishell - Unix Shell Implementation

<div align="center">

![Minishell Banner](https://via.placeholder.com/800x200/0D1117/00D4AA?text=MINISHELL+-+UNIX+SHELL+RECREATION)

[![Made with C](https://img.shields.io/badge/Made%20with-C-blue?style=for-the-badge&logo=c)](https://en.wikipedia.org/wiki/C_(programming_language))
[![42 School](https://img.shields.io/badge/42-School-000000?style=for-the-badge&logo=42)](https://42.fr/)
[![Shell](https://img.shields.io/badge/Shell-Implementation-success?style=for-the-badge)](https://github.com/__azh4rrr__/minishell)
[![Partner](https://img.shields.io/badge/Partner-mouchtach-orange?style=for-the-badge&logo=github)](https://github.com/mouchtach)

*A fully functional Unix shell with advanced parsing and execution capabilities*

[Features](#-features) • [Installation](#-installation) • [Usage](#-usage) • [Built-ins](#-built-in-commands) • [Architecture](#-architecture)

</div>

---

## 🎯 About

**Minishell** is a comprehensive Unix shell implementation project from 42 School that recreates the core functionality of bash. This project demonstrates deep understanding of system programming, process management, signal handling, and command-line parsing in a Unix environment.

Built as a collaborative effort, this shell handles complex command parsing, pipe chains, redirections, environment variable expansion, and provides a complete interactive command-line experience.

## ✨ Features

- 🖥️ **Interactive Shell** - Full command-line interface with prompt and history
- 🔗 **Pipe Chains** - Support for complex command piping (`cmd1 | cmd2 | cmd3`)
- 📁 **I/O Redirections** - Input, output, and append redirections (`<`, `>`, `>>`)
- 🌍 **Environment Variables** - Complete variable expansion and management (`$VAR`)
- 🔤 **Quote Handling** - Proper parsing of single and double quotes
- ⚡ **Signal Management** - Graceful handling of Ctrl+C, Ctrl+D, and Ctrl+\
- 🏗️ **Built-in Commands** - Essential shell built-ins implementation
- 🧠 **Advanced Parsing** - Robust tokenization and command parsing
- 🛡️ **Error Handling** - Comprehensive error management and reporting
- 🎯 **42 Compliant** - Meets all project requirements and norms

## 🚀 Installation

### Prerequisites
- **OS**: Unix-like system (Linux, macOS, WSL)
- **Compiler**: GCC or Clang with C99 support
- **Libraries**: GNU Readline library
- **Make**: GNU Make

### Quick Start

```bash
# Clone the repository
git clone https://github.com/__azh4rrr__/minishell.git
cd minishell

# Install dependencies (Ubuntu/Debian)
sudo apt-get install libreadline-dev

# Install dependencies (macOS with Homebrew)
brew install readline

# Compile the project
make

# Clean object files
make clean

# Remove all generated files
make fclean

# Recompile everything
make re
```

## 💡 Usage

### Basic Usage

```bash
# Start the shell
./minishell

# Basic commands
minishell$ ls -la
minishell$ pwd
minishell$ echo "Hello, World!"

# Exit the shell
minishell$ exit
```

### Advanced Examples

```bash
# Pipe chains
minishell$ ls -la | grep ".c" | wc -l
minishell$ cat file.txt | sort | uniq -c | sort -nr

# Redirections
minishell$ echo "Hello" > output.txt
minishell$ sort < input.txt > sorted.txt
minishell$ ls -la >> log.txt

# Environment variables
minishell$ export MY_VAR="Hello World"
minishell$ echo "Message: $MY_VAR"
minishell$ echo "Path: $PATH"

# Quote handling
minishell$ echo 'Single quotes: $USER'
minishell$ echo "Double quotes: $USER"
minishell$ echo "Mixed 'quotes' and $HOME"
```

## 🛠️ Built-in Commands

### Complete Built-in Implementation

| Command | Description | Usage | Exit Status |
|---------|-------------|-------|-------------|
| `echo` | Display text with optional newline suppression | `echo [-n] [text...]` | 0 |
| `cd` | Change current directory | `cd [directory]` | 0/1 |
| `pwd` | Print current working directory | `pwd` | 0 |
| `export` | Set or display environment variables | `export [VAR[=value]]` | 0 |
| `unset` | Remove environment variables | `unset [VAR...]` | 0 |
| `env` | Display environment variables | `env` | 0 |
| `exit` | Exit shell with optional status | `exit [status]` | varies |

### Built-in Examples

```bash
# Echo with options
minishell$ echo -n "No newline"
minishell$ echo "Normal echo"

# Directory navigation
minishell$ cd /home/user
minishell$ cd ..
minishell$ cd    # Go to HOME
minishell$ pwd

# Environment management
minishell$ export DEBUG=1
minishell$ export PATH="$PATH:/custom/bin"
minishell$ unset DEBUG
minishell$ env | grep PATH

# Exit with status
minishell$ exit 42
```

## 🏗️ Architecture

### Project Structure

```
minishell/
├── minishell.c               # Main entry point
├── minishell.h               # Main header file
├── Makefile                  # Build configuration
├── execution/
│   ├── builtin/
│   │   ├── built_in.c        # Built-in dispatcher
│   │   ├── cd.c              # Change directory
│   │   ├── echo.c            # Echo command
│   │   ├── exit.c            # Exit command
│   │   ├── export.c          # Export variables
│   │   ├── export_utils.c    # Export utilities
│   │   └── unset.c           # Unset variables
│   ├── environment.c         # Environment management
│   ├── environment_utils.c   # Environment utilities
│   ├── error.c               # Error handling
│   ├── execution.c           # Main execution engine
│   ├── exit_status.c         # Exit status management
│   ├── fork.c                # Process forking
│   ├── get_next_line.c       # Line reading utility
│   ├── get_path.c            # PATH resolution
│   ├── heredoc.c             # Here document handling
│   ├── leaks_fd.c            # File descriptor leak management
│   ├── leaks_mem.c           # Memory leak management
│   ├── list_utils.c          # Linked list utilities
│   ├── redirections.c        # I/O redirections
│   ├── signals.c             # Signal handling
│   └── utils_std.c           # Standard utilities
├── parsing/
│   ├── expansion/
│   │   ├── expansion.c       # Variable expansion
│   │   ├── expansion_utils.c # Expansion utilities
│   │   ├── expansion_utils_b.c
│   │   ├── expansion_utils_c.c
│   │   └── pre_expand.c      # Pre-expansion processing
│   ├── redirecting/
│   │   ├── parse_redir.c     # Redirection parsing
│   │   ├── parse_redir_utils.c
│   │   ├── parse_redir_utils_b.c
│   │   └── redirection.c     # Redirection handling
│   ├── utils/
│   │   ├── utils_a.c         # Parsing utilities A
│   │   ├── utils_b.c         # Parsing utilities B
│   │   └── utils_c.c         # Parsing utilities C
│   ├── cleanup.c             # Memory cleanup
│   ├── init_structs.c        # Structure initialization
│   ├── parsing.c             # Main parsing logic
│   ├── special_split.c       # Advanced string splitting
│   └── syntax_handle.c       # Syntax validation
├── H_EXP/
│   ├── h_exp.c               # Heredoc expansion
│   └── h_exp_utils.c         # Heredoc utilities
└── libft/
    ├── libft.h               # Library header
    ├── Makefile              # Library build file
    └── [42 library functions] # Custom C library
```

### Core Components

```
┌─────────────────────────────────────────┐
│            MINISHELL PIPELINE          │
├─────────────────────────────────────────┤
│ 1. INPUT → Main loop (minishell.c)     │
│ 2. PARSING → Tokenization & validation │
│    ├── Special split & syntax check    │
│    ├── Variable expansion (H_EXP)      │
│    └── Redirection parsing             │
│ 3. EXECUTION → Process management      │
│    ├── Built-in commands               │
│    ├── External command execution      │
│    ├── Signal handling                 │
│    └── I/O redirections                │
│ 4. CLEANUP → Memory & FD management    │
└─────────────────────────────────────────┘
```

## 🔧 Features in Detail

### Command Parsing Pipeline

1. **Lexical Analysis** - Tokenizes input into meaningful units
2. **Syntax Analysis** - Validates command syntax and structure
3. **Expansion** - Handles variable expansion and quote removal
4. **Execution Planning** - Builds execution tree for complex commands

### Pipe Implementation

```bash
# Simple pipe
minishell$ ls | wc -l

# Complex pipe chain
minishell$ cat file.txt | grep "pattern" | sort | uniq | wc -l

# Pipes with redirections
minishell$ ls -la | grep "\.c$" > c_files.txt
```

### Redirection Handling

```bash
# Input redirection
minishell$ sort < unsorted.txt

# Output redirection (overwrite)
minishell$ echo "Hello" > output.txt

# Output redirection (append)
minishell$ echo "World" >> output.txt

# Multiple redirections
minishell$ cat < input.txt > output.txt
```

### Environment Variables

```bash
# Setting variables
minishell$ export NAME="John Doe"
minishell$ export PATH="$PATH:/new/path"

# Using variables
minishell$ echo "Hello, $NAME"
minishell$ echo "Current user: $USER"
minishell$ ls $HOME

# Special variables
minishell$ echo "Exit status: $?"
minishell$ echo "Process ID: $$"
```

### Quote Handling

```bash
# Single quotes (literal)
minishell$ echo 'Value of $HOME: $HOME'

# Double quotes (with expansion)
minishell$ echo "Value of $HOME: $HOME"

# Mixed quotes
minishell$ echo "User's home: '$HOME'"
```

## 🧪 Testing

### Manual Testing

```bash
# Basic functionality
./minishell
minishell$ echo "Test successful"
minishell$ pwd
minishell$ ls | head -5

# Error handling
minishell$ /nonexistent/command
minishell$ export 123INVALID=value
minishell$ cd /nonexistent/directory

# Signal handling
# Press Ctrl+C, Ctrl+D, Ctrl+\ and observe behavior
```

### Automated Testing

```bash
# Create test script
cat > test_minishell.sh << 'EOF'
#!/bin/bash
echo "=== Testing Basic Commands ==="
echo "pwd" | ./minishell
echo "echo 'Hello World'" | ./minishell

echo "=== Testing Pipes ==="
echo "ls | wc -l" | ./minishell

echo "=== Testing Redirections ==="
echo "echo 'test' > /tmp/minishell_test" | ./minishell
echo "cat < /tmp/minishell_test" | ./minishell
rm -f /tmp/minishell_test

echo "=== Testing Environment ==="
echo "export TEST_VAR=hello && echo \$TEST_VAR" | ./minishell
EOF

chmod +x test_minishell.sh
./test_minishell.sh
```

### Comparison with Bash

```bash
# Test identical behavior
command="echo 'Hello' | wc -c"

echo "Bash output:"
echo "$command" | bash

echo "Minishell output:"
echo "$command" | ./minishell
```

## 📊 Performance & Compliance

### 42 School Requirements

#### Mandatory Part
- ✅ Display prompt and wait for commands
- ✅ Execute external commands via PATH or relative/absolute paths
- ✅ Implement all required built-in commands
- ✅ Handle pipes (`|`) correctly
- ✅ Handle redirections (`<`, `>`, `>>`) correctly
- ✅ Handle environment variables (`$VAR`) correctly
- ✅ Handle single and double quotes correctly
- ✅ Implement signal handling (Ctrl+C, Ctrl+D, Ctrl+\)
- ✅ No memory leaks or crashes

#### Error Handling
- ✅ Command not found
- ✅ Permission denied
- ✅ Syntax errors
- ✅ File/directory not found
- ✅ Invalid redirections
- ✅ Broken pipes

### Memory Management

```c
// Example of proper resource management
typedef struct s_shell {
    char **env;
    char *line;
    t_token *tokens;
    t_cmd *commands;
} t_shell;

// Cleanup function called on exit
void cleanup_shell(t_shell *shell);
```

## 🎓 Learning Outcomes

This project demonstrates mastery of:

- **System Programming** - Process creation, management, and communication
- **Unix APIs** - File descriptors, pipes, signals, environment
- **Memory Management** - Dynamic allocation, leak prevention, cleanup
- **Parsing Techniques** - Lexical analysis, syntax parsing, AST building
- **Error Handling** - Robust error detection and recovery
- **Shell Internals** - Understanding how shells work internally
- **Collaboration** - Working effectively in pairs on complex projects

## 👥 Team

<div align="center">

### Project Partners

| Developer | GitHub | Contributions |
|-----------|---------|---------------|
| **__azh4rrr__** | [@__azh4rrr__](https://github.com/__azh4rrr__) | Parsing, Memory Management, Testing |
| **mouchtach** | [@mouchtach](https://github.com/mouchtach) | Signals, Execution, Built-ins |

*Built through collaborative pair programming and code reviews*

</div>

## 🏆 42 School Evaluation

### Evaluation Criteria
- **Functionality** - All required features work correctly
- **Error Management** - Proper handling of all error cases  
- **Code Quality** - Clean, readable, and well-structured code
- **Memory Management** - No leaks, proper cleanup
- **Compliance** - Follows 42 coding standards (Norminette)

### Expected Grade Distribution
- **Mandatory Part**: 80/100 (All requirements met)
- **Code Quality**: +10 (Clean implementation)
- **Error Handling**: +5 (Comprehensive error management)
- **Bonus Features**: +5 (Additional shell features)

## 🔧 Build System

```makefile
# Compilation flags
CFLAGS = -Wall -Wextra -Werror -std=c99
LIBS = -lreadline

# Build targets
all: minishell
clean: # Remove object files
fclean: # Remove all generated files
re: # Rebuild everything
```

## 🐛 Known Limitations

- No job control (background processes with `&`)
- Limited wildcard expansion (globbing)
- No command substitution (`$(command)` or `` `command` ``)
- No arithmetic expansion (`$((expression))`)
- No brace expansion (`{a,b,c}`)
- No alias support
- Limited here-document support (`<<`)

---

<div align="center">

**🐚 Unix shell mastery through collaborative development! 🐚**

*"The shell is the gateway to the system - make it robust, make it reliable."*

Made with 🧠 and systematic thinking by **[__azh4rrr__](https://github.com/__azh4rrr__)** & **[mouchtach](https://github.com/mouchtach)**

</div>