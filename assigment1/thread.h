#ifndef __H_THREAD__
#define __H_THREAD__
#include "stdint.h"

#define NUM_THREADS 4
#define ESP = 0x0

#define prem 1                                       // prem 1 enables the preemptive version
#define dyn  1	                            //  dyn 1 enables static scheduling policy

typedef enum {
  FALSE,
  TRUE
} bool;

typedef struct thread_control_block_st {
	uint32_t stack_pointer;
	uint32_t thread_id;
	uint32_t * entry;
	uint32_t priority[2];
	bool assigned;
} TCB;					//Define the TCB 

int thread_create( void * stack, void * function, int priority); //Creates the thread

int get_free_pcb();                         //Find the available control block

void schedule();                          // Schedule the thread

void yield();                            

void exit_thread();

void init_thread(void); 

#endif
