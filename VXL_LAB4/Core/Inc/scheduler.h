/*
 *
 *
 *
 *
 */

#include "main.h"

#ifndef INC_SCHEDULER_H_
#define INC_SCHEDULER_H_


#define SCH_MAX_TASKS 40
#define NO_TASK_ID 0

/*
typedef struct {
	// Pointer to the task (must be a ’void (void)’ function )
	void (*pTask) (void) ;

	// Delay (ticks) until the function will (next) be run
	uint32_t Delay;

	// Interval (ticks) between subsequent runs .
	uint32_t Period;

	// Incremented (by scheduler) when task is due to execute
	uint8_t RunMe;

	//This is a hint to solve the problem
	uint32_t TaskID;

} sTask ;

sTask SCH_tasks_G[SCH_MAX_TASKS] ;

*/

/*

// Define the task structure (linked list node)
typedef struct TaskNode {
    void (*pTask)(void);          // Pointer to the task function
    uint32_t Delay;               // Delay (ticks) until the task runs
    uint32_t Period;              // Period (ticks) between subsequent runs
    uint8_t RunMe;                // Flag to indicate if the task should run
    uint32_t TaskID;              // Unique task ID
    struct TaskNode* next;        // Pointer to the next task in the list
} TaskNode;

// Function declarations
void SCH_Init(void);
void SCH_Update(void);
void SCH_Dispatch_Task(void);
unsigned char SCH_Add_Task(void (*pFunction)(), unsigned int DELAY, unsigned int PERIOD);
unsigned char SCH_Delete_Task(TaskNode* taskToDelete);
*/

// Task structure
typedef struct Task {
    void (*pTask)(void);      // Pointer to the task function (void function)
    unsigned long nextRunTime; // Time when the task will run
    unsigned long period;      // Period in ticks for periodic tasks (0 for one-shot)
    struct Task* next;         // Pointer to the next task in the list
} Task;

unsigned long SCH_GlobalTick;      // Global tick counter
Task* SCH_TaskList;                // Pointer to the head of the task list

// Function prototypes
void SCH_Init(void);
void SCH_Update(void);
void SCH_Dispatch_Task(void);
unsigned char SCH_Add_Task(void (*pFunction)(), unsigned int DELAY, unsigned int PERIOD);
unsigned char SCH_Delete_Task(const int TASK_INDEX);


#endif /* INC_SCHEDULER_H_ */
