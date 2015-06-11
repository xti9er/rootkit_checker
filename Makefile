obj-m :=process_list.o
KDIR := /lib/modules/$(shell uname -r)/build
PWD := $(shell pwd)
default:
  $(MAKE) -C $(KDIR) SUBDIRS=$(PWD) modules
install:
  rmmod process_list.ko 2>1& > /dev/null;insmod process_list.ko
clean:
  rm -f *.mod.c *.ko *.o
