#include <stdlib.h>
#include "kernel.h"
#include "list.h"

#ifndef NULL
#define NULL 0
#endif


/*****************************************************************************
 * Global variables
 *****************************************************************************/

static uint32_t id=1;
Task * tsk_running = NULL;	/* pointer to ready task list : the first
                                     node is the running task descriptor */
Task * tsk_prev = NULL;
Task * tsk_sleeping = NULL;	/* pointer to sleeping task list */

/*****************************************************************************
 * SVC dispatch
 *****************************************************************************/
/* sys_add
 *   test function
 */
int sys_add(int a, int b)
{
    return a+b;
}

/* syscall_dispatch
 *   dispatch syscalls
 *   n      : syscall number
 *   args[] : array of the parameters (4 max)
 */
int32_t svc_dispatch(uint32_t n, uint32_t args[])
{
	int32_t result=-1;

    switch(n) {
    	case 0:
    		result = sys_add((int)args[0], (int)args[1]);
    		break;
    	/* A COMPLETER */
    	case 1:
    		result = malloc(args[0]); //sys_os_alloc((unsigned int)args[0]);
    		break;
    	case 2:
    		free(args[0]);
    		result = 0;
    		break;
    	case 3:
    		result = sys_os_start();
    		break;
    	case 4:
    		result = sys_task_new((TaskCode)args[0], (uint32_t)args[1]);
    		break;
    	case 5:
    		result = sys_task_id();
    	case 6:
    		result = sys_task_wait((uint32_t)args[0]);
    		break;
    	case 7:
    		result = sys_task_kill();
    		break;
    	case 8:
    		result = sys_sem_new((int32_t)args[0]);
    		break;
    	case 9:
    		result = sys_sem_p((Semaphore *)args[0]);
    		break;
    	case 10:
    		result = sys_sem_v((Semaphore *)args[0]);
    		break;
    }
    return result;
}

void sys_switch_ctx()
{
	SCB->ICSR |= 1<<28; // set PendSV to pending
}
/*****************************************************************************
 * Round robin algorithm
 *****************************************************************************/
#define SYS_TICK  10	// system tick in ms

uint32_t sys_tick_cnt=0;

/* tick_cb
 *   system tick callback: task switching, ...
 */
void sys_tick_cb()
{
	/* A COMPLETER */

//    list_display(tsk_running);
}

void SysTick_Handler(void)
{
	sys_tick_cnt++;

	if (sys_tick_cnt == SYS_TICK) {
		sys_tick_cnt = 0;
		sys_tick_cb();
	}
}

/*****************************************************************************
 * General OS handling functions
 *****************************************************************************/

/* sys_os_start
 *   start the first created task
 */
int32_t sys_os_start()
{
	/* A COMPLETER */
	tsk_running->status = TASK_RUNNING;
	sys_switch_ctx();
	// Reset BASEPRI
    __set_BASEPRI(0);

	// Set systick reload value to generate 1ms interrupt
    SysTick_Config(SystemCoreClock / 1000U);
    return 0;
}

/*****************************************************************************
 * Task handling functions
 *****************************************************************************/
void task_kill();

/* sys_task_new
 *   create a new task :
 *   func      : task code to be run
 *   stacksize : task stack size
 *
 *   Stack frame:
 *      |    xPSR    |
 *      |     PC     |
 *      |     LR     |
 *      |     R12    |    ^
 *      |     R3     |    ^
 *      |     R2     |    | @++
 *      |     R1     |
 *      |     R0     |
 *      +------------+
 *      |     R11    |
 *      |     R10    |
 *      |     R9     |
 *      |     R8     |
 *      |     R7     |
 *      |     R6     |
 *      |     R5     |
 *      |     R4     |
 *      +------------+
 *      | EXC_RETURN |
 *      |   CONTROL  | <- sp
 *      +------------+
 */
int32_t sys_task_new(TaskCode func, uint32_t stacksize)
{
	// get a stack with size multiple of 8 bytes
	uint32_t size = stacksize>96 ? 8*(((stacksize-1)/8)+1) : 96;
	
	/* A COMPLETER */
	Task* task =(Task*)malloc(sizeof(Task)+size);
	if(!task) return -1;

	task->id= id++;
	task->status = TASK_READY;
	task->delay = 0;
	task->splim = (uint32_t*)(task+1);
	task->sp = task->splim + (size/4);

	task->sp = (uint32_t *)(task->sp - 18); 			// Décrémenter sp pour réserver la ctx

	task->sp[0] = 1;          						// CONTROL - Mode Thread unprivileged
	task->sp[1] = 0xFFFFFFFD; 						// EXC_RETURN
    task->sp[16] = func;      						// PC - Qu'est-ce que la tache doit executer? -func
    task->sp[17] = 1 << 24;   						// xPSR - Valeur du registre d'état au demarrage (juste le bit T)
    											// 2ème Methode: task->sp[17]=0x01000000;
	task->sp[15]=task_kill;						// Kill the task at the end of the code execution


	tsk_running = list_insert_tail(tsk_running, task);

	return task->id;
}

/* sys_task_kill
 *   kill oneself
 */
int32_t sys_task_kill()
{
	/* A COMPLETER */
	Task *task_to_kill = NULL;
	tsk_running = list_remove_head(tsk_running, &task_to_kill);
	free(task_to_kill);
	tsk_running->status = TASK_RUNNING;
	sys_switch_ctx();
	return -1;
}

/* sys_task_id
 *   returns id of task
 */
int32_t sys_task_id()
{
	/* A COMPLETER */
	if (tsk_running)
	    {
	        return tsk_running->id;
	    }
    return -1;
}


/* sys_task_yield
 *   run scheduler to switch to another task
 */
int32_t sys_task_yield()
{

    return -1;
}

/* task_wait
 *   suspend the current task until timeout
 */
int32_t sys_task_wait(uint32_t ms)
{
	/* A COMPLETER */

    return -1;
}


/*****************************************************************************
 * Semaphore handling functions
 *****************************************************************************/

/* sys_sem_new
 *   create a semaphore
 *   init    : initial value
 */
Semaphore * sys_sem_new(int32_t init)
{
	/* A COMPLETER */

    return NULL;
}

/* sys_sem_p
 *   take a token
 */
int32_t sys_sem_p(Semaphore * sem)
{
	/* A COMPLETER */

	return -1;
}

/* sys_sem_v
 *   release a token
 */
int32_t sys_sem_v(Semaphore * sem)
{
	/* A COMPLETER */

	return -1;
}
