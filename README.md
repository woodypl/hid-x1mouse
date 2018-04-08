# Lenovo Thinkpad X1 Wireless Touch Mouse
This is a kernel module for the Thinkpad X1 Wireless Touch Mouse.
It makes the following features work:

* Touchpad on the back
* Tap-to-click on the touchpad

## Prerequisites

* Kernel headers for your current kernel (e.g. kernel-devel on most RPM based systems)
* GCC
* make


## Installation

```bash
make
make install
modprobe hid-x1mouse
```

## Technical notes

The mouse gets detected fine by the hid-generic module.
However, because the pointer and touchpad are treated as one device, `GenericDesktop.X` and `GenericDesktop.Y` HID usages are exposed twice and the touchpad axes end up getting mapped to Z and Rx axes. Touchpad buttons are in similar situation. This module makes input mapping for the axes and buttons explicit.

## Feedback

Comments and pull requests are most welcome.
