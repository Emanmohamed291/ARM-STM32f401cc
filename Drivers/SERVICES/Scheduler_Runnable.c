/*
 * Scheduler_Runnable.c
 *
 * Created: 3/14/2024 9:00:58 AM
 *  Author: Eman
 */ 
#include "Scheduler_Runnable.h"
#include "Scheduler.h"
runnableCBF_t Switch_func;
runnableCBF_t led_func;
const runnable_t SYSRunnables[_Runnables_Num] =
{
    [LEDAPP]={
        .name = "led1",
        .delay_ms = 10,
	    .periodicitymS = 50,
	    .CBfunc = &led_func
    },
    [SWICHAPP]={
        .name = "switch1",
        .delay_ms = 10,
	    .periodicitymS = 20,
	    .CBfunc = &Switch_func
    }
};