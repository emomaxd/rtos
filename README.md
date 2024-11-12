# rtos - Simple Preemptive Task Scheduler
This project demonstrates a simple preemptive task scheduler written in C. It schedules and executes tasks based on their priorities and periodic intervals, simulating tasks such as reading sensor data, processing data, and communicating with external devices.

## Features:
- **Preemptive Scheduling**: The scheduler prioritizes tasks and runs the highest-priority task that is ready to execute.
- **Simulated Tasks**: Three tasks are included to simulate reading sensor data, processing data, and communicating with an external device.
- **Task Management**: Add tasks to the scheduler with different priorities and periods.
- **Real-time Scheduling**: Tasks are triggered based on their defined periods and are executed accordingly.

## Installation and Usage:
1. Clone the repository:
    ```bash
    git clone https://github.com/emomaxd/rtos.git
    ```
2. Get into the cloned directory
    ```bash
    cd rtos
    ```
3. Compile & run
    ```bash
    gcc -o rtos rtos.c
    ./rtos
    ```

## Example output
    Task 1 (Read Sensor Data): Reading sensor data...
    Task 1 (Read Sensor Data): Reading sensor data...
    Task 2 (Process Data): Processing data...
    Task 1 (Read Sensor Data): Reading sensor data...
    Task 3 (Communicate): Communicating with device...
    Task 1 (Read Sensor Data): Reading sensor data...
    Task 2 (Process Data): Processing data...
