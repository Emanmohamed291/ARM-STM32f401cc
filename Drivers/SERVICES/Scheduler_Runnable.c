/*
 * Scheduler_Runnable.c
 *
 * Created: 3/14/2024 9:00:58 AM
 *  Author: Eman
 */ 
#include "Scheduler_Runnable.h"
#include "Scheduler.h"

extern runnableCBF_t SW_Runnable;
extern runnableCBF_t APP1_Runnable;
extern runnableCBF_t APP2_Runnable;
extern runnableCBF_t Traffic_Runnable;

const runnable_t SYSRunnables[_Runnables_Num] =
{
    [APP1]={
        .name = "led1",
        .delay_ms = 20,
	    .periodicitymS = 500,
	    .CBfunc = &APP1_Runnable
    },
    [APP2]={
        .name = "led2 with switch",
        .delay_ms = 20,
	    .periodicitymS = 30,
	    .CBfunc = &APP2_Runnable
    },
    [SWITCH]={
        .name = "switch1",
        .delay_ms = 10,
	    .periodicitymS = 20,
	    .CBfunc = &SW_Runnable
    },
    [TRAFFICAPP]={
        .name = "traffic1",
        .delay_ms = 0,
	    .periodicitymS = 1000,
	    .CBfunc = &Traffic_Runnable
    }
};