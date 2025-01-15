# IPC: Shared Memory vs Pipe

This repository contains two C programs that implement inter-process communication (IPC) mechanisms—**shared memory** and **pipes**—and measure the time required for data transmission using each method.

## Overview

Inter-process communication is essential for enabling processes to exchange data and coordinate actions. Among various IPC methods, **pipes** and **shared memory** are commonly used:

- **Pipes**: Allow unidirectional data flow between processes. Data written to the pipe by one process can be read by another, facilitating a stream-oriented communication channel.

- **Shared Memory**: Enables multiple processes to access a common memory segment, allowing for high-speed data exchange without the need for data copying between processes.

This project evaluates the performance of these two IPC methods by measuring the time taken for data transmission in each case.

## Repository Contents

- `time_pipe.c`: C program that implements IPC using pipes and measures the transmission time.  
- `time_shm.c`: C program that implements IPC using shared memory and measures the transmission time.  
- `time_pipe_output.txt`: Output file containing the timing results for the pipe implementation.  
- `time_shm_output.txt`: Output file containing the timing results for the shared memory implementation.  

## Getting Started

### Prerequisites

- GCC compiler  
- POSIX-compliant operating system (e.g., Linux)  

### Compilation

To compile the programs, use the following commands:

```bash
gcc -o time_pipe time_pipe.c
gcc -o time_shm time_shm.c
```

### Execution

After compilation, run the executables to measure IPC performance:
```
./time_pipe
./time_shm
```

The programs will output the time taken for data transmission using pipes and shared memory, respectively.

## License

This project is licensed under the MIT License—see the LICENSE file for details.

## Acknowledgments

This project was developed by Brandon Lavello as an exploration of IPC mechanisms and their performance characteristics.
