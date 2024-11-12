#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <stdbool.h>

#define MAX_TASKS 3

typedef struct {
    void (*taskFunction)(void);  
    uint8_t priority;            
    uint8_t taskID;              
    uint32_t periodMs;           
    uint32_t elapsedMs;          
    bool isReady;                
} Task;

static Task taskList[MAX_TASKS];
static uint8_t taskCount = 0;
static uint32_t currentTick = 0;

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
    usleep(ms * 1000);
}

static void LogTaskStatus(const char *executingMessage) {
    printf("\033[H\033[J");

    printf("Current Tick: %d ms\n", currentTick);

    if (executingMessage != NULL) {
        printf("%s\n\n", executingMessage);
    }

    printf("%-10s%-12s%-12s%-20s%-10s\n", "Task ID", "Priority", "Period", "Elapsed Time (s)", "Ready");
    for (uint8_t i = 0; i < taskCount; i++) {
        Task *task = &taskList[i];
        printf("%-10d%-12d%-12d%-20.2f%-10s\n",
               task->taskID,
               task->priority,
               task->periodMs,
               task->elapsedMs / 1000.0,
               task->isReady ? "Yes" : "No");
    }
    printf("\n");
}

static void SchedulerRun(uint32_t tickMs) {
    while (1) {
        Task *highestPriorityTask = NULL;
        char executingMessage[100] = "";

        for (uint8_t i = 0; i < taskCount; i++) {
            taskList[i].elapsedMs += tickMs;
            if (taskList[i].elapsedMs >= taskList[i].periodMs) {
                taskList[i].isReady = true;  
            }
        }

        for (uint8_t i = 0; i < taskCount; i++) {
            if (taskList[i].isReady) {
                if (highestPriorityTask == NULL || taskList[i].priority > highestPriorityTask->priority) {
                    highestPriorityTask = &taskList[i];
                }
            }
        }

        if (highestPriorityTask != NULL) {
            snprintf(executingMessage, sizeof(executingMessage),
                     "Executing Task ID: %d | Priority: %d",
                     highestPriorityTask->taskID,
                     highestPriorityTask->priority);

            LogTaskStatus(executingMessage);

            highestPriorityTask->taskFunction();
            highestPriorityTask->elapsedMs = 0;
            highestPriorityTask->isReady = false;
        }

        delayMs(tickMs);  
        
        currentTick += tickMs;
    }
}

void ReadSensorData() {
    printf("Task 1 (Read Sensor Data): Reading sensor data...\n");
    delayMs(50);  
}

void ProcessData() {
    printf("Task 2 (Process Data): Processing data...\n");
    delayMs(100);  
}

void CommunicateWithDevice() {
    printf("Task 3 (Communicate): Communicating with device...\n");
    delayMs(150); 
}

int main() {
    AddTask(ReadSensorData, 3, 500);       
    AddTask(ProcessData, 2, 1000);         
    AddTask(CommunicateWithDevice, 1, 1500); 

    SchedulerRun(400);

    return 0;
}

