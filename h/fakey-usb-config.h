/* fakey-usb-config.h - USB configuration header file for Fakeyboard
 *
 * This file contains the configuration parameters for the usb subsystem used in Fakeyboard
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
#ifndef fakey_usb_config_h
#define fakey_usb_config_h	1

#include <davroska.h>

/* DV_CFG_USBDRV is the driver header to include
*/
#define DV_CFG_USBDRV	<dv-stm32-usb.h>

/* DV_CFG_USB_N_ENDPOINTS is the number of endpoints to use in the USB peripheral
 * Must be at least 1. Probably a minumum of 2 to make sense.
*/
#define DV_CFG_USB_N_ENDPOINTS	2

/* DV_CFG_USB_N_INTERFACES is the number of interfaces to use in the USB peripheral
 * Must be at least 1.
*/
#define DV_CFG_USB_N_INTERFACES	1

/* DV_CFG_EP0_TX_SIZE and DV_CFG_EP0_RX_SIZE are the sizes of the packet buffers for EP0
 *
 * It isn't clear where these numbers come from.
*/
#define DV_CFG_EP0_TX_SIZE	8
#define DV_CFG_EP0_RX_SIZE	8

/* DV_CFG_USB_INTERRUPTS are the USB interrupts that we want to see.
 * Reset and transfer interrupts are added to this list.
*/
#define	DV_CFG_USB_INTERRUPTS	0

/* Events to be notified to the handler task
*/
#define DV_CFG_USB_SUSPEND_EVT	0
#define DV_CFG_USB_WAKEUP_EVT	0
#define DV_CFG_USB_ERROR_EVT	0
#define DV_CFG_USB_OVERRUN_EVT	0
#define DV_CFG_USB_SOF_EVT		0
#define DV_CFG_USB_ESOF_EVT		0

#endif
