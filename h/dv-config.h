/* dv-config.h - davroska configuration header file for Fakeyboard
 *
 * This file contains the configuration parameters for the davroska kernel used in Fakeyboard
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
#ifndef dv_config_h
#define dv_config_h	1

/* Settings for the Blue Pill board
*/
#define DV_TARGET		<arm/h/dv-target-blue-pill.h>
#define FAKEY_TARGET	<fakey-blue-pill.h>
#define DV_USB_CONFIG	<fakey-usb-config.h>
#define DV_USB_CALLOUT	<fakey-usb-callout.h>

/* DV_CFG_MAXEXE is the maximum number of executables (tasks + ISRs) that you can create.
*/
#define DV_CFG_MAXEXE		20

/* DV_CFG_MAXEXTENDED is the maximum number of extended executables that you can create.
 * If this is zero, the event API is omitted.
*/
#define DV_CFG_MAXEXTENDED	5

/* DV_CFG_MAXPRIO is the maximum number of different priorities that you can use
 * The number includes all task and ISR priorities
*/
#define DV_CFG_MAXPRIO		10

/* DV_CFG_NSLOT_EXTRA is the number of extra queue slots you need for tasks with maxact > 1
 * If this is zero the "multiple activations" feature is omitted,
*/
#define DV_CFG_NSLOT_EXTRA	10

/* DV_CFG_MAXMUTEX is the maximum number of mutexes that you can create
*/
#define DV_CFG_MAXMUTEX		10

/* DV_CFG_MAXCOUNTER is the maximum number of counters that you can create
*/
#define DV_CFG_MAXCOUNTER	5

/* DV_CFG_MAXALARM is the maximum number of alarms that you can create
*/
#define DV_CFG_MAXALARM		10

/* Inline versions of the empty callout functions
*/
static inline void callout_preexe(void)
{
}

static inline void callout_postexe(void)
{
}

static inline void callout_startup(void)
{
}


#endif
