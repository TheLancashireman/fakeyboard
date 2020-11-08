/* fakeyboard.c - project source for Fakeyboard
 *
 * Copyright David Haworth
 *
 * This file is part of Fakeyboard.
 *
 * Fakeyboard is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Fakeyboard is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Fakeyboard.  If not, see <http://www.gnu.org/licenses/>.
 *
 *
 *
*/
#define DV_ASM	0
#include <dv-config.h>
#include <davroska.h>
#include <dv-stdio.h>
#include <dv-string.h>

/* This include file selects the hardware type
*/
#include FAKEY_TARGET

/* Task main functions, along with a description of how they interact.
 *
 * ...
*/
/* Object identifiers
*/
dv_id_t Init, Led;							/* Tasks */
dv_id_t Uart, Timer;						/* ISRs */
dv_id_t Ticker;								/* Counters */
dv_id_t LedOn, LedOff;						/* Alarms */

const dv_eventmask_t ev_LedOn	= 0x01;	/* Turn LED on */
const dv_eventmask_t ev_LedOff	= 0x02;	/* Turn LED off */

/* main_Led() - task body function for the Led task
*/
void main_Led(void)
{
	dv_statustype_t ee;
	dv_eventmask_t events;

	for (;;)
	{
		if ( (ee = dv_waitevent(ev_LedOn|ev_LedOff)) != dv_e_ok )
			dv_shutdown(ee);
		if ( (ee = dv_getevent(Led, &events)) != dv_e_ok )
			dv_shutdown(ee);
		if ( (ee = dv_clearevent(events)) != dv_e_ok )
			dv_shutdown(ee);

		if ( (events & ev_LedOff) != 0 )
		{
			hw_SetLed(0);
		}

		if ( (events & ev_LedOn) != 0 )
		{
			hw_SetLed(1);
		}
	}
}

/* main_Init() - start the ball rolling
*/
void main_Init(void)
{
	dv_printf("main_Init() reached\n");
	sysinfo();
	for ( int i = 0; i < dv_nexe; i++ )
	{
		dv_printf("%d %s  b=%d r=%d c=%d %d\n", i, dv_exe[i].name, dv_exe[i].baseprio, dv_exe[i].runprio,
													dv_exe[i].currprio, dv_exe[i].state);
	}
}

/* main_Uart() - body of ISR to handle uart rx interrupt
*/
void main_Uart(void)
{
	while ( dv_consoledriver.isrx() )
	{
		int c = dv_consoledriver.getc();

		dv_printf("uart rx : 0x%02x\n", c);
	}
}

/* main_Timer() - body of ISR to handle interval timer interrupt
*/
void main_Timer(void)
{
	hw_ClearTimer();

	dv_statustype_t ee = dv_advancecounter(Ticker, 1);
	if ( ee != dv_e_ok )
		dv_shutdown(ee);
}

/* af_LedOn() - alarm function to turn on the LED
*/
dv_u64_t af_LedOn(dv_id_t a, dv_param_t unused_d)
{
	dv_setevent(Led, ev_LedOn);
	return 2000;
}

/* af_LedOff() - alarm function to turn on the LED
*/
dv_u64_t af_LedOff(dv_id_t a, dv_param_t unused_d)
{
	dv_setevent(Led, ev_LedOff);
	return 2000;
}

/* callout_addtasks() - configure the tasks
*/
void callout_addtasks(dv_id_t mode)
{
	Init = dv_addtask("Init", &main_Init, 4, 1);
	Led = dv_addextendedtask("Led", &main_Led, 1, 2048);
}

/* callout_addisrs() - configure the isrs
*/
void callout_addisrs(dv_id_t mode)
{
	Uart = dv_addisr("Uart", &main_Uart, hw_UartInterruptId, 7);
	Timer = dv_addisr("Timer", &main_Timer, hw_TimerInterruptId, 8);
}

/* callout_addgroups() - configure the executable groups
 *
 * ToDo: remove the contents - just for testing
*/
void callout_addgroups(dv_id_t mode)
{
}

/* callout_addmutexes() - configure the mutexes
*/
void callout_addmutexes(dv_id_t mode)
{
}

/* callout_addcounters() - configure the counters
*/
void callout_addcounters(dv_id_t mode)
{
	Ticker = dv_addcounter("Ticker");
}

/* callout_addalarms() - configure the alarms
*/
void callout_addalarms(dv_id_t mode)
{
	LedOn = dv_addalarm("LedOn", &af_LedOn, 0);
	LedOff = dv_addalarm("LedOff", &af_LedOff, 0);
}

/* callout_autostart() - start the objects that need to be running after dv_startos()
*/
void callout_autostart(dv_id_t mode)
{
	dv_activatetask(Init);
	dv_activatetask(Led);
	dv_setalarm_rel(Ticker, LedOn, 1000);
	dv_setalarm_rel(Ticker, LedOff, 1025);

	/* Enable interrupts from the UART
	*/
	hw_EnableUartRxInterrupt();
	dv_enable_irq(hw_UartInterruptId);

	hw_InitialiseMillisecondTicker();
	dv_enable_irq(hw_TimerInterruptId);
}

/* callout_reporterror() - called if an error is detected
*/
dv_statustype_t callout_reporterror(dv_sid_t sid, dv_statustype_t e, dv_qty_t nparam, dv_param_t *param)
{
	dv_printf("callout_reporterror(%d, %d, %d, ...) called.\n", sid, e, nparam);
	for (int i = 0; i < nparam; i++ )
	{
		/* Only print the lower 32 bits of the parameters
		*/
		dv_printf("    param[%d] = %d (0x%08x)\n", i, (dv_u32_t)param[i], (dv_u32_t)param[i]);
	}

	for (;;) {} /* Temporary */
	return e;
}

/* callout_shutdown() - called on shutdown
*/
void callout_shutdown(dv_statustype_t e)
{
	dv_printf("callout_shutdown: %d\n", e);
}

/* callout_idle() - called in idle loop
*/
void callout_idle(void)
{
	dv_printf("Idle loop reached\n");
	for (;;) {}
}

/* callout_panic() - called from dv_panic
*/
#ifndef panic_info
#define panic_info()	do { } while (0)
#endif
void callout_panic(dv_panic_t p, dv_sid_t sid, char *fault)
{
	dv_printf("Panic %d in %d : %s\n", p, sid, fault);
	panic_info();
}

/* main() - well, it's main, innit?
*/
int main(int argc, char **argv)
{
	dv_printf("Fakeyboard starting ...\n");

	sysinfo();

	dv_startos(0);

	return 0;
}
