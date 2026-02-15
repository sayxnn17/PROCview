# my_ps - Process Information Merger

## Overview
This C program merges the output of two Linux process listing commands:
- `ps aux` - Provides CPU%, MEM%, VSZ, RSS, TTY, STAT, and other information
- `ps -eLf` - Provides UID, PPID, LWP (thread ID), C, NLWP (thread count), and other information

The program merges both outputs using PID as the common key and creates a unified view.

## Compilation

### Standard Compilation
```bash
gcc -o my_ps my_ps.c
```

### With Warnings (Recommended)
```bash
gcc -Wall -Wextra -o my_ps my_ps.c
```

### With Optimization
```bash
gcc -O2 -o my_ps my_ps.c
```

## Usage

### Basic Execution
```bash
./my_ps
```

### Check if Executable Exists
```bash
ls -lh my_ps
```

### View Only the Output File
```bash
cat merged.txt
```

### View with Pagination
```bash
less merged.txt
```

## Output Format

The merged output includes the following columns:

```
UID      - User ID of the process owner
PID      - Process ID
PPID     - Parent Process ID
LWP      - Light Weight Process (thread ID)
C        - Processor utilization for scheduling
NLWP     - Number of threads in the process
%CPU     - CPU usage percentage
%MEM     - Memory usage percentage
VSZ      - Virtual memory size (in KB)
RSS      - Resident set size (physical memory in KB)
TTY      - Controlling terminal
STAT     - Process state (R, S, D, Z, T, etc.)
START    - Start time of the process
TIME     - Cumulative CPU time
COMMAND  - Command line that started the process
```

## Files Generated

1. **x1.txt** - Output from `ps aux`
2. **x2.txt** - Output from `ps -eLf`
3. **merged.txt** - Final merged output (main result)

## Example Execution

```bash
$ gcc -o my_ps my_ps.c
$ ./my_ps

=== my_ps: Process Information Merger ===

Executing ps aux and ps -eLf...
Commands executed successfully

Parsed 342 processes from ps aux
Merged data for 342 processes from ps -eLf

Merged output written to merged.txt

========================================
       MERGED PROCESS INFORMATION       
========================================

UID        PID     PPID    LWP     C   NLWP  %CPU   %MEM   VSZ        RSS        TTY        STAT  START      TIME       COMMAND
root       1       0       1       0   1     0.0    0.1    168644     11632      ?          Ss    Feb14      0:02       /sbin/init
root       2       0       2       0   1     0.0    0.0    0          0          ?          S     Feb14      0:00       [kthreadd]
...
```

## How It Works

1. **Execute Commands**: Uses `system()` to run `ps aux` and `ps -eLf`, redirecting output to temporary files
2. **Parse ps aux**: Reads x1.txt and extracts process information into an array
3. **Merge ps -eLf**: Reads x2.txt and merges additional fields by matching PIDs
4. **Write Output**: Writes the merged data to merged.txt with formatted columns
5. **Display**: Shows the merged output on the terminal

## Key Features

- ✅ Uses standard C library functions (fopen, fclose, fscanf, fprintf, system)
- ✅ Dynamic memory allocation for process array
- ✅ Proper error handling for file operations
- ✅ No memory leaks (proper cleanup with free())
- ✅ Modular design with separate functions for each task
- ✅ Handles up to 10,000 processes
- ✅ Null-termination for string safety
- ✅ Comprehensive comments explaining each step

## Requirements Met

✓ Uses system() to execute ps commands
✓ Opens and reads x1.txt and x2.txt
✓ Parses using sscanf (compatible with fscanf)
✓ Merges data using PID as the key
✓ Writes to merged.txt using fprintf
✓ Displays output on terminal
✓ Uses struct to store process information
✓ Clean, modular, well-commented code
✓ GCC compatible standard C

## Troubleshooting

### Permission Denied
```bash
chmod +x my_ps
```

### Compilation Errors
Make sure you have GCC installed:
```bash
gcc --version
```

### Empty Output
Ensure you have proper permissions to run ps commands on your system.

## Cleanup

To remove temporary files:
```bash
rm x1.txt x2.txt merged.txt
```

To remove the executable:
```bash
rm my_ps
```

## Technical Details

- **Language**: C (C99 standard)
- **Compiler**: GCC compatible
- **Platform**: Linux/Unix systems
- **Memory**: Dynamically allocated (MAX_PROCESSES = 10,000)
- **Line Buffer**: 2048 bytes per line

## Author Notes

This program demonstrates:
- System call integration with C
- File I/O operations
- Dynamic memory management
- Data structure design
- String manipulation in C
- Process information parsing
- Multi-source data merging
