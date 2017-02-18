#include <linux/fs.h>
#include <linux/module.h>
#include <linux/errno.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/cdev.h>
#include <linux/io.h>
#include <linux/ioport.h>
#include <linux/gpio.h>
#include <linux/irq.h>
#include <linux/interrupt.h>

unsigned int *reg;

static irqreturn_t test_irq(int irq,void *dev_id)
{
	reg=(unsigned int *)ioremap(0x1c14178,4);
	*reg=1<<3;
	printk(KERN_WARNING"It is test_irq");
}

static int __init irq_test_init(void)
{
	printk(KERN_WARNING"irq_test init!!!!!!!!!\n");
	request_irq(28,test_irq,IRQF_SHARED,"test","NULL");
	
	return 0;
}

module_init(irq_test_init);
module_exit(irq_test_exit);
MODULE_LICENSE("GPL");

