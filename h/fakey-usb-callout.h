/* fakey-usb-callout.h - USB callout header file for Fakeyboard
 *
 * This file contains the callout functions for the usb subsystem used in Fakeyboard
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
#ifndef fakey_usb_callout_h
#define fakey_usb_callout_h	1

#include <davroska.h>

extern dv_id_t Usb;

/* callout_usb_reset() - callout function
 *
 * Called in response to a USB reset event
*/
static inline void callout_usb_reset(void)
{
}

/* callout_usb_transfer() - callout function
 *
 * Called in response to a USB transfer. The parameter contains the endpoint number and direction flag.
 * Returns an "event" for callout_usb_events() to handle
*/
static inline dv_u32_t callout_usb_transfer(dv_u32_t istr)
{
	switch ( istr & DV_USB_EP_ID )
	{
	case 0:		/* Endpoint 0 (control) */
		break;

	case 1:		/* Endpoint 1 */
		break;

	default:	/* There are only 2 endpoints */
		break;
	}
	return 0;
}

static inline void callout_usb_events(dv_u32_t evt)
{
	(void)dv_setevent(Usb, (dv_u64_t)evt);
}

#endif
