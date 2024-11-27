/*
 *
 *
 *
 *
 */

#include "scheduler.h"
#include "task.h"
#include <stdlib.h>

/*
void SCH_Init(void) {
	unsigned char i;
	for (i = 0 ; i < SCH_MAX_TASKS; i++) {
		 SCH_Delete_Task(i);
	}
}

void SCH_Update(void) {
	unsigned char Index;

	// NOTE: calculations are in *TICKS* (not milliseconds)
    for (Index = 0; Index < SCH_MAX_TASKS; Index++) {
	    // Check if there is a task at this location
	     if (SCH_tasks_G[Index].pTask){
	         if (SCH_tasks_G[Index].Delay == 0) {
	             // The task is due to run
	             // Inc. the 'RunMe' flag
	             SCH_tasks_G[Index].RunMe += 1;
	             if (SCH_tasks_G[Index].Period) {
	            	 // Schedule periodic tasks to run again
	            	 SCH_tasks_G[Index].Delay = SCH_tasks_G[Index].Period;
	             }
	         } else {
	        	 // Not yet ready to run: just decrement the delay
	        	 SCH_tasks_G[Index].Delay -= 1;
	         }
	     }
	}
}

void SCH_Dispatch_Task(void) {
    unsigned char Index;
    // Dispatches (runs) the next task (if one is ready)
    for (Index = 0; Index < SCH_MAX_TASKS; Index++){
	   	 if (SCH_tasks_G[Index].RunMe > 0) {
	   		 (*SCH_tasks_G[Index].pTask)(); // Run the task
 	         SCH_tasks_G[Index].RunMe -= 1; // Reset / reduce RunMe flag
 	         // Periodic tasks will automatically run again
 	         // - if this is a 'one shot' task, remove it from the array
 	         if (SCH_tasks_G[Index].Period == 0) {
 	        	 SCH_Delete_Task(Index);
             }
    	 }
    }
}

unsigned char SCH_Add_Task(void (* pFunction)(), unsigned int DELAY, unsigned int PERIOD) {
    unsigned char Index = 0;

    // First find a gap in the array (if there is one)
    while ((SCH_tasks_G[Index].pTask != 0) && (Index < SCH_MAX_TASKS)) {
       Index++;
    }

    // Have we reached the end of the list?
    if (Index == SCH_MAX_TASKS) {

        return SCH_MAX_TASKS;
    }

    // If we're here, there is a space in the task array
    SCH_tasks_G[Index].pTask = pFunction;
    SCH_tasks_G[Index].Delay = DELAY;
    SCH_tasks_G[Index].Period = PERIOD;
    SCH_tasks_G[Index].RunMe = 0;

    // return position of task (to allow later deletion)
    return Index;
}

unsigned char SCH_Delete_Task(const int TASK_INDEX){
    unsigned char Return_code;
    if (SCH_tasks_G[TASK_INDEX].pTask == 0) {
        Return_code = 0;
    } else {
        Return_code = 1;
    }

    SCH_tasks_G[TASK_INDEX].pTask = 0x0000;
    SCH_tasks_G[TASK_INDEX].Delay = 0;
    SCH_tasks_G[TASK_INDEX].Period = 0;
    SCH_tasks_G[TASK_INDEX].RunMe = 0;
    return Return_code; // return status
}
*/


/*

// Head of the linked list that holds tasks
TaskNode* taskListHead = NULL;  // Initially, no tasks

// Initialize the scheduler (reset task list)
void SCH_Init(void) {
    taskListHead = NULL;  // No tasks initially
}

// Update the tasks, decrement delays, and check if tasks are due
void SCH_Update(void) {
    TaskNode* current = taskListHead;
    TaskNode* prev = NULL;

    while (current != NULL) {
        if (current->Delay == 0) {
            current->RunMe++;  // Task is ready to run
            if (current->Period) {
                current->Delay = current->Period;  // Re-schedule periodic tasks
            } else {
                // Remove one-shot tasks from the list
                if (prev) {
                    prev->next = current->next;
                } else {
                    taskListHead = current->next;  // Remove from head
                }
                free(current);
                current = prev ? prev->next : taskListHead;  // Continue with next task
                continue;
            }
        } else {
            current->Delay--;  // Decrement the delay
        }

        prev = current;
        current = current->next;
    }
}

// Dispatch and run the tasks that are ready
void SCH_Dispatch_Task(void) {
    TaskNode* current = taskListHead;
    while (current != NULL) {
        if (current->RunMe > 0) {
            (*current->pTask)();  // Execute the task function
            current->RunMe--;     // Reset RunMe flag
            if (current->Period == 0) {
                // One-shot task, remove it from the list
                TaskNode* toDelete = current;
                current = current->next;
                free(toDelete);
            } else {
                current = current->next;  // Move to the next task
            }
        } else {
            current = current->next;
        }
    }
}

// Add a new task to the scheduler
unsigned char SCH_Add_Task(void (*pFunction)(), unsigned int DELAY, unsigned int PERIOD) {
    TaskNode* newTask = (TaskNode*)malloc(sizeof(TaskNode));
    if (!newTask) return 0;  // Allocation failed

    newTask->pTask = pFunction;
    newTask->Delay = DELAY;
    newTask->Period = PERIOD;
    newTask->RunMe = 0;
    newTask->next = NULL;

    // Insert the new task at the end of the list
    if (taskListHead == NULL) {
        taskListHead = newTask;  // If the list is empty, new task is the head
    } else {
        TaskNode* temp = taskListHead;
        while (temp->next) {
            temp = temp->next;  // Traverse to the last task
        }
        temp->next = newTask;  // Append the new task
    }

    return 1;  // Task added successfully
}

// Delete a specific task from the scheduler
unsigned char SCH_Delete_Task(TaskNode* taskToDelete) {
    if (!taskToDelete) return 0;  // Invalid task

    if (taskListHead == taskToDelete) {
        taskListHead = taskToDelete->next;  // Remove task from head
    } else {
        TaskNode* current = taskListHead;
        while (current != NULL && current->next != taskToDelete) {
            current = current->next;  // Find the task to delete
        }
        if (current != NULL) {
            current->next = taskToDelete->next;  // Bypass the task to delete
        }
    }
    free(taskToDelete);  // Free memory
    return 1;  // Task deleted successfully
}
*/

// Initialize the scheduler
void SCH_Init(void) {
    SCH_GlobalTick = 0;  // Reset global tick counter
    SCH_TaskList = NULL; // Initialize the task list as empty
}

// Update the scheduler (called in the ISR)
void SCH_Update(void) {
    SCH_GlobalTick++;  // Increment the global tick (called in ISR)

    // Check if there are any tasks in the task list
    if (SCH_TaskList == NULL) {
        return;  // No tasks to run
    }

    // The task at the front of the list has the earliest nextRunTime
    Task* currentTask = SCH_TaskList;

    // Check if the task is ready to run (its next run time has arrived)
    if (currentTask->nextRunTime <= SCH_GlobalTick) {
        // Run the task
        currentTask->pTask();

        // Update the nextRunTime for periodic tasks
        if (currentTask->period > 0) {
            currentTask->nextRunTime = SCH_GlobalTick + currentTask->period;
        } else {
            // For one-shot tasks, remove it from the list after execution
            SCH_TaskList = currentTask->next;
            free(currentTask);  // Free the memory for the one-shot task
        }
    }
}

// Dispatch (run) the next task from the task list
void SCH_Dispatch_Task(void) {
    Task* currentTask = SCH_TaskList;
    unsigned char taskIndex = 0;

    while (currentTask != NULL) {
        if (currentTask->nextRunTime <= SCH_GlobalTick) {
            // Run the task
            currentTask->pTask();

            // For periodic tasks, update nextRunTime
            if (currentTask->period > 0) {
                currentTask->nextRunTime = SCH_GlobalTick + currentTask->period;
                currentTask = currentTask->next;  // Move to the next task
                taskIndex++;
            } else {
                // For one-shot tasks, use SCH_Delete_Task to remove them
                unsigned char result = SCH_Delete_Task(taskIndex);

                // If deletion was successful, move to the next task
                if (result == 1) {
                    currentTask = currentTask->next;
                } else {
                    // Handle the failure of deletion if necessary (this should rarely happen)
                    currentTask = currentTask->next;
                }
            }
        } else {
            currentTask = currentTask->next;
            taskIndex++;
        }
    }
}






// Add a task to the scheduler
unsigned char SCH_Add_Task(void (*pFunction)(), unsigned int DELAY, unsigned int PERIOD) {
    Task* newTask = (Task*)malloc(sizeof(Task));
    if (newTask == NULL) {
        return SCH_MAX_TASKS;  // Memory allocation failed
    }

    // Initialize the task structure
    newTask->pTask = pFunction;
    newTask->nextRunTime = SCH_GlobalTick + DELAY;
    newTask->period = PERIOD;
    newTask->next = NULL;

    // Insert the new task into the task list while maintaining order
    if (SCH_TaskList == NULL || SCH_TaskList->nextRunTime > newTask->nextRunTime) {
        // Insert at the head if the list is empty or new task is due earlier
        newTask->next = SCH_TaskList;
        SCH_TaskList = newTask;
    } else {
        // Find the correct position to insert (in sorted order)
        Task* current = SCH_TaskList;
        while (current->next != NULL && current->nextRunTime <= newTask->nextRunTime) {
            current = current->next;
        }
        newTask->next = current->next;
        current->next = newTask;
    }

    return 1;  // Task successfully added
}



// Delete a task from the scheduler
unsigned char SCH_Delete_Task(const int TASK_INDEX) {
    Task* current = SCH_TaskList;
    Task* previous = NULL;
    unsigned char i = 0;

    // Traverse the task list to find the task to delete
    while (current != NULL && i < TASK_INDEX) {
        previous = current;
        current = current->next;
        i++;
    }

    // If task was not found, return failure
    if (current == NULL) {
        return 0;  // Task not found
    }

    // Task found, remove it from the list
    if (previous == NULL) {
        // The task is at the head of the list
        SCH_TaskList = current->next;
    } else {
        // Task is in the middle or end of the list
        previous->next = current->next;
    }

    free(current);  // Free the memory occupied by the task
    return 1;  // Task successfully deleted
}
