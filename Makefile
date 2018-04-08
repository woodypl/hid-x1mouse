KVERSION=$(shell uname -r)
KDIR := /lib/modules/$(KVERSION)/build
PWD := $(shell pwd)

obj-m += hid-x1mouse.o

all:
	make -C $(KDIR) SUBDIRS=$(PWD) modules
clean:
	make -C $(KDIR) SUBDIRS=$(PWD) clean

install:
	make -C $(KDIR) SUBDIRS=$(PWD) modules_install
