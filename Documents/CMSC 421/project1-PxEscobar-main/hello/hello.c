#include <linux/kernel.h>
#include <linux/syscalls.h>

SYSCALL_DEFINE0(hello) {
	printk("Hello World!\n");
	return 0;
}
