/*
 *  HID driver for Thinkpad X1 Wireless Mouse
 *
 *  Copyright (c) 2018 Pawel Drewniak
 */

/*
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation; either version 2 of the License, or (at your option)
 * any later version.
 */

#include <linux/device.h>
#include <linux/input.h>
#include <linux/hid.h>
#include <linux/module.h>

#include "hid-ids.h"

#define map_rel_clear(c)      hid_map_usage_clear(hi, usage, bit, max, EV_REL, (c))
#define map_key_clear(c)      hid_map_usage_clear(hi, usage, bit, max, EV_KEY, (c))

static int x1mouse_input_mapping(struct hid_device *hdev, struct hid_input *hi,
		struct hid_field *field, struct hid_usage *usage,
		unsigned long **bit, int *max)
{
	if ((usage->hid & HID_USAGE_PAGE) == HID_UP_GENDESK) {
		switch (usage->hid) {
			case HID_GD_X: map_rel_clear(REL_X); break;
			case HID_GD_Y: map_rel_clear(REL_Y); break;
		default: return 0;
		}
		return 1;
	} else if ((usage->hid & HID_USAGE_PAGE) == HID_UP_BUTTON) {
		int code = ((usage->hid - 1) & HID_USAGE);
		switch (code) {
			case 0: map_key_clear(BTN_LEFT); break;
			case 1: map_key_clear(BTN_RIGHT); break;
			default: return 0;
		}
		return 1;
	}
	return 0;
}

#undef map_rel_clear
#undef map_key_clear

static const struct hid_device_id x1mouse_devices[] = {
	{ HID_USB_DEVICE(USB_VENDOR_ID_LENOVO, USB_DEVICE_ID_LENOVO_X1_MOUSE) },
	{ HID_BLUETOOTH_DEVICE(USB_VENDOR_ID_LENOVO, USB_DEVICE_ID_LENOVO_X1_MOUSE) },
	{ }
};
MODULE_DEVICE_TABLE(hid, x1mouse_devices);

static struct hid_driver x1mouse_driver = {
	.name = "x1mouse",
	.id_table = x1mouse_devices,
	.input_mapping = x1mouse_input_mapping,
};
module_hid_driver(x1mouse_driver);

MODULE_LICENSE("GPL");
