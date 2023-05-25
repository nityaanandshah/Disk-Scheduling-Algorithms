# Disk Scheduling Algorithms

## Description

This program implements the following disk scheduling algorithms:
- FCFS (First Come First Serve)
- SSTF (Shortest Seek Time First)
- SCAN (Elevator Algorithm)
- C-SCAN (Circular SCAN Algorithm)

## Input

The program takes the following inputs:
- Total number of cylinders (Cylinder number starts from 0)
- Sequence of cylinder requests (Cylinder number along with request arrival time)

## Implementation Details

### FCFS (First Come First Serve)
1. Requests are serviced in the order they arrive in the disk queue.
2. The algorithm does not prioritize seek time and provides fair service.

### SSTF (Shortest Seek Time First)
1. Requests closer to the current disk head position are serviced first to minimize seek operations.

### SCAN (Elevator Algorithm)
1. The head starts from one end of the disk and moves towards the other end, servicing requests in between one by one.
2. After reaching the other end, the direction of the head is reversed, and the process continues as the head scans back and forth to access the disk.

### C-SCAN (Circular SCAN Algorithm)
1. The head moves from one end to the other end, servicing all the requests.
2. Upon reaching the other end, it immediately returns to the beginning of the disk without servicing any requests on the return trip.
3. The head starts servicing again once it reaches the beginning.

## Running the Program

1. Download the provided zip folder and extract all the files.
2. Open the "Lab09" folder and open the terminal in that folder.
3. For macOS users, if needed, run the following command on the terminal before compiling the attached codes:
      xcode-select --install
4. Run the following commands for compilation and execution:
      $ g++ <filename>.cpp -o <filename>
      $ ./<filename>

## Output

The program provides the following output:
- Total cylinder movement
- Seek sequence
- Waiting time
- Cylinder number and time (in ms)
- Average waiting time
- Turnaround time
- Average turnaround time
  
