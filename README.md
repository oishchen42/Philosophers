# Philosophers

A multithreaded simulation of the classic **Dining Philosophers Problem** using C and POSIX threads (pthread).

## Table of Contents

- [About the Project](#about-the-project)
- [The Dining Philosophers Problem](#the-dining-philosophers-problem)
- [Installation](#installation)
- [Usage](#usage)
- [Program Arguments](#program-arguments)
- [Examples](#examples)
- [How It Works](#how-it-works)
- [Implementation Details](#implementation-details)

## About the Project

This project implements a solution to the famous Dining Philosophers Problem, a classic synchronization problem in computer science. The program simulates philosophers sitting at a round table, where they must coordinate the use of shared resources (forks) to eat, think, and sleep without causing deadlock or starvation.

## The Dining Philosophers Problem

The Dining Philosophers Problem was originally formulated by Edsger Dijkstra in 1965 as a demonstration of the challenges of resource sharing in concurrent programming.

**The Setup:**
- Several philosophers sit at a round table
- Each philosopher alternates between eating, thinking, and sleeping
- There is a fork between each pair of adjacent philosophers
- A philosopher needs **two forks** (one from each side) to eat
- After eating, the philosopher puts down both forks and sleeps
- After sleeping, the philosopher thinks

**The Challenge:**
- Implement synchronization so that philosophers don't starve
- Avoid deadlock (all philosophers waiting for forks)
- Ensure thread safety when accessing shared resources
- Monitor when a philosopher dies from starvation

## Installation

### Prerequisites
- GCC compiler
- Make
- POSIX-compliant operating system (Linux, macOS, etc.)
- pthread library

### Building the Project

```bash
cd philo
make
```

This will compile the project and create the `philo` executable.

To clean up object files:
```bash
make clean
```

To remove all compiled files including the executable:
```bash
make fclean
```

To recompile everything:
```bash
make re
```

## Usage

```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

All time values are in **milliseconds**.

## Program Arguments

| Argument | Required | Description |
|----------|----------|-------------|
| `number_of_philosophers` | Yes | The number of philosophers (and forks) at the table |
| `time_to_die` | Yes | Time in milliseconds before a philosopher dies if they haven't eaten |
| `time_to_eat` | Yes | Time in milliseconds it takes for a philosopher to eat |
| `time_to_sleep` | Yes | Time in milliseconds a philosopher spends sleeping |
| `number_of_times_each_philosopher_must_eat` | No | If specified, the simulation stops when all philosophers have eaten at least this many times. If not specified, the simulation runs until a philosopher dies |

**Important Notes:**
- All arguments must be positive integers
- Philosophers are numbered from 1 to N
- Time values must be at least 60ms for the simulation to work properly

## Examples

### Example 1: Basic simulation with 4 philosophers
```bash
./philo 4 410 200 200
```
- 4 philosophers at the table
- Each philosopher dies if they don't eat within 410ms
- Eating takes 200ms
- Sleeping takes 200ms
- Simulation runs until a philosopher dies

### Example 2: Simulation with eating limit
```bash
./philo 5 800 200 200 7
```
- 5 philosophers at the table
- Each philosopher dies if they don't eat within 800ms
- Eating takes 200ms
- Sleeping takes 200ms
- Simulation stops when each philosopher has eaten 7 times

### Example 3: No one should die
```bash
./philo 4 410 200 200
```
With proper time parameters, no philosopher should die.

### Example 4: A philosopher should die
```bash
./philo 4 310 200 100
```
With tight time constraints, a philosopher will eventually die.

## How It Works

### Simulation Output

The program outputs the state of each philosopher with timestamps:

```
0 1 is thinking
0 1 has taken a fork
0 1 has taken a fork
0 1 is eating
200 1 is sleeping
400 1 is thinking
```

Output format: `timestamp_in_ms philosopher_id state`

**Possible states:**
- `is thinking` - Philosopher is thinking
- `has taken a fork` - Philosopher has picked up a fork
- `is eating` - Philosopher is eating (requires 2 forks)
- `is sleeping` - Philosopher is sleeping
- `died` - Philosopher has died from starvation

### Death Condition

A philosopher dies if:
- The time since their last meal exceeds `time_to_die` milliseconds
- When a death occurs, a death message is printed and the simulation stops

## Implementation Details

### Thread Management
- Each philosopher runs in its own thread
- A separate monitoring thread checks for philosopher deaths
- Mutexes are used to protect shared resources (forks) and prevent data races

### Synchronization
The program uses several mutex locks to ensure thread safety:
- **Fork mutexes**: One mutex per fork to control access
- **Message mutex**: Prevents overlapping output messages
- **Last meal mutex**: Protects the last meal timestamp
- **Program finish mutex**: Coordinates program termination

### Deadlock Prevention
The implementation includes strategies to avoid deadlock:
- Alternating philosopher wait states to prevent circular waiting
- Special handling for odd/even numbered philosophers
- Careful fork acquisition order

### Key Features
- Precise timestamp tracking using `gettimeofday()`
- Custom sleep function for accurate timing
- Thread-safe message printing
- Proper cleanup of threads and mutexes
- Error handling for invalid inputs and system call failures

## Project Structure

```
philo/
├── Makefile              # Build configuration
├── philo.h               # Header file with structures and function declarations
├── main.c                # Entry point
├── init_data.c           # Data structure initialization
├── init_data_utils.c     # Helper functions for initialization
├── start_threads.c       # Thread creation and management
├── routines.c            # Philosopher routine implementations
├── routine_utils.c       # Helper functions for routines
├── time_utils.c          # Time-related utilities
├── is_finished_utils.c   # Program completion checks
├── error_handler.c       # Error handling utilities
├── cleanups.c            # Memory and resource cleanup
└── libft_utils.c         # String and utility functions
```

## Author

Created by oishchen (@oishchen42)
