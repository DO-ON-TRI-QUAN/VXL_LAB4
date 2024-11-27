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
