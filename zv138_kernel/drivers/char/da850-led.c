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
#include <linux/delay.h>
#define DA850_GPIO5_3_PIN	GPIO_TO_PIN(5,3)
#define DA850_GPIO5_4_PIN	GPIO_TO_PIN(5,4)
#define DA850_GPIO5_5_PIN	GPIO_TO_PIN(5,5)
#define DA850_GPIO5_6_PIN	GPIO_TO_PIN(5,6)
#define DA850_GPIO5_7_PIN	GPIO_TO_PIN(5,7)

#define DA850_GPIO3_6_PIN	GPIO_TO_PIN(3,6)
#define DA850_GPIO3_7_PIN	GPIO_TO_PIN(3,7)
static int value = 0;
unsigned int *reg,*reg1;
static irqreturn_t led_interrupt(int irq, void *dev_id)
{
	 value=!value;
	 gpio_direction_output(DA850_GPIO3_6_PIN,!value);
	 gpio_direction_output(DA850_GPIO3_7_PIN,value);
	 reg1=(unsigned int *)ioremap(0x1c14174,4);
	 *reg1=1<<3;
	 iounmap(reg1);
	 return 0;
}
static irqreturn_t irq_test(int irq,void *dev_id)
{
	reg=(unsigned int *)ioremap(0x1c14178,4);
	*reg=1<<3;
	iounmap(reg);
	printk(KERN_WARNING"irq_test!!!!!!!!!!!\n");
	return 0;
}

static void set_gpio_request(void)
{
	int ret;
	ret=gpio_request(DA850_GPIO5_3_PIN,"gpio5_3");
	if(ret)
		{
			printk(KERN_WARNING"gpio5_3 requeset failed !!!\n");
		}

	ret=gpio_request(DA850_GPIO5_4_PIN,"gpio5_4");
	if(ret)
		{
			printk(KERN_WARNING"gpio5_4 requeset failed !!!\n");
		}

	ret=gpio_request(DA850_GPIO5_5_PIN,"gpio5_5");
	if(ret)
		{
			printk(KERN_WARNING"gpio5_5 requeset failed !!!\n");
		}

	ret=gpio_request(DA850_GPIO5_6_PIN,"gpio5_6");
	if(ret)
		{
			printk(KERN_WARNING"gpio5_6 requeset failed !!!\n");
		}

	ret=gpio_request(DA850_GPIO5_7_PIN,"gpio5_7");
	if(ret)
		{
			printk(KERN_WARNING"gpio5_7 requeset failed !!!\n");
		}
	ret=gpio_request(DA850_GPIO3_6_PIN,"gpio3_6");
	if(ret)
		{
			printk(KERN_WARNING"gpio3_6 requeset failed !!!\n");
		}
	ret=gpio_request(DA850_GPIO3_7_PIN,"gpio3_7");
	if(ret)
		{
			printk(KERN_WARNING"gpio3_7 requeset failed !!!\n");
		}
}

static void set_gpio_direction(void)
{
	gpio_direction_output(DA850_GPIO3_6_PIN,1);
	gpio_direction_output(DA850_GPIO3_7_PIN,1);
	
	gpio_direction_input(DA850_GPIO5_3_PIN);
	gpio_direction_input(DA850_GPIO5_4_PIN);
	gpio_direction_input(DA850_GPIO5_5_PIN);
	gpio_direction_input(DA850_GPIO5_6_PIN);
	gpio_direction_input(DA850_GPIO5_7_PIN);

}
int abc;
static void set_irq(void)
{
/*	set_irq_type(gpio_to_irq(DA850_GPIO5_3_PIN),IRQ_TYPE_EDGE_FALLING);
	set_irq_type(gpio_to_irq(DA850_GPIO5_4_PIN),IRQ_TYPE_EDGE_FALLING);
	set_irq_type(gpio_to_irq(DA850_GPIO5_5_PIN),IRQ_TYPE_EDGE_FALLING);
	set_irq_type(gpio_to_irq(DA850_GPIO5_6_PIN),IRQ_TYPE_EDGE_FALLING);
	set_irq_type(gpio_to_irq(DA850_GPIO5_7_PIN),IRQ_TYPE_EDGE_FALLING);
*/
	request_irq(gpio_to_irq(DA850_GPIO5_3_PIN),led_interrupt,IRQF_TRIGGER_FALLING,"led",NULL);
	request_irq(gpio_to_irq(DA850_GPIO5_4_PIN),led_interrupt,IRQF_TRIGGER_FALLING,"led",NULL);
	request_irq(gpio_to_irq(DA850_GPIO5_5_PIN),led_interrupt,IRQF_TRIGGER_FALLING,"led",NULL);
	request_irq(gpio_to_irq(DA850_GPIO5_6_PIN),led_interrupt,IRQF_TRIGGER_FALLING,"led",NULL);
	request_irq(gpio_to_irq(DA850_GPIO5_7_PIN),led_interrupt,IRQF_TRIGGER_FALLING,"led",NULL);
//	request_irq(31,irq_test,IRQF_SHARED,"led",&abc);

}

static int __init da850_led_init(void)
{
	
	printk(KERN_WARNING"da850 led init !!!!\n");
	
	set_gpio_request();
	set_gpio_direction();
	set_irq();	
	return 0;
}
static void __init da850_led_exit(void)
{
	gpio_free(DA850_GPIO5_3_PIN);
	gpio_free(DA850_GPIO5_4_PIN);
	gpio_free(DA850_GPIO5_5_PIN);
	gpio_free(DA850_GPIO5_6_PIN);
	gpio_free(DA850_GPIO5_7_PIN);


	gpio_free(DA850_GPIO3_6_PIN);
	gpio_free(DA850_GPIO3_7_PIN);
}
module_init(da850_led_init);
module_exit(da850_led_exit);
MODULE_DESCRIPTION("SEED-DIM_GB LED driver");
MODULE_AUTHOR("SEED txyugood");
MODULE_LICENSE("GPL");
