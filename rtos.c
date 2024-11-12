#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <stdbool.h>

#define MAX_TASKS 3

// Task structure
typedef struct {
    void (*taskFunction)(void);  // Task function pointer
    uint8_t priority;            // Task priority
    uint8_t taskID;              // Task ID for identification
    uint32_t periodMs;           // Period for running the task in ms
    uint32_t elapsedMs;          // Time elapsed since last execution
    bool isReady;                // Flag to indicate if the task is ready
} Task;

static Task taskList[MAX_TASKS];
static uint8_t taskCount = 0;

static void AddTask(void (*taskFunction)(void), uint8_t priority, uint32_t periodMs) {
    if (taskCount < MAX_TASKS) {
        taskList[taskCount].taskFunction = taskFunction;
        taskList[taskCount].priority = priority;
        taskList[taskCount].periodMs = periodMs;
        taskList[taskCount].elapsedMs = 0;
        taskList[taskCount].isReady = false;
        taskList[taskCount].taskID = taskCount;
        taskCount++;
    }
}

static void delayMs(uint32_t ms) {
    usleep(ms * 1000);  // Convert to microseconds
}

// Preemptive scheduler function
static void SchedulerRun(uint32_t tickMs) {
    while (1) {
        Task *highestPriorityTask = NULL;

        // Update elapsed time and set tasks to ready if their period has elapsed
        for (uint8_t i = 0; i < taskCount; i++) {
            taskList[i].elapsedMs += tickMs;
            if (taskList[i].elapsedMs >= taskList[i].periodMs) {
                taskList[i].isReady = true;  
            }
        }

        // Find the highest-priority ready task
        for (uint8_t i = 0; i < taskCount; i++) {
            if (taskList[i].isReady) {
                if (highestPriorityTask == NULL || taskList[i].priority > highestPriorityTask->priority) {
                    highestPriorityTask = &taskList[i];
                }
            }
        }

        // Execute the highest-priority task if one is ready
        if (highestPriorityTask != NULL) {
            highestPriorityTask->taskFunction();
            highestPriorityTask->elapsedMs = 0;
            highestPriorityTask->isReady = false;
        }

        delayMs(tickMs);  
    }
}


// Simulated sensor data reading
void ReadSensorData() {
    printf("Task 1 (Read Sensor Data): Reading sensor data...\n");
    // Simulate data processing time
    delayMs(50);  
}

// Simulated data processing
void ProcessData() {
    printf("Task 2 (Process Data): Processing data...\n");
    // Simulate processing time
    delayMs(100);  
}

// Simulated communication with external device
void CommunicateWithDevice() {
    printf("Task 3 (Communicate): Communicating with device...\n");
    // Simulate communication time
    delayMs(150); 
}

int main() {
    // Function Name - Priority - Period
    AddTask(ReadSensorData, 3, 500);       // High priority, every 500 ms
    AddTask(ProcessData, 2, 1000);         // Medium priority, every 1000 ms
    AddTask(CommunicateWithDevice, 1, 1500); // Low priority, every 1500 ms

    SchedulerRun(100);

    return 0;
}

